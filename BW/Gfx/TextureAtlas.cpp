#include "TextureAtlas.h"
#include <stb_image.h>
#include <json.hpp>
#include <fstream>
#include <map>

BW::TextureArray::TextureArray(const std::string& file) {
	load(file);
}

BW::TextureArray::~TextureArray() {
}

unsigned char BW::TextureArray::getTextureLayer(unsigned char id) {
	return textures.at(id); //implement error texture 0
}

void BW::TextureArray::bind(GLenum target) {
	if (id != 0) {
		glActiveTexture(target);
		glBindTexture(GL_TEXTURE_2D_ARRAY, id);
	} else
		std::cout << "Image binding error '" << id << std::endl;
}

void BW::TextureArray::load(const std::string& file) { 
	std::fstream in(file);
	nlohmann::json json;
	in >> json;
	in.close();

	nlohmann::json config = json["config"], images = json["textures"];

	int layers = images.size();
	int width = config["width"], height = config["height"];
	std::cout << width << " " << height << std::endl;
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, id);

	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 4, GL_RGBA8, width, height, 256);
	
	std::cout << "Layers " << layers << std::endl;
	for (int i = 0; i < layers; i++) {
		std::string imgfile = images[i]["file"];
		imgfile = "data/textures/" + imgfile;
		int channels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(imgfile.c_str(), &width, &height, &channels, STBI_rgb_alpha);
		if (!data) {
			std::cout << "Could not load '" << imgfile << "'" <<  std::endl;
			std::terminate();
		}
	
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, layers, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
		std::cout << imgfile << std::endl;
		
	}

	

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	std::cout << "TextureArray '" << file << "' was loaded..." << std::endl;
}
