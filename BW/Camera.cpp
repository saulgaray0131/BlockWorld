#include "Camera.h"
#include <GLFW\glfw3.h>
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>

BW::Camera::Camera() : position(0, 200, 0), worldUp(0.0, 1.0, 0.0), up(worldUp), yaw(-90), pitch(-35) {

	sensitivity = .2;
	speed = 14;

	first = true;

	update();
}

BW::Camera::~Camera() {
}

void BW::Camera::processInput(GLFWwindow* window, float delta) {
	static bool s = false;
	float cameraSpeed = delta * speed;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += cameraSpeed * front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= cameraSpeed * front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += glm::normalize(glm::cross(front, up)) * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && !s) {
		std::cout << "X:" << position.x << " Y:" << position.y << " Z:" << position.z << std::endl;
		s = true;
	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE) {
		s = false;
	}
}

void BW::Camera::processMouse(double xpos, double ypos) {
	if (first) {
		last_x = xpos; last_y = ypos;
		first = false;
	}

	double xoffset = last_x - xpos, yoffset = last_y - ypos;
	last_x = xpos; last_y = ypos;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw -= xoffset;
	pitch += yoffset;

	if (pitch > 89)
		pitch = 89;
	else if (pitch < -89)
		pitch = -89;

	update();
}

glm::mat4 BW::Camera::getViewMatrix() {
	return glm::lookAt(position, position + front, up);
}

glm::vec3& BW::Camera::getPosition() {
	return position;
}

glm::vec3& BW::Camera::getFront() {
	update();
	return front;
}

float BW::Camera::getYaw() const {
	return yaw;
}

float BW::Camera::getPitch() const {
	return pitch;
}

void BW::Camera::update() {
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}
