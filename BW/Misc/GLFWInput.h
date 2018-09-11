#pragma once

namespace BW {
	class GLFWInput {
		public:
		virtual void keyCallback(int key, int action, int mods) = 0;
		virtual void mouseButtonCallback(int button, int action, int mods) = 0;
		virtual void mouseMoveCallback(double x, double y) = 0;
	};
}
