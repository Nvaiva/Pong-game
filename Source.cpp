#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "game.h"
int main(int argc, char *argv[])
{
	game *Game = NULL;
	Game = new game();
	
	while (Game->running()) {
		Game->update();
		Game->events();
		//Game->render();
		SDL_Delay(1000 / 60);
	}

	delete Game;
	system("Pause");
	return 0;
}