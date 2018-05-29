
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> 
#include <glad/glad.h>
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vertexStream, fragmentStream;

	vertexStream.open(vertexShaderPath);
	fragmentStream.open(fragmentShaderPath);

	std::stringstream vertexSStream, fragmentSStream;

	vertexSStream << vertexStream.rdbuf();
	fragmentSStream << fragmentStream.rdbuf();
	vertexStream.close();
	fragmentStream.close();

	vertexCode = vertexSStream.str();
	fragmentCode = fragmentSStream.str();

	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Create a shader program and link shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// We no longer need them so we can delete them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setMat4Uniform(const std::string &name, glm::mat4 value) {
	unsigned int uniformLoc = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setFloatUniform(const std::string &name, float value) {
	unsigned int uniformLoc = glGetUniformLocation(ID, name.c_str());
	glUniform1f(uniformLoc, value);
}

void Shader::setVec3Uniform(const std::string &name, glm::vec3 value) {
	unsigned int uniformLoc = glGetUniformLocation(ID, name.c_str());
	glUniform3fv(uniformLoc, 1, glm::value_ptr(value));
}

unsigned int Shader::getID() {
	return ID;
}