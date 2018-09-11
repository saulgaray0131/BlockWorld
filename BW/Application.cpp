#include "Application.h"
#include <glad\glad.h>
#include "State\PlayingState.h"
#include "Misc\Timer.h"

BW::Application::Application()
{
}


BW::Application::~Application() {
}

void BW::Application::start(Config& config) {
	this->config = config;
	init();

	Timer timer;
	double last_frame = timer.getTime();

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		double delta = timer.getTime() - last_frame;
		last_frame = timer.getTime();

		camera.processInput(window, delta);

		states.top()->update(delta, camera);
		states.top()->draw();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glfwSwapBuffers(window);

		GLenum err = glGetError();
		while (err != GL_NO_ERROR) {
			std::cout << err << std::endl;
			err = glGetError();
		}
	}
}

void BW::Application::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, false);

	window = glfwCreateWindow(config.width, config.height, config.title.c_str(), NULL/*glfwGetPrimaryMonitor()*/, NULL);
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowUserPointer(window, this);
	glfwSwapInterval(0);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, config.width, config.height);
	glClearColor(118 / 256.f, 157 / 256.f, 219 / 256.f, 1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_STENCIL_TEST);
	//glStencilFunc(GL_EQUAL, 1, 0xFF);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
		auto app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		app->mouseMoveCallback(x, y);
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int modifiers) {
		auto app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		app->mouseButtonCallback(button, action, modifiers);
	});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		auto app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		app->keyCallback(key, action, mods);
	});

	glfwSetScrollCallback(window, [](GLFWwindow* window, double x, double y) {
		
	});

	states.emplace(new PlayingState(config.width, config.height, camera));
}

void BW::Application::keyCallback(int key, int action, int mods) {
	states.top()->keyCallback(key, action, mods);
}

void BW::Application::mouseButtonCallback(int button, int action, int mods) {
	states.top()->mouseButtonCallback(button, action, mods);
}

void BW::Application::mouseMoveCallback(double xpos, double ypos) {
	camera.processMouse(xpos, ypos);
	states.top()->mouseMoveCallback(xpos, ypos);
}
