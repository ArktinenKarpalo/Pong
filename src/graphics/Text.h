#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Gob.h"

class Text : public Gob {
	public:
		Text(std::string, glm::vec3, float, Shader*);
		glm::vec3 getPosition();
		void setPosition(glm::vec3);
		glm::vec3 getScale();
		void setScale(glm::vec3);
		void initDraw();
		void draw();
		void setText(std::string);
		std::string getText();
	private:
		std::string text;
		Shader *shader;
		glm::vec3 position, scale;
};