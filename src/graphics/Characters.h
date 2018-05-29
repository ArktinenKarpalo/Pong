#pragma once
#include <utility>

class Characters {
	public:
		void genCharacters();
		std::pair<int, int> getCharEBO(char);
		unsigned int getCharVAO(char);
	private:
		std::pair<int, unsigned int> EBOS[128];
		unsigned int VAOS[128];
};