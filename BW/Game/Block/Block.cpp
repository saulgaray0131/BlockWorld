#include "Block.h"

namespace BW {
	const std::array<GLuint, 6> INDICES = {
		1, 2, 0, 3, 2, 1
	};

	const std::array<_blockface, 6> VERTICES = {
		_blockface { { //NORTHFACE
				glm::vec4(-0.5f,  0.5f, 0.5f, 1.0f),  // Top left
				glm::vec4(0.5f,  0.5f,  0.5f, 1.0f), // Top right
				glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f),  // Bottom left
				glm::vec4(0.5f, -0.5f,  0.5f, 1.0f)},  // Bottom right
	            {{ {0,255}, {255,255}, {0,0}, {255, 0} }}},
		_blockface { { //SOUTHFACE
				glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f), // Bottom left
				glm::vec4(0.5f, -0.5f,  -0.5f, 1.0f), // Bottom right
				glm::vec4(-0.5f,  0.5f, -0.5f, 1.0f), // Top left
				glm::vec4(0.5f,  0.5f, -0.5f, 1.0f)}, // Top right
				{{ { 0,0 },{ 255,0 },{ 0,255 },{ 255, 255 } }}},
		_blockface { { //EASTFACE
				glm::vec4(0.5f, -0.5f, -0.5f, 1.0f),  // Bottom left
				glm::vec4(0.5f, -0.5f,  0.5f, 1.0f),  // Bottom right
				glm::vec4(0.5f,  0.5f, -0.5f, 1.0f),  // Top left
				glm::vec4(0.5f,  0.5f,  0.5f, 1.0f)}, // Top right
	            {{ { 0,0 },{ 255,0 },{ 0,255 },{ 255, 255 } }}},
		_blockface { { //WESTFACE
				glm::vec4(-0.5f, -0.5f,  0.5f, 1.0f), // Bottom left
				glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f), // Bottom Right
				glm::vec4(-0.5f,  0.5f,  0.5f, 1.0f), // Top left
				glm::vec4(-0.5f,  0.5f, -0.5f, 1.0f)},// Top right
	            {{ { 0,0 },{ 255,0 },{ 0,255 },{ 255, 255 } }}},
		_blockface { { //TOPFACE !?!
				glm::vec4(-0.5f,  0.5f, -0.5f, 1.0f), // Bottom left
				glm::vec4(0.5f,   0.5f, -0.5f, 1.0f), // Bottom right
				glm::vec4(-0.5f,  0.5f,  0.5f, 1.0f), // Top left
				glm::vec4(0.5f,   0.5f,  0.5f, 1.0f)},// Top right
	            {{ { 0,0 },{ 255,0 },{ 0,255 },{ 255, 255 } }}},
		_blockface { { //BOTTOMFACE
				glm::vec4(-0.5f, -0.5f,  0.5f, 1.0f), // Bottom left
				glm::vec4(0.5f, -0.5f,   0.5f, 1.0f), // Bottom right
				glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f), // Top left
				glm::vec4(0.5f, -0.5f,  -0.5f, 1.0f)},// Top right
	            {{ { 0,0 },{ 255,0 },{ 0,255 },{ 255, 255 } }}}
	};
}