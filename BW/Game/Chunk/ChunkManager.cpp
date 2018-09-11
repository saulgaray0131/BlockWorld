#include "ChunkManager.h"

BW::ChunkManager::ChunkManager() : thread_pool(std::thread::hardware_concurrency() - 1) {
	
}

BW::ChunkManager::~ChunkManager() {
}

std::vector<BW::Chunk*> BW::ChunkManager::getNearbyChunks(Location location, int radius) {
	std::vector<BW::Chunk*> nearbyChunks;//opt reserve()
	Location center = toChunkLocation(location);

	for (short x = -radius; x <= radius; ++x) {
		short xr = (int)std::sqrt(radius * radius - x * x);
		for (short y = -10; y <= 10; ++y)
			for (short z = -xr; z <= xr; ++z) {
				Location chunk_location{ x , y, z };
				chunk_location += center;

				if (chunk_location.y < 0 || chunk_location.y > 20)
					break;

				nearbyChunks.push_back(&getChunk(chunk_location));
			}
	}
	
	return nearbyChunks;
}

bool BW::ChunkManager::chunkExists(Location& location) {
	return chunks.find(location) != chunks.end();
}

BW::Chunk& BW::ChunkManager::getChunk(Location& location) {
	writing_map.lock();

	auto it = chunks.find(location);
	if (it == chunks.end()) {
		Chunk* chunk = new Chunk(location, *this);
		chunks.emplace(location, chunk);
		chunk->generateChunk(generator);

		writing_map.unlock();
		return *chunk;
	}

	writing_map.unlock();
	return *it->second;
}

BW::Location BW::ChunkManager::toChunkLocation(Location& location) {
	Location chunk_location;
	chunk_location.x = location.x >> 4;
	chunk_location.y = location.y >> 4;
	chunk_location.z = location.z >> 4;

	return chunk_location;
}

BW::Block BW::ChunkManager::getBlock(Location& block) {
	Location chunk_location = toChunkLocation(block);

	return getChunk(chunk_location).getBlock(block.x - chunk_location.x * Chunk::SIZE, block.y - chunk_location.y * Chunk::SIZE, block.z - chunk_location.z * Chunk::SIZE);
}

void BW::ChunkManager::setBlock(Location& location, BlockType type) {
	Location chunk_location = toChunkLocation(location);

	return getChunk(chunk_location).setBlock(location.x - chunk_location.x * Chunk::SIZE, location.y - chunk_location.y * Chunk::SIZE, location.z - chunk_location.z * Chunk::SIZE, type);
}

BW::ChunkGenerator& BW::ChunkManager::getChunkGenerator() {
	return generator;
}

ctpl::thread_pool& BW::ChunkManager::getThreadPool() {
	return thread_pool;
}

