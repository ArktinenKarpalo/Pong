#pragma once
#include <GLFW/glfw3.h>

class Game {
	public:
		void updateGame(double);
		static void framebuffer_size_callback(GLFWwindow*, int, int);
		static void handleInput(GLFWwindow*, int, int, int, int);
		void startGame();
		void init();
	private:
		GLFWwindow* window;
};