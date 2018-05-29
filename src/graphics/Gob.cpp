#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Gob.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <glad/glad.h>

Gob::Gob() {
	position = glm::vec3(0.0f);
}

void Gob::initDraw(unsigned int indices[], int sizeOfIndices, float vertices[], int sizeOfVertices) {
	this->indices = sizeOfIndices/sizeof(vertices[0]);
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
}

void Gob::draw() {
	(*shader).use();

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
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
}

glm::vec3 Gob::getPosition() {
	return position;
}

void Gob::setPosition(glm::vec3 position) {
	this->position = position;
}

glm::vec3 Gob::getScale() {
	return scale;
}

void Gob::setScale(glm::vec3 scale) {
	this->scale = scale;
}

void Gob::setShader(Shader* shader) {
	this->shader = shader;
}