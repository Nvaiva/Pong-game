#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "game.h"
int main(int argc, char *argv[])
{
	try {
		Game *game = NULL;
		game = new Game();
		while (true) {
			while (game->running()) {
				game->events();
				game->update();
				SDL_Delay(1000 / 60);
			}
			if (game->again()) {
				game->game_start_again();
				game->set_running();
				game->set_again();
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