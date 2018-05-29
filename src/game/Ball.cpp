#include "Ball.h"
#include "Player.h"
#include "../Utils.h"
#include "../graphics/Text.h"

Ball::Ball(float radius, float speed, Shader* shader) {
	this->radius = radius;
	this->speed = speed;
	circle = new Circle(glm::vec3(400.0f, 300.0f, 0.0f), radius, shader);
	(*circle).initDraw();
}

void Ball::update(float deltaTime) {
	extern Player *player1, *player2;
	extern Text *player1Score, *player2Score;
	position += velocity*deltaTime;
	
	if(position.y+radius >= upperBound) {
		velocity.y = -velocity.y;
		position.y = upperBound-radius;
	}

	if(position.y-radius <= lowerBound) {
		velocity.y = -velocity.y;
		position.y = lowerBound+radius;
	}
	if(position.x+radius >= rightBound) {
		velocity.x = -velocity.x;
		position.x = rightBound-radius;
		std::string str = (*player1Score).getText();
		if(str[1]=='9') {
			str[0]++;
			str[1] = '0';
		} else {
			str[1]++;
		}
		(*player1Score).setText(str);
		reset();
	}

	if(position.x-radius <= leftBound) {
		velocity.x = -velocity.x;
		position.x = leftBound+radius;
		std::string str = (*player2Score).getText();
		
		if(str[1]=='9') {
			str[0]++;
			str[1] = '0';
		} else {
			str[1]++;
		}
		(*player2Score).setText(str);
		reset();
	}

	glm::vec3 p1Pos = (*player1).getPosition();
	glm::vec2 p1Size = (*player1).getSize();
	// Check box in front of player
	if(position.y < p1Pos.y+p1Size.y/2 && position.y > p1Pos.y-p1Size.y/2 && abs(p1Pos.x-position.x) < radius + p1Size.x/2) {
		velocity.x = -velocity.x;
		velocity.y += 60-rand()%60;
		position.x = p1Pos.x+p1Size.x/2+radius;
		velocity *= 1.05;
	}

	// Check player corners
	if(Utils::distance(glm::vec2(position.x, position.y), glm::vec2(p1Pos.x+p1Size.x/2.0f, p1Pos.y+p1Size.y/2.0f)) < radius
	|| Utils::distance(glm::vec2(position.x, position.y), glm::vec2(p1Pos.x+p1Size.x/2.0f, p1Pos.y-p1Size.y/2.0f)) < radius) {
		velocity.x = -velocity.x;
		velocity.y += 60-rand()%60;
		position.x = p1Pos.x+p1Size.x/2+radius;
		velocity *= 1.05;
	}

	glm::vec3 p2Pos = (*player2).getPosition();
	glm::vec2 p2Size = (*player2).getSize();
	if(position.y < p2Pos.y+p2Size.y/2 && position.y > p2Pos.y-p2Size.y/2 && abs(p2Pos.x-position.x) < radius + p2Size.x/2) {
		velocity.x = -velocity.x;
		velocity.y += 60-rand()%60;
		position.x = p2Pos.x-p2Size.x/2-radius;
		velocity *= 1.05;
	}

	if(Utils::distance(glm::vec2(position.x, position.y), glm::vec2(p2Pos.x-p2Size.x/2.0f, p2Pos.y+p2Size.y/2.0f)) < radius
	|| Utils::distance(glm::vec2(position.x, position.y), glm::vec2(p2Pos.x-p2Size.x/2.0f, p2Pos.y-p2Size.y/2.0f)) < radius) {
		velocity.x = -velocity.x;
		velocity.y += 60-rand()%60;
		position.x = p2Pos.x-p2Size.x/2-radius;
		velocity *= 1.05;
	}

	(*circle).setPosition(position);
}

void Ball::reset() {
	position = glm::vec3(400.0f, 300.0f, 0.0f);
	velocity = glm::vec3(std::rand()%50+150.0f, std::rand()%50+150.0f, 0.0f);
	if(std::rand()%2)
		velocity.x = -velocity.x;
	if(std::rand()%2)
		velocity.y = -velocity.y;
	velocity *= 1.25;
}

Circle* Ball::getCircle() {
	return circle;
}

glm::vec3 Ball::getPosition() {
	return position;
}

void Ball::setVelocity(glm::vec3 velocity) {
	this->velocity = velocity;
}

void Ball::setPosition(glm::vec3 position) {
	this->position = position;
	(*circle).setPosition(position);
}