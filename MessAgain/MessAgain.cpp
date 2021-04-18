#include "Game.h"




int main()
{
	glfwInit();

	const int glMajorVersion = 4;
	const int glMinorVersion = 5;

	Game game( (char*) "Mess Again");
	
	while (game.getWindowShouldClose() == false)
	{
		game.update();
		game.render();
	}

	return 0;
}

