#pragma once
#include "Chunk.h"
#include "ChunkGenerator.h"
#include <ctpl_stl.h>


namespace BW {
	class ChunkManager {
		public:
		ChunkManager();
		~ChunkManager();

		ChunkManager(ChunkManager const&) = delete;
		ChunkManager& operator=(ChunkManager const&) = delete;

		std::vector<Chunk*> getNearbyChunks(Location location, int chunkRadius);

		bool chunkExists(Location& location);

		/* Get chunk nearest to location*/
		Chunk& getChunk(Location& location);
		
		Location toChunkLocation(Location& location);

		Block getBlock(Location& location);
		void setBlock(Location& location, BlockType type);

		ChunkGenerator& getChunkGenerator();
		ctpl::thread_pool& getThreadPool();

		private:
		SimpleGenerator generator;
		std::unordered_map<Location, std::unique_ptr<Chunk>> chunks;
		ctpl::thread_pool thread_pool;

		std::mutex writing_map;
	};
}

