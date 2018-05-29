#include "Player.h"

Player::Player(glm::vec3 position, glm::vec2 size, float speed, Shader* shader) {
	this->size = size;
	this->position = position;
	this->speed = speed;
	rectangle = new Rectangle(position, size, shader);
	(*rectangle).initDraw();
	moveDirection = 0;
}

void Player::update(float deltaTime) {
	position.y += speed*moveDirection*deltaTime;
	if(position.y+size.y/2 > upperBound)
		position.y = upperBound-size.y/2;
	if(position.y-size.y/2 < lowerBound)
		position.y = lowerBound+size.y/2;
	(*rectangle).setPosition(position);
}

Rectangle* Player::getRectangle() {
	return rectangle;
}

void Player::setSpeed(float speed) {
	this->speed = speed;
}

int Player::getDirection() {
	return moveDirection;
}

// 1 = up, 0 = no move, -1 = down
void Player::move(int direction) {
	moveDirection = direction;
}

glm::vec3 Player::getPosition() {
	return position;
}

glm::vec2 Player::getSize() {
	return size;
}

void Player::setPosition(glm::vec3 position) {
	this->position = position;
	(*rectangle).setPosition(position);
}