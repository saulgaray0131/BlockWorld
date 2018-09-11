#include "Renderer.h"

#include <glm\gtc\matrix_transform.hpp>

BW::Renderer::Renderer(int width, int height, Camera& camera) : camera(camera) {
	block_shader.compile("shaders/block.frag", "shaders/block.vert");
	simple.compile("shaders/simple.frag", "shaders/simple.vert");

	perspective = glm::perspective(glm::radians(90.0f), (float)width / height, 0.1f, 5000.0f);
	ortho = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 100.f);
	ortho = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.0f, 1.f);
}

BW::Renderer::~Renderer() {
}

void BW::Renderer::renderChunk(Chunk& chunk) {
	renderChunk(&chunk);
}

void BW::Renderer::renderChunk(Chunk* chunk) {
	if (chunk->readyToDraw()) {
		const Mesh& mesh = chunk->getMesh();

		mesh.bind();
		Chunk::getTextureArray().bind(GL_TEXTURE0);
		block_shader.use();

		block_shader.setMat4("projection", perspective);
		block_shader.setMat4("view", camera.getViewMatrix());

		glDrawElements(GL_TRIANGLES, mesh.getVertexCount(), GL_UNSIGNED_INT, NULL);
	}
}

void BW::Renderer::renderChunks(std::vector<Chunk*>& chunks) {
	Chunk::getTextureArray().bind(GL_TEXTURE0);
	block_shader.use();

	block_shader.setMat4("projection", perspective);
	block_shader.setMat4("view", camera.getViewMatrix());

	for (auto it = chunks.begin(); it != chunks.end(); ++it) {
		if ((*it)->readyToDraw()) {
			const Mesh& mesh = (*it)->getMesh();
			mesh.bind();

			glDrawElements(GL_TRIANGLES, mesh.getVertexCount(), GL_UNSIGNED_INT, NULL);
		}
	}
}

void BW::Renderer::renderOrtho(Shader& shader, Mesh& mesh, Texture2D& texture) {
	shader.use();
	mesh.bind();
	texture.bind(GL_TEXTURE0);
	shader.setMat4("ortho", ortho);
	
	glDrawElements(GL_TRIANGLES, mesh.getVertexCount(), GL_UNSIGNED_INT, NULL);
}

void BW::Renderer::renderLine(glm::vec3 origin, double length) {
	Mesh* mesh = new Mesh();

	f_vec pos = { origin.x, origin.y, origin.z };
	origin += length;
	pos.insert(pos.end(), { origin.x, origin.y, origin.z });

	mesh->buffer(pos, Attrib::POSITION, 3);

	debug_meshes.emplace_back(mesh);
}

void BW::Renderer::renderLine(glm::vec3 origin, glm::vec3 endpoint) {
	Mesh* mesh = new Mesh();

	f_vec pos{ origin.x, origin.y, origin.z, endpoint.x, endpoint.y, endpoint.z };

	mesh->buffer(pos, Attrib::POSITION, 3);
	mesh->setVertexCount(pos.size() / 3);

	debug_meshes.emplace_back(mesh);
}

void BW::Renderer::drawDebugMeshes() {
	simple.use();
	simple.setMat4("projection", perspective);
	simple.setMat4("view", camera.getViewMatrix());

	for (auto& mesh : debug_meshes) {
		mesh->bind();
		glDrawArrays(GL_LINES, 0, mesh->getVertexCount());
	}
}

void BW::Renderer::clearDebugMeshes() {
	debug_meshes.clear();
}
