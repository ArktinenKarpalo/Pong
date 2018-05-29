#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "Gob.h"

class Rectangle : public Gob {

	public:
		Rectangle(glm::vec3, glm::vec2, Shader*);
		glm::vec3 getPosition();
		void setPosition(glm::vec3);
		glm::vec3 getScale();
		void setScale(glm::vec3);
		void setShader(Shader*);
		void draw();
		void initDraw();
		void setColor(glm::vec3);
		void setSize(glm::vec2);
		glm::vec3 getColor();
	private:
		glm::vec3 position, scale, color;
		glm::vec2 size;
		Shader *shader;
		unsigned int EBO, VBO, VAO, indices;
};