#pragma once
#include <iostream>
#include <unordered_map>
#include <glad\glad.h>

namespace BW {
	class TextureArray {
		public:
		TextureArray(const std::string& file);
		~TextureArray();

		TextureArray(TextureArray const&) = delete;
		TextureArray& operator=(TextureArray const&) = delete;

		unsigned char getTextureLayer(unsigned char id);
		void bind(GLenum target);

		private:
		GLuint id;
		std::unordered_map<short, GLubyte> textures;

		void load(const std::string& file);
	};
}

