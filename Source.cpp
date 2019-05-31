#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "game.h"
int main(int argc, char *argv[])
{
	try {
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
	}
	catch(const std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}
	system("Pause");
	return 0;
	//
}