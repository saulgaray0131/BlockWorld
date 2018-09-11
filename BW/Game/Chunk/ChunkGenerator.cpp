#include "ChunkGenerator.h"
#include "Chunk.h"

BW::ChunkGenerator::ChunkGenerator() {
	
}

BW::ChunkGenerator::~ChunkGenerator() {
}

const double BW::SimpleGenerator::e = std::exp(1.0);

BW::SimpleGenerator::SimpleGenerator() {
	noise1.SetSeed(98612349861249861);
	noise1.SetNoiseType(FastNoise::SimplexFractal);
	noise1.SetFrequency(.002);
	noise1.SetFractalOctaves(4);
	noise1.SetFractalLacunarity(4.0);
	noise1.SetFractalGain(.2);
}

void BW::SimpleGenerator::generateChunk(Chunk& chunk) {
	Location loc = chunk.getLocation();
	loc *= Chunk::SIZE;

	for (short x = 0; x < Chunk::SIZE; ++x) {
		for (short z = 0; z < Chunk::SIZE; ++z) {
			float height = noise1.GetNoise(loc.x + x, loc.z + z) / 2 + 0.5;
			height = std::pow(height, .3);

			for (short y = 0; y < Chunk::SIZE; ++y) {
				short world_height = height * 255;
				if (world_height >= loc.y + y) {

					if(std::rand() % 10000 == 1)
						chunk.setBlock(x, y, z, DEBUGLAMP);
					else if (world_height == loc.y + y)
						chunk.setBlock(x, y, z, GRASS);
					else if (loc.y + y < world_height && loc.y + y >= world_height - 3)
						chunk.setBlock(x, y, z, DIRT);
					else
						chunk.setBlock(x, y, z, STONE);
				}
			}
		}
	}
}
