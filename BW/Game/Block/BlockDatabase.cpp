#include "BlockDatabase.h"
#include <json.hpp>
#include <fstream>
#include <iostream>


BW::BlockData::BlockData(BlockType id) {
	type = id;
	lightSource = false;
}

bool BW::BlockData::isOpaque() const {
	return opaque;
}

bool BW::BlockData::isLightSource() const {
	return lightSource;
}

unsigned char BW::BlockData::getLightLevel() const {
	return lightLevel;
}

GLubyte BW::BlockData::getTexture(FACE face) const {
	GLubyte texture = 0;

	switch (face) {
		case BW::NORTH: texture = tNorth;
			break;
		case BW::SOUTH:	texture = tSouth;
			break;
		case BW::EAST:	texture = tEast;
			break;
		case BW::WEST:	texture = tWest;
			break;
		case BW::TOP:	texture = tTop;
			break;
		case BW::BOTTOM:texture = tBottom;
			break;
	}
	return texture;
}

BW::BlockDatabase::BlockDatabase(const std::string& file) {
	block_types.emplace_back(nullptr); //air block
	loadFromFile(file);
	std::cout << "Block DB loaded..." << std::endl;
}

BW::BlockDatabase::~BlockDatabase() {
}

BW::BlockDatabase& BW::BlockDatabase::getInstance() {
	static BlockDatabase db("data/blocks.json");
	return db;
}

const BW::BlockData* BW::BlockDatabase::getBlockData(BlockType id) {
	return block_types.at(id).get();
}

void BW::BlockDatabase::loadFromFile(const std::string& file) {
	std::fstream stream(file);
	nlohmann::json json;
	stream >> json;
	stream.close();

	nlohmann::json blocks = json["blocks"], textures;
	stream = std::fstream("data/textures/textures.json");
	stream >> json;
	stream.close();
	textures = json["textures"];

	std::map<std::string, unsigned char> tMap;
	for (unsigned char i = 0; i < textures.size(); i++) {
		std::string name = textures[i]["name"];
		tMap.emplace(name, i);
	}

	for (unsigned char i = 0; i < blocks.size(); i++) {
		BlockType id = blocks[i]["id"];
		BlockData* block = new BlockData(id);

		auto it = blocks[i].find("texture-all");
		if (it != blocks[i].end()) {
			unsigned char id = tMap.at(*it);
			block->tNorth = id;
			block->tSouth = id;
			block->tEast = id;
			block->tWest = id;
			block->tTop = id;
			block->tBottom = id;
		}

		it = blocks[i].find("texture-north");
		if (it != blocks[i].end())
			block->tNorth = tMap.at(*it);

		it = blocks[i].find("texture-south");
		if (it != blocks[i].end())
			block->tSouth = tMap.at(*it);

		it = blocks[i].find("texture-east");
		if (it != blocks[i].end())
			block->tEast = tMap.at(*it);

		it = blocks[i].find("texture-west");
		if (it != blocks[i].end())
			block->tWest = tMap.at(*it);

		it = blocks[i].find("texture-top");
		if (it != blocks[i].end())
			block->tTop = tMap.at(*it);

		it = blocks[i].find("texture-bottom");
		if (it != blocks[i].end())
			block->tBottom = tMap.at(*it);

		block->opaque = blocks[i]["opaque"];
		it = blocks[i].find("light-source");
		if (it != blocks[i].end())
			block->lightSource = *it;
		if (block->lightSource)
			block->lightLevel = blocks[i]["light-level"];

		block_types.emplace_back(block);
	}
}
