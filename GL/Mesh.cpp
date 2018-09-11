#include "Mesh.h"

BW::Mesh::Mesh() 
	: buffers({}), vao(0)
{
}

BW::Mesh::~Mesh() {
	glDeleteVertexArrays(1, &vao);
	
	for (auto& buffer : buffers) {
		if (buffer != 0)
			glDeleteBuffers(1, &buffer);
	}
}

void BW::Mesh::buffer(const f_vec& data, Attrib attrib, GLint attrib_size, bool normalize) {
	if (vao == 0)
		glGenVertexArrays(1, &vao);

	if (buffers[(int) attrib] == 0)
		glGenBuffers(1, &buffers[(int) attrib]);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[(int)attrib]);

	// Buffer data into 'attrib' buffer and enable the attrib index
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)attrib, attrib_size, GL_FLOAT, normalize, attrib_size * sizeof(GLfloat), 0);
	glEnableVertexAttribArray((GLuint)attrib);
}

void BW::Mesh::buffer(const ub_vec& data, Attrib attrib, GLint attrib_size, bool normalize) {
	if (vao == 0)
		glGenVertexArrays(1, &vao);

	if (buffers[(int)attrib] == 0)
		glGenBuffers(1, &buffers[(int)attrib]);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[(int)attrib]);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLubyte), data.data(), GL_STATIC_DRAW);
	//
	if (normalize)
		glVertexAttribPointer((GLuint)attrib, attrib_size, GL_UNSIGNED_BYTE, GL_TRUE, attrib_size * sizeof(GLubyte), 0);
	else
		glVertexAttribIPointer((GLuint)attrib, attrib_size, GL_UNSIGNED_BYTE, attrib_size * sizeof(GLubyte), 0);
	glEnableVertexAttribArray((GLuint)attrib);
}

void BW::Mesh::buffer(const ui_vec& data, Attrib attrib, GLint attrib_size) {
	if (vao == 0)
		glGenVertexArrays(1, &vao);

	if (buffers[(int)attrib] == 0)
		glGenBuffers(1, &buffers[(int)attrib]);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[(int)attrib]);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLuint), data.data(), GL_STATIC_DRAW);
	glVertexAttribIPointer((GLuint)attrib, attrib_size, GL_UNSIGNED_INT, attrib_size * sizeof(GLuint), 0);
	glEnableVertexAttribArray((GLuint)attrib);
}

void BW::Mesh::bufferIndices(const ui_vec& data) {
	if (vao == 0)
		glGenVertexArrays(1, &vao);

	if (buffers[(int)Attrib::INDICES] == 0)
		glGenBuffers(1, &buffers[(int)Attrib::INDICES]);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[(int)Attrib::INDICES]);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), data.data(), GL_STATIC_DRAW);

	vertex_count = (GLsizei)data.size();
}

void BW::Mesh::setVertexCount(const GLuint count) {
	vertex_count = count;
}

void BW::Mesh::bind() const {
	glBindVertexArray(vao);
}

GLsizei BW::Mesh::getVertexCount() const {
	return vertex_count;
}