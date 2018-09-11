#include "RayTrace.h"

BW::RayTrace::RayTrace(float yaw, float pitch, glm::vec3 start) 
	: origin(std::move(start)), endpoint(origin), yaw(glm::radians(yaw)), pitch(glm::radians(pitch))
{
}

void BW::RayTrace::step(float x) {
	endpoint.x += std::cos(yaw)   * x;
	endpoint.z += std::sin(yaw)   * x;
	endpoint.y += std::tan(pitch) * x;
}

const glm::vec3& BW::RayTrace::getEndpoint() const {
	return endpoint;
}

float BW::RayTrace::getLength() const {
	return glm::distance(origin, endpoint);
}
