#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"

class Gob {

	public:
		Gob();
		virtual glm::vec3 getPosition();
		virtual void setPosition(glm::vec3);
		virtual glm::vec3 getScale();
		virtual void setScale(glm::vec3);
		virtual void setShader(Shader*);
		virtual void initDraw(unsigned int*, int, float*, int);
		virtual void draw();
	private:
		glm::vec3 position;
		glm::vec3 scale;
		std::vector<float> vertices;
		Shader *shader;
		unsigned int EBO, VBO, VAO, indices;
};