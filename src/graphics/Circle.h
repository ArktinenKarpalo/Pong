#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"
#include "Gob.h"

class Circle : public Gob {
	
	public:
		Circle(glm::vec3, float, Shader*);
		glm::vec3 getPosition();
		void setPosition(glm::vec3);
		glm::vec3 getScale();
		void setScale(glm::vec3);
		void setShader(Shader*);
		void setColor(glm::vec3);
		void initDraw();
		void draw();
		void setRadius(float);
		glm::vec3 getColor();
		float getRadius();
	private:
		glm::vec3 position, scale, color;
		std::vector<float> vertices;
		Shader *shader;
		unsigned int EBO, VBO, VAO, indices;
		float radius;  
};