#include "PlayingState.h"
#include "../Game/Block/BlockDatabase.h"
#include <GLFW\glfw3.h>

BW::PlayingState::PlayingState(int width, int height, Camera& camera)
	: renderer(width, height, camera), world(renderer), hr()
{

}

BW::PlayingState::~PlayingState() {
}

void BW::PlayingState::update(float delta, Camera& camera) {
	if (input_tick.getTime() >= (1.0 / 60.0)) {
		if(!in)
			world.update(camera);

		input_tick.reset();
	}
}

void BW::PlayingState::draw() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		world.draw();
		renderer.renderOrtho(hr.shader, hr.mesh, hr.texture);
		renderer.drawDebugMeshes();
}

void BW::PlayingState::keyCallback(int key, int action, int mods) {
	world.keyCallback(key, action, mods);

	if (key == GLFW_KEY_X)
		renderer.clearDebugMeshes();
}

void BW::PlayingState::mouseButtonCallback(int button, int action, int mods) {
	world.mouseButtonCallback(button, action, mods);
}

void BW::PlayingState::mouseMoveCallback(double x, double y) {
	world.mouseMoveCallback(x, y);
}

BW::CrossHair::CrossHair() {
	f_vec pos = { 0, 25, 0,  25, 25, 0,  0, 0, 0,    25, 25, 0,  25, 0, 0,  0, 0, 0 };
	ub_vec uvs = { 0,255,  255,255, 0,0,   255,255, 255,0, 0,0 };
	ui_vec i = { 0,1,2,3,4,5 };

	mesh.bufferIndices(i);
	mesh.buffer(pos, Attrib::POSITION, 3);
	mesh.buffer(uvs, Attrib::UVS, 2, true);

	texture = ResourceManager::getInstance().loadTexture("data/textures/crosshair.png");

	shader.compile("shaders/crosshair.frag", "shaders/crosshair.vert");
}

BW::CrossHair::~CrossHair() {
}