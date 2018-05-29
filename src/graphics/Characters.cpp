#include "Characters.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <vector>

// Generates characters between 0-9
void Characters::genCharacters() {
	float vertices[] = {
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	};

	std::vector<unsigned int> indices[128];
	//indices.resize(128);

	indices['0'] = {
		0, 4,
		1, 5,
		0, 1,
		4, 5,
		1, 4
	};
	indices['1'] = {
		0, 4
	};
	indices['2'] = {
		0, 1,
		2, 3,
		4, 5,
		1, 3,
		2, 4
	};
	indices['3'] = {
		0, 1,
		2, 3,
		4, 5,
		1, 5
	};
	indices['4'] = {
		2, 3,
		0, 2,
		1, 5
	};
	indices['5'] = {
		0, 1,
		2, 3,
		4, 5,
		3, 5,
		0, 2
	};
	indices['6'] = {
		0, 4,
		3, 5,
		0, 1,
		2, 3,
		4, 5
	};
	indices['7'] = {
		0, 1,
		1, 5
	};
	indices['8'] = {
		0, 1,
		2, 3,
		4, 5,
		0, 4,
		1, 5
	};
	indices['9'] = {
		1, 5,
		0, 1,
		2, 3,
		0, 2
	};
		
	for(int i='0'; i<='9'; i++) {
		unsigned int VAO, EBO, VBO;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);		
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		EBOS[i] = std::make_pair(EBO, indices[i].size());
		VAOS[i] = VAO;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices[i].size()*sizeof(unsigned int), &indices[i].front(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

std::pair<int, int> Characters::getCharEBO(char cha) {
	return EBOS[cha];
}

unsigned int Characters::getCharVAO(char cha) {
	return VAOS[cha];
}