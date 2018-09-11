#pragma once
#include <glm\glm.hpp>

struct GLFWwindow;
namespace BW {
	class Camera {
		public:
		Camera();
		~Camera();

		Camera(const Camera&) = delete;

		void processInput(GLFWwindow* window, float delta);
		void processMouse(double xpos, double ypos);
		glm::mat4 getViewMatrix();

		glm::vec3& getPosition();
		glm::vec3& getFront();

		float getYaw() const;
		float getPitch() const;

		private:
		const glm::vec3 worldUp;

		glm::vec3 position;
		glm::vec3 right, up, front;
		glm::mat4 view;

		float yaw, pitch;

		float speed;
		float sensitivity;

		double last_x, last_y;
		bool first;

		void update();
	};
}

