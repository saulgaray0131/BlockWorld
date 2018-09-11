#pragma once
#include <glad\glad.h>
#include "Block.h"
#include <string>
#include <memory>
#include <vector>

namespace BW {
	class BlockData {
		public:
		BlockData(BlockType id);
		~BlockData() = default;

		friend class BlockDatabase;

		GLubyte getTexture(FACE face) const;
		bool isOpaque() const;
		bool isLightSource() const;
		unsigned char getLightLevel() const;

		protected:
		BlockType type;

		//Texture id's
		GLubyte tNorth, tSouth;
		GLubyte tEast, tWest;
		GLubyte tTop, tBottom;

		//Block properties
		bool opaque;

		bool lightSource;
		unsigned char lightLevel; //Only if is light source
	};

	class BlockDatabase {
		public:
		~BlockDatabase();

		BlockDatabase(BlockDatabase const&) = delete;
		BlockDatabase& operator=(BlockDatabase const&) = delete;

		static BlockDatabase& getInstance();

		const BlockData* getBlockData(BlockType id);

		private:
		std::vector<std::unique_ptr<BlockData>> block_types;
		BlockDatabase(const std::string& file);

		void loadFromFile(const std::string& file);
	};
}

