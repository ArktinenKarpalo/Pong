#include "Utils.h"
#include <cmath>

float Utils::distance(glm::vec2 p1, glm::vec2 p2) {
	return std::sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}