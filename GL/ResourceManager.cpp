#include "ResourceManager.h"

BW::ResourceManager::ResourceManager() {
}

BW::ResourceManager::~ResourceManager() {
}

BW::ResourceManager& BW::ResourceManager::getInstance() {
	static ResourceManager mgr;
	return mgr;
}

BW::Texture2D& BW::ResourceManager::loadTexture(const std::string& path) {
	auto it = textures2D.find(path);

	if (it != textures2D.end())
		return *it->second;

	Texture2D* texture = new Texture2D();
	texture->loadTexture(path);

	textures2D.insert(std::make_pair(path, texture));
	return *texture;
}

BW::TextureArray& BW::ResourceManager::loadTextureArray(const std::string& path) {
	auto it = texture_arrays.find(path);
	if (it != texture_arrays.end())
		return *it->second;

	TextureArray* array = new TextureArray(path);

	texture_arrays.emplace(path, array);
	return *array;
}
