#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Circle.h"
#include <glad/glad.h>
#include "Gob.h"
#include <vector>

extern std::vector<Gob*> objectsToDraw;

Circle::Circle(glm::vec3 position, float radius, Shader* circleShader) {
	this->radius = radius;
	this->position = position;
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	scale = glm::vec3(radius*2);
	shader = circleShader;
}

void Circle::initDraw() {
	float vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f,-0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	unsigned int indices[] = {
		0,1,2,
		0,2,3
	};
	unsigned int sizeOfIndices = sizeof(indices), sizeOfVertices = sizeof(vertices);
	this->indices = sizeOfIndices/sizeof(indices[0]);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	// Send coordinates of vertices to the GPU
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices, GL_STATIC_DRAW);

	// Send order of vertices to the GPU
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	objectsToDraw.push_back(this);
}

void Circle::draw() {
	(*shader).use();
	glBindVertexArray(VAO);

	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);

	projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	model = glm::translate(model, position);
	model = glm::scale(model, scale);

	(*shader).setMat4Uniform("model", model);
	(*shader).setMat4Uniform("view", view);
	(*shader).setMat4Uniform("projection", projection);
	(*shader).setFloatUniform("radius", radius);
	(*shader).setVec3Uniform("center", position);
	(*shader).setVec3Uniform("color", color);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
}

glm::vec3 Circle::getPosition() {
	return position;
}

glm::vec3 Circle::getColor() {
	return color;
}

void Circle::setPosition(glm::vec3 position) {
	this->position = position;
}

glm::vec3 Circle::getScale() {
	return scale;
}

void Circle::setScale(glm::vec3 scale) {
	this->scale = scale;
}

void Circle::setShader(Shader* shader) {
	this->shader = shader;
}

void Circle::setRadius(float radius) {
	this->radius = radius;
	scale = glm::vec3(radius*2);
}

void Circle::setColor(glm::vec3 color) {
	this->color = color;
}

float Circle::getRadius() {
	return radius;
}