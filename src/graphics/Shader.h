#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader {
	public:
		Shader(std::string, std::string);
		unsigned int getID();
		void use();
		void setMat4Uniform(const std::string&, glm::mat4);
		void setFloatUniform(const std::string&, float);
		void setVec3Uniform(const std::string&, glm::vec3);
	private:
		unsigned int ID;
};