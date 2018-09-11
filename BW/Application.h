#pragma once
#include <GLFW\glfw3.h>
#include <iostream>
#include <stack>
#include <memory>

#include "State\GameState.h"
#include "Camera.h"

namespace BW {
	class Application : public GLFWInput {
		public:
		Application();
		~Application();

		Application(Application const&) = delete;
		Application& operator=(Application const&) = delete;

		struct Config {
			int height, width;
			std::string title;
		};
		
		void start(Config& config);

		private:
		GLFWwindow* window;
		Config config;

		Camera camera;
		std::stack<std::unique_ptr<GameState>> states;

		void init();
		void keyCallback(int key, int action, int mods) override;
		void mouseButtonCallback(int button, int action, int mods) override;
		void mouseMoveCallback(double x, double y) override;
	};
}

