#pragma once
#include <glad\glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <array>

namespace BW {

	//Short hand
	using f_vec = std::vector<GLfloat>;
	using ub_vec = std::vector<GLubyte>;
	using ui_vec = std::vector<GLuint>;

	enum class Attrib : GLuint {
		POSITION = 0, TEXTURE = 1, UVS = 2, LIGHTING = 3, INDICES = 4,
		Count
	};

	class Mesh {
		public:
		Mesh();
		~Mesh();

		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		void buffer(const f_vec& data, Attrib attrib, GLint attrib_size, bool normalize = false);
		void buffer(const ub_vec& data, Attrib attrib, GLint attrib_size, bool normalize = false);
		void buffer(const ui_vec& data, Attrib attrib, GLint attrib_size);
		void bufferIndices(const ui_vec& data);
		void setVertexCount(const GLuint count);

		void bind() const;
		GLsizei getVertexCount() const;

		private:
		GLuint vao;
		std::array<GLuint, (std::size_t)Attrib::Count> buffers;

		GLsizei vertex_count;
	};
}

