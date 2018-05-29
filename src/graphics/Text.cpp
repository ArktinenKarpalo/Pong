#include "Text.h"
#include "Characters.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <glad/glad.h>

extern std::vector<Gob*> objectsToDraw;
extern Characters *characters;

Text::Text(std::string text, glm::vec3 position, float size, Shader* textShader) {
	this->text = text;
	this->position = position;
	scale = glm::vec3(size/2, size, 0.0f);
	shader = textShader;
}

void Text::initDraw() {
	objectsToDraw.push_back(this);
}

void Text::draw() {
	(*shader).use();

	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	(*shader).setMat4Uniform("view", view);
	(*shader).setMat4Uniform("projection", projection);
	
	glLineWidth(scale.x/5);
	for(int i=0; i<text.size(); i++) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position.x+i*scale.x*3, position.y, position.z));
		model = glm::scale(model, scale);
		(*shader).setMat4Uniform("model", model);
		glBindVertexArray((*characters).getCharVAO(text[i]));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*characters).getCharEBO(text[i]).first);
		glDrawElements(GL_LINES, (*characters).getCharEBO(text[i]).second, GL_UNSIGNED_INT, 0);
	}
}

glm::vec3 Text::getPosition() {
	return position;
}

void Text::setText(std::string text) {
	this->text = text;
}

void Text::setPosition(glm::vec3 position) {
	this->position = position;
}

glm::vec3 Text::getScale() {
	return scale;
}

void Text::setScale(glm::vec3 scale) {
	this->scale = scale;
}

std::string Text::getText() {
	return text;
}