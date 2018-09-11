#pragma once
#include <glm/glm.hpp>

namespace BW {
	class RayTrace {
		public:
		RayTrace(float yaw, float pitch, glm::vec3 start);
		~RayTrace() = default;

		void step(float x);
		const glm::vec3& getEndpoint() const;
		float getLength() const;

		private:
		glm::vec3 origin, endpoint;
		float pitch, yaw;
	};
}

