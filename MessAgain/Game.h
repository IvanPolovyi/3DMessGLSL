#pragma once

#include "libs.h"

class Game
{
private:
	GLFWwindow* window;
	const char* title = "Mess Again";
	const int WIDTH = 640;
	const int HEIGHT = 480;
	int framebufferWidth = WIDTH;
	int framebufferHeight = HEIGHT;

	void initGLFW();
	void initWindow();
	void iniGlEW();
public:
	Game();
	virtual ~Game();

	void update();
	void render();
};

