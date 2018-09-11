
#include <glm\gtc\matrix_transform.hpp>
#include "ChunkGenerator.h"
#include "ChunkManager.h"
#include "..\Block\BlockDatabase.h"
#include "..\..\Misc\Exceptions.h"

BW::Chunk::Chunk(Location& location, ChunkManager& manager) 
	: manager(manager), chunk_location(location), generated(false)
{
	mesh_ready = false;
	chunk_empty = false;
	ready_to_buffer = false;
	thread_queued = false;
	rebuild_mesh = false;
}

BW::Chunk::~Chunk() {
}

void BW::Chunk::generateChunk(ChunkGenerator& generator) {
	generated = true;
	
	manager.getChunkGenerator().generateChunk(*this);

	if (block_array == nullptr)
		chunk_empty = true;
}

void BW::Chunk::buildMesh() {
	ctpl::thread_pool& pool = manager.getThreadPool();
	pool.push([this](int id) { this->generateVertices(); });
	thread_queued = true;
	rebuild_mesh = false;
}

const BW::Mesh& BW::Chunk::getMesh() {
	return mesh;
}

bool BW::Chunk::readyToDraw() {

	if (!thread_queued && !chunk_empty && (rebuild_mesh || !mesh_ready))
		buildMesh();
	else if (ready_to_buffer) {
		mesh.bufferIndices(indices_data);
		mesh.buffer(vertices_data, Attrib::POSITION, 3);
		mesh.buffer(textures_data, Attrib::TEXTURE, 1);
		mesh.buffer(texcoords_data, Attrib::UVS, 2, true);
		mesh.buffer(light_data, Attrib::LIGHTING, 1);

		vertices_data.clear();
		textures_data.clear();
		texcoords_data.clear();
		indices_data.clear();
		light_data.clear();

		mesh_ready = true;
		ready_to_buffer = false;
		thread_queued = false;
		rebuild_mesh = false;
	}

	return mesh_ready & !chunk_empty;
} 

BW::Block BW::Chunk::getBlock(const short x, const short y, const short z) const {
	if (!inBounds(x, y, z))
		throw InvalidBlockIndex(x, y, z);
	else if (chunk_empty)
		return Block{ AIR };

	return (*block_array)[getBlockIndex(x, y, z)];
}

void BW::Chunk::setBlock(const short x, const short y, const short z, BlockType type) {
	if (!inBounds(x, y, z))
		throw InvalidBlockIndex(x, y, z);

	if (block_array == nullptr)
		block_array = std::make_unique<std::array<Block, Chunk::VOLUME>>();

	(*block_array)[getBlockIndex(x, y, z)].type = type;
	rebuild_mesh = true;
}

BW::Block BW::Chunk::getAdjacentBlock(short x, short y, short z, FACE side) {
	Location adj = Chunk::getAdjacentLocation({ x, y, z }, side);

	if (!inBounds(adj.x, adj.y, adj.z)) {
		Location block = chunk_location * Chunk::SIZE + adj;
		return manager.getBlock(block); //Block{ AIR }; 
	}

	return (*block_array)[getBlockIndex(adj.x, adj.y, adj.z)];
}

BW::Location BW::Chunk::getLocation() {
	return chunk_location;
}



BW::TextureArray& BW::Chunk::getTextureArray() {
	static TextureArray& textures = ResourceManager::getInstance().loadTextureArray("data/textures/textures.json");
	return textures;
}

BW::Location BW::Chunk::getAdjacentLocation(Location location, FACE face) {
	switch (face) {
		case NORTH:  location.z += 1;
			break;	 
		case SOUTH:  location.z -= 1;
			break;	
		case EAST:   location.x += 1;
			break;	 
		case WEST:   location.x -= 1;
			break;	 
		case TOP:    location.y += 1;
			break;	 
		case BOTTOM: location.y -= 1;
			break;
	}

	return location;
}

void BW::Chunk::generateVertices() {
	loadLight();

	vertices_data.reserve(20000);
	texcoords_data.reserve(5000);
	textures_data.reserve(5000);
	indices_data.reserve(5000);

	BlockDatabase& db = BlockDatabase::getInstance();

	GLuint indexCount = 0;
	for (short x = 0; x < Chunk::SIZE; ++x) 
		for (short y = 0; y < Chunk::SIZE; ++y) 
			for (short z = 0; z < Chunk::SIZE; ++z) {
				const Block block = (*block_array)[Chunk::getBlockIndex(x, y, z)];

				if (block.type != BlockType::AIR) {
					glm::mat4 model(1.0f);
					model = glm::translate(model, static_cast<glm::vec3>(chunk_location * Chunk::SIZE) + glm::vec3(x, y, z));

					for (char face = NORTH; face < FACE::SIZE; ++face) {
						FACE side = static_cast<FACE>(face);

						if (getAdjacentBlock(x, y, z, side).type == AIR) {
							const BlockData* blockdata = db.getBlockData(block.type);
							GLubyte lightValue = getBlockLight(x, y, z, side);

							for (char i = 0; i < VERTICES[face].vertices.size(); ++i) {
								glm::vec3 vertex = model * VERTICES[face].vertices[i];

								vertices_data.insert(vertices_data.end(), { vertex.x, vertex.y, vertex.z});
								texcoords_data.insert(texcoords_data.end(), { VERTICES[face].uvs[i].x, VERTICES[face].uvs[i].y });
								textures_data.push_back(blockdata->getTexture(side));
								light_data.push_back(lightValue);
							}

							for (short i = 0; i < INDICES.size(); ++i)
								indices_data.push_back(indexCount + INDICES[i]);

							indexCount += 4;
						}
					}
				}
			}
		
	

	ready_to_buffer = true;
	// The vertex data is now ready to be buffered into the mesh
} 

short BW::Chunk::getBlockIndex(const short x, const short y, const short z) {
	return x * Chunk::AREA + z * Chunk::SIZE + y;
}

bool BW::Chunk::inBounds(const short x, const short y, const short z) {
	return (x >= 0 && x < Chunk::SIZE) && (y >= 0 && y < Chunk::SIZE) && (z >= 0 && z < Chunk::SIZE);
}

void BW::Chunk::loadLight() {
	light_values.clear();
	for (short x = 0; x < Chunk::SIZE; x++) {
		for (short y = 0; y < Chunk::SIZE; y++) {
			for (short z = 0; z < Chunk::SIZE; z++) {
				if (getBlock(x, y, z).type == DEBUGLAMP) {
					Location block{ x, y, z };
					auto& map = light_values;
					std::function<void(Location&, GLubyte)> calc;

					calc = [&calc, &map, this](Location& position, GLubyte light_level) {
						if (light_level <= 2 || !Chunk::inBounds(position.x, position.y, position.z))
							return;

						Block block = this->getBlock(position.x, position.y, position.z);
						if ((block.type != AIR && block.type != DEBUGLAMP))
							return;

						auto val = map.find(position);
						if (val != map.end())
							return; //val->second = std::max(val->second, light_level);
						else {
							map.insert({ position, light_level });

							for (char i = NORTH; i < FACE::SIZE; i++) {
								Location pos = getAdjacentLocation(position, (FACE)i);
								calc(pos, light_level - 1);
							}
						}
					};

					calc(block, 14);
				}
			}
		}
	}
}

GLubyte BW::Chunk::getBlockLight(short x, short y, short z, FACE face) {
	if (!inBounds(x, y, z))
		throw InvalidBlockIndex(x, y, z);

	Location adj = Chunk::getAdjacentLocation({ x, y, z }, face);

	auto it = light_values.find(adj);
	if (it == light_values.end())
		return 4;

	return it->second;
}
