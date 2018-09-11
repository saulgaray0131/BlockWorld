#pragma once
#include <glm\glm.hpp>
#include <glad\glad.h>
#include <array>

namespace BW {
	enum BlockType : unsigned char {
		AIR = 0,
		DIRT = 1,
		GRASS = 2,
		STONE = 3,
		DEBUGLAMP = 4
	};

	struct Block {
		Block() = default;

		BlockType type;
	};

	typedef glm::ivec3 Location;

	struct _blockface {
		struct _uvs {
			GLubyte x, y;
		};

		std::array<glm::vec4, 4> vertices;
		std::array<_uvs, 4> uvs;
	};

	enum FACE : char {
		NORTH = 0,
		SOUTH = 1,
		EAST = 2,
		WEST = 3,
		TOP = 4,
		BOTTOM = 5,

		SIZE = 6
	};

	extern const std::array<_blockface, 6> VERTICES;
	extern const std::array<GLuint, 6> INDICES;
}

namespace std {
	template<>
	struct hash<BW::Location> {
		inline size_t operator()(const BW::Location& k) const {
			return std::hash<int>()(k.x) ^ std::hash<int>()(k.y) ^ std::hash<int>()(k.z);
		}
	};
}