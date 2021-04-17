#include "Game.h"

void Game::initWindow()
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, title, NULL, NULL);

	if(this->window == nullptr)
	{
		std::cout << "ERROR::GAME::INIT_WINDOW::WINDOW_IS_NULL" << "\n";
		glfwTerminate();
	}
	
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glViewport(0, 0, framebufferWidth, framebufferHeight);
	glfwMakeContextCurrent(window);
}

Game::Game()
{
	this->initWindow();
}
Game::~Game()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
}
void Game::update()
{
	
}
void Game::render()
{
	
}
void Game::initGLFW()
{
	if(glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR::GAME::INIT_GLFW::INIT_FAILED" << "\n";
		glfwTerminate();
	}
}
void Game::iniGlEW()
{
	
}
