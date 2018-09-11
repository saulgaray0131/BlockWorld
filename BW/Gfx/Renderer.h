#pragma once
#include "../Camera.h"
#include "../Game/Chunk/Chunk.h"
#include "../../GL/Shader.h"

namespace BW {
	class Renderer {
		public:
		Renderer(int width, int height, Camera& camera);
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

		void renderChunk(Chunk& chunk);
		void renderChunk(Chunk* chunk);
		void renderChunks(std::vector<Chunk*>& chunks);

		void renderOrtho(Shader& shader, Mesh& mesh, Texture2D& texture);

		/* Debug functions*/
		void renderLine(glm::vec3 origin, double length);
		void renderLine(glm::vec3 origin, glm::vec3 endpoint);

		void drawDebugMeshes();
		void clearDebugMeshes();

		private:
		Camera& camera;
		glm::mat4 perspective, ortho;

		Shader block_shader;
		Shader simple;
		std::vector<std::unique_ptr<Mesh>> debug_meshes;
	};
}

