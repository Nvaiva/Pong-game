#pragma once
#include <vector>
#include "loadImage.h"

class Object
{
public:
	bool isRunning = true;
	bool startAgain = true;
	SDL_Rect object_pos;
	SDL_Texture* tex;
	const Uint8 *keyState;
	SDL_Event event;
	SDL_Event event2;

public:

	Object() = default;
	virtual ~Object() = default;
	virtual void load_image(const char* photoName, SDL_Renderer* ren) = 0;
	virtual void render(SDL_Renderer* ren, SDL_Rect wall) = 0;
	virtual void events() = 0;

	//const values
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

