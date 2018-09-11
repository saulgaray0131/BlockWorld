#pragma once
#include "../Misc/GLFWInput.h"

struct GLFWwindow;


namespace BW {
	class Camera;
	class GameState : public GLFWInput {
		public:
		GameState();
		virtual ~GameState();

		GameState(GameState const&) = delete;
		GameState& operator=(GameState const&) = delete;

		virtual void update(float delta, Camera& camera) = 0;
		virtual void draw() = 0;
	};
}

