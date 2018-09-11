#include "World.h"
#include <GLFW/glfw3.h>
#include "../../Gfx/Renderer.h"
#include "../../Camera.h"
#include "../../Physics/RayTrace.h"

BW::World::World(Renderer& renderer) : renderer(renderer) {
	breaking = false;
	updateCamera = true;
}

BW::World::~World() {
}

void BW::World::update(Camera& camera) {
	if(updateCamera)
	player.updatePosition(camera);

	if (breaking) {
		player.updatePosition(camera);
		RayTrace ray(camera.getYaw(), camera.getPitch(), player.getPosition());

		while (ray.getLength() < 4.0f) {
			ray.step(0.01);
			Location x = ray.getEndpoint();

			if (chunk_mgr.getBlock(x).type != AIR) {
				chunk_mgr.setBlock(x, AIR);
				renderer.renderLine(player.getPosition(), ray.getEndpoint());

				break;
			}
		}
	}
}

void BW::World::draw() {
	std::vector<Chunk*> chunks = chunk_mgr.getNearbyChunks(player.getPosition(), 10);
	renderer.renderChunks(chunks);

	/*for (auto it = chunks.begin(); it != chunks.end(); it++) {
		Location chunk = (*it)->getLocation();

		//glm::vec3 AB = (chunk * Chunk::SIZE) - player_position;
		//if (glm::dot(AB, front) > 0)
		renderer.renderChunk(*it);
	}

	for (int dist = 0; dist < 12; dist++) {
		Location x = player_position + static_cast<Location>(front * (dist / 2.0f));

		if (chunk_mgr.getBlock(x).type != AIR) {
			chunk_mgr.setBlock(x, AIR);
			break;
		}
	}*/
}

void BW::World::keyCallback(int key, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_C)
			updateCamera = !updateCamera;

	} else if (action == GLFW_RELEASE) {

	}
}

void BW::World::mouseButtonCallback(int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_1)
			breaking = true;

	} else if (action == GLFW_RELEASE) {
		if (button == GLFW_MOUSE_BUTTON_1)
			breaking = false;
	}
}

void BW::World::mouseMoveCallback(double x, double y) {
}
