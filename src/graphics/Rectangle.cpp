#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Gob.h"
#include <glad/glad.h>
#include "Rectangle.h"

Rectangle::Rectangle(glm::vec3 position, glm::vec2 size, Shader* shader) {
	this->position = position;
	this->size = size;
	setScale(glm::vec3(size, 1.0f));
	this->shader = shader;
	color = glm::vec3(1.0f);
}

void Rectangle::initDraw() {
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
	int sizeOfIndices = sizeof(indices);
	int sizeOfVertices = sizeof(vertices);
	this->indices = sizeOfIndices/sizeof(vertices[0]);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Rectangle::draw() {
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
	(*shader).setVec3Uniform("color", color);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
}

glm::vec3 Rectangle::getPosition() {
	return position;
}

void Rectangle::setPosition(glm::vec3 position) {
	this->position = position;
}

glm::vec3 Rectangle::getScale() {
	return scale;
}

glm::vec3 Rectangle::getColor() {
	return color;
}

void Rectangle::setScale(glm::vec3 scale) {
	this->scale = scale;
}

void Rectangle::setShader(Shader* shader) {
	this->shader = shader;
}

void Rectangle::setColor(glm::vec3 color) {
	this->color = color;
}

void Rectangle::setSize(glm::vec2 size) {
	this->size = size;
	setScale(glm::vec3(size, 1.0f));
}