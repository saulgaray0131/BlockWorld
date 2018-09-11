#pragma once
#include <atomic>

#include "../../../GL/Mesh.h"
#include "../Block/Block.h"
#include "../../../GL/ResourceManager.h"

namespace BW {
	class ChunkGenerator;
	class ChunkManager;
	class Chunk {
		public:
		Chunk(Location& location, ChunkManager& manager);
		~Chunk();

		Chunk(Chunk const&) = delete;
		Chunk& operator=(Chunk const&) = delete;

		constexpr static int SIZE = 16;
		constexpr static int AREA = SIZE * SIZE;
		constexpr static int VOLUME = AREA * SIZE;

		void generateChunk(ChunkGenerator& generator);
		void buildMesh();
		const Mesh& getMesh();
		void generateVertices();
		bool readyToDraw();

		Block getBlock(const short x, const short y, const short z) const;
		/* Get adjacent block on FACE 'side'*/
		Block getAdjacentBlock(const short x, const short y, const short z, FACE side);
		Location getLocation();

		void setBlock(const short x, const short y, const short z, BlockType type);
	
		static TextureArray& getTextureArray();
		static Location getAdjacentLocation(Location location, FACE face);

		private:
		ChunkManager& manager;
		Location chunk_location;
		Mesh mesh;

		bool generated, mesh_ready, chunk_empty, thread_queued, rebuild_mesh;
		std::atomic<bool> ready_to_buffer;

		std::vector<GLfloat> vertices_data;
		std::vector<GLuint> indices_data;
		std::vector<GLubyte> textures_data, texcoords_data, light_data;

		std::unique_ptr<std::array<Block, Chunk::VOLUME>> block_array;
		std::unordered_map<Location, GLubyte> light_values;

		static short getBlockIndex(const short x, const short y, const short z);
		static bool inBounds(const short x, const short y, const short z);

		void loadLight();

		/* Get the light level of a block face */
		GLubyte getBlockLight(short x, short y, short z, FACE face);
	};
}

