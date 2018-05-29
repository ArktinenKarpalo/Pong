#pragma once
#include <glm/glm.hpp>
#include "../graphics/Rectangle.h"
#include "../graphics/Shader.h"

class Player {
	public:
		Player(glm::vec3, glm::vec2, float, Shader*);
		Rectangle* getRectangle();
		void update(float);
		void setPosition(glm::vec3);
		glm::vec3 getPosition();
		glm::vec2 getSize();
		void move(int);
		void setSpeed(float);
		int getDirection();
	private:
		Rectangle* rectangle;
		glm::vec3 position;
		glm::vec2 size;
		float speed;
		int moveDirection, lowerBound=0, upperBound=600;
};