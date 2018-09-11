#include "Timer.h"

#include <GLFW\glfw3.h>

BW::Timer::Timer() {
	reset();
}

BW::Timer::~Timer() {
}

void BW::Timer::reset() {
	start_time = glfwGetTime();
}

double BW::Timer::getTime() {
	return glfwGetTime() - start_time;
}
