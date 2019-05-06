#pragma once
#define SDL_MAIN_HANDLED
#include <iostream>
#include <fstream>
#include <list>
#include "SDL.h"
#include "SDL_image.h"
#include "loadImage.h"
#include "ball.h"
#include "wall.h"
#include "objects.h"
#include "memory.h"
class Game
{
public:
	void events();
	void update();
	bool start();
	void save();
	void load();
	bool running() const { return isRunning; }
	bool again() const { return startAgain;  }
	bool collision1(Ball *square) const;
	bool collision2(Ball *square) const;
	Game();
	~Game();

private:
	std::vector <Object*> object;
	std::vector <Ball*> balls;
	bool t = true;
	bool isRunning;
	bool startAgain;
	SDL_Window* win;
	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Texture *game_over;
	SDL_Texture* intro;
	const Uint8 *key;
	Wall_1 *block1;
	Wall_2 *block2;
	Ball *square;
	Additional_ball *additional;
	std::vector <Additional_ball*> additionals;
	//const values
	const int BLOCKS = 2;
	const int BLOCK_W = 90;
	const int BLOCK_H = 30;
	const int SQUARE_H_W = 25;
	const int BLOCK_QUANTITY = 2;

	//renderer size
	const int REN_X = 100;
	const int REN_Y = 100;
	const int REN_W = 640;
	const int REN_H = 400;

};

