#define GLFW_INCLUDE_NONE
#include <iostream>
#include <fstream>
#include <vector>
#include <GLFW/glfw3.h> 
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../graphics/Gob.h"
#include "../graphics/Shader.h"
#include "../graphics/Circle.h"
#include "../graphics/Rectangle.h"
#include "../graphics/Characters.h"
#include "../graphics/Text.h"
#include "Player.h"
#include "Ball.h"
#include "Game.h"

std::vector<Gob*> objectsToDraw;
Characters *characters;
Ball *ball;
Text *player1Score, *player2Score;
Player *player1, *player2;

void Game::startGame() {
	init();

	Shader circleShader = Shader("shaders/circleVertexShader.vert", "shaders/circleFragmentShader.frag");
	Shader shader = Shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
	
	characters = new Characters();
	(*characters).genCharacters();

	player1Score = new Text("00", glm::vec3(280.0f, 550.0f, 0.0f), 40.0f, &shader);
	(*player1Score).initDraw();
	player2Score = new Text("00", glm::vec3(460.0f, 550.0f, 0.0f), 40.0f, &shader);
	(*player2Score).initDraw();

	ball = new Ball(15.0f, 1.0f, &circleShader);
	objectsToDraw.push_back((*ball).getCircle());
	(*ball).reset();
	
	player1 = new Player(glm::vec3(30.0f, 300.0f, 0.0f), glm::vec2(20.0f, 100.0f), 320.0f, &shader);
	objectsToDraw.push_back((*player1).getRectangle());
	player2 = new Player(glm::vec3(770.0f, 300.0f, 0.0f), glm::vec2(20.0f, 100.0f), 320.0f, &shader);	
	objectsToDraw.push_back((*player2).getRectangle());

	glfwSwapInterval(1); // VSYNC 0-OFF / ON-1

	double last = 0;
	// Main gameloop
	while(!glfwWindowShouldClose(window)) {
		double now = glfwGetTime();
		std::cout << "FPS: " << 1.0/(now-last) << std::endl;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		updateGame(now-last);

		for(auto u:objectsToDraw)
			(*u).draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
		last = now;
	}
	glfwTerminate();
}

void Game::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(800, 600, "Pong", NULL, NULL);
	if(window == NULL) {
		std::cout << "Failed to create GLFW window!" << "\n";
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, handleInput);
	glEnable(GL_MULTISAMPLE);
}

void Game::handleInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_UP || key == GLFW_KEY_W) {
		if(action)
			(*player1).move(1);	 
		else if((*player1).getDirection()==1)
			(*player1).move(0);	
	} else if(key == GLFW_KEY_DOWN || key == GLFW_KEY_S) {
		if(action)
			(*player1).move(-1);
		else if((*player1).getDirection()==-1)
			(*player1).move(0);	
	}
}

void Game::updateGame(double deltaTime) {
	(*ball).update(deltaTime);
	if(std::abs((*ball).getPosition().y-(*player2).getPosition().y) > 30) {
		if((*ball).getPosition().y-((*player2).getPosition().y) > 0)
			(*player2).move(1);
		else if((*ball).getPosition().y-((*player2).getPosition().y) < 0)
			(*player2).move(-1);
	} else {
		(*player2).move(0);
	}
	(*player1).update(deltaTime);
	(*player2).update(deltaTime);
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// Resize viewport when window size is changed
	glViewport(0, 0, width, height);
}