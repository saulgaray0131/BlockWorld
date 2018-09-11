#include "Shader.h"

#include <fstream>
#include <string>
#include <glm\gtc\type_ptr.hpp>

BW::Shader::Shader() : program(0) {
}

BW::Shader::~Shader() {
}

void BW::Shader::compile(const std::string& frag, const std::string& vert) {
	if (program != 0) {
		std::cout << "Shader already compiled..." << std::endl;
		return;
	}

	GLuint vertexID = Shader::loadShader(vert, GL_VERTEX_SHADER),
		fragID = Shader::loadShader(frag, GL_FRAGMENT_SHADER);

	program = glCreateProgram();

	glAttachShader(program, vertexID);
	glAttachShader(program, fragID);
	glLinkProgram(program);

	GLint success = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		std::cout << frag << "-" << vert << " could not link program..." << std::endl;
		std::exit(-1);
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragID);
}

void BW::Shader::use() const {
	glUseProgram(program);
}

void BW::Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}

void BW::Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void BW::Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void BW::Shader::setMat4(const std::string& name, const glm::mat4& value) const {
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, false, glm::value_ptr(value));
}

GLuint BW::Shader::loadShader(const std::string& file, GLenum type) {
	std::ifstream ifs(file);
	std::string srsc((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	ifs.close();

	const char* src = srsc.c_str();
	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);
	
	int  success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "Shader '" << file << "' compile error:\n" << infoLog << std::endl;
		exit(-1);
	} else
		std::cout << "Shader '" << file << "' compiled successfully..." << std::endl;

	return id;
}
