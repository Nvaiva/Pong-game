#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "game.h"

int main(int argc, char *argv[])
{
	while (true) {
		Game *game = NULL;
		game = new Game();
		while (game->running()) {
			game->events();
			game->update();
			SDL_Delay(1000 / 60);
		}
		if (game->again()) {
			delete game;
		}
		else {
			delete game;
			break;
		}
	}
	system("Pause");
	return 0;
	//
}