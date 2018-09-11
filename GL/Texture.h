#pragma once
#include <glad\glad.h>
#include <string>

namespace BW {
	class Texture2D {
		public:
		Texture2D();
		~Texture2D();

		void loadTexture(const std::string& path);
		void bind(GLenum target);

		private:
		GLuint id;
	};
}

