#pragma once
#include <glad\glad.h>
#include "..\GL\Texture.h"
#include "..\BW\Gfx\TextureAtlas.h"
#include <unordered_map>
#include <memory>

namespace BW {
	class ResourceManager {
		public:
		ResourceManager();
		~ResourceManager();

		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;

		static ResourceManager& getInstance();

		Texture2D& loadTexture(const std::string& path);

		BW::TextureArray& loadTextureArray(const std::string & path);

		private:
		std::unordered_map<std::string, std::unique_ptr<Texture2D>> textures2D;
		std::unordered_map<std::string, std::unique_ptr<TextureArray>> texture_arrays;
	};
}

