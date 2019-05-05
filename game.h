#pragma once
#define SDL_MAIN_HANDLED
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "loadImage.h"
#include "ball.h"
#include "wall.h"
#include "objects.h"
#define BLOCK_W 90
#define BLOCK_H 30
class game
{
public:
	void events();
	void update();
	bool running() { return isRunning; }
	bool collision1();
	bool collision2();
	game();
	~game();

private:

	std::vector <objects*> object;
	bool isRunning;
	SDL_Window* win;
	SDL_Renderer* renderer;
	const Uint8 *keyState;
	wall_1 *block1;
	wall_2 *block2;
	ball square;
};

