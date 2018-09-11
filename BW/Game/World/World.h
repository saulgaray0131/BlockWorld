#pragma once
#include "../Chunk/ChunkManager.h"
#include "../Entity/Player.h"
#include "../../Misc/GLFWInput.h"

namespace BW {
	class Renderer;
	class Camera;

	class World : public GLFWInput {
		public:
		World(Renderer& renderer);
		~World();

		World(World const&) = delete;
		World& operator=(World const&) = delete;

		void update(Camera& camera);
		void draw();

		// Inherited via GLFWInput
		virtual void keyCallback(int key, int action, int mods) override;
		virtual void mouseButtonCallback(int button, int action, int mods) override;
		virtual void mouseMoveCallback(double x, double y) override;

		private:
		ChunkManager chunk_mgr;
		Renderer& renderer;

		Player player;

		bool breaking, updateCamera;
	};
}

