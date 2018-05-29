#pragma once
#include <glm/glm.hpp>
#include "../graphics/Circle.h"
#include "../graphics/Shader.h"

class Ball {
	public:
		Ball(float, float, Shader*);
		Circle* getCircle();
		void update(float);
		void setVelocity(glm::vec3);
		void setPosition(glm::vec3);
		glm::vec3 getPosition();
		void reset();
	private:
		Circle* circle;
		float radius, speed;
		glm::vec3 position, velocity;
		int upperBound=600, lowerBound=0, leftBound=0, rightBound=800;
};