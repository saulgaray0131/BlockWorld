 #pragma once
#include "GameState.h"
#include "../Gfx/Renderer.h"
#include "../Game/World/World.h"
#include "../Misc/Timer.h"

namespace BW {
	class CrossHair {
		public:
		CrossHair();
		~CrossHair();

		Mesh mesh;
		Shader shader;
		Texture2D texture;
	};

	class PlayingState : public GameState {
		public:
		PlayingState(int width, int height, Camera& camera);
		~PlayingState();

		void update(float delta, Camera& camera) override;
		void draw() override;

		virtual void keyCallback(int key, int action, int mods) override;
		virtual void mouseButtonCallback(int button, int action, int mods) override;
		virtual void mouseMoveCallback(double x, double y) override;

		private:
		Renderer renderer;
		World world;

		Timer input_tick, draw_tick;
		bool in;

		CrossHair hr;
	};
}

