#pragma once
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <iostream>

namespace BW {
	class Shader {
		public:
		Shader();
		~Shader();

		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		void compile(const std::string& frag, const std::string& vert);
		void use() const;

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setMat4(const std::string& name, const glm::mat4& value) const;

		private:
		GLuint program;
		static GLuint loadShader(const std::string& file, GLenum type);
	};
}

