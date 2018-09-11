#pragma once
#include "../Block/Block.h"
#include <FastNoise.h>

namespace BW {
	class Chunk;
	class ChunkGenerator {
		public:
		ChunkGenerator();
		virtual ~ChunkGenerator();

		ChunkGenerator(ChunkGenerator const&) = delete;
		ChunkGenerator& operator=(ChunkGenerator const&) = delete;

		virtual void generateChunk(Chunk& chunk) = 0;
	};

	class SimpleGenerator : public ChunkGenerator {
		public:
		SimpleGenerator();

		virtual void generateChunk(Chunk& chunk) override;

		private:
		FastNoise noise1, noise2, noise3;
		const static double e;
	};
}

