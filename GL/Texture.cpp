#include "Texture.h"

#include <stb_image.h>
#include <iostream>

BW::Texture2D::Texture2D() : id(0) {

}

BW::Texture2D::~Texture2D() {
}

void BW::Texture2D::loadTexture(const std::string& path) {
	int w, h, ch;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &w, &h, &ch, STBI_rgb_alpha);
	std::cout << ch << std::endl;
	if (!data) {
		std::cout << "Could not load image:" << path << std::endl;
		throw "Error";
	}

	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void BW::Texture2D::bind(GLenum target) {
	if (id != 0) {
		glActiveTexture(target);
		glBindTexture(GL_TEXTURE_2D, id);
	} else
		std::cout << "Image binding error '" << id << std::endl;
}
