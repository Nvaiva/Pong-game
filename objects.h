#pragma once
#include <vector>
#include "loadImage.h"
#include "object_pos.h"
const int BLOCKS = 2;
const int BLOCK_W = 80;
const int BLOCK_H = 15;
const int SQUARE_H_W = 20;
const int BLOCK_QUANTITY = 2;
//renderer size
const int REN_X = 100;
const int REN_Y = 100;
const int REN_W = 640;
const int REN_H = 400;

class Object
{
public:
	Object_pos<int>object_pos;
	bool is_running = true;
	bool start_again = true;
	SDL_Rect pos;
	SDL_Texture* tex;
	const Uint8 *keyState;
	SDL_Event event;
	SDL_Event event2;

public:
	int x, y, w, h, vell_x_d, vell_y_d;
	int get_x() { return x; }
	Object() = default;
	virtual ~Object() = default;
	virtual void load_image(const char* photoName, SDL_Renderer* ren) = 0;
	virtual void render(SDL_Renderer* ren, SDL_Rect wall) = 0;
	virtual void events() = 0;
	virtual void default_coordinates() = 0;
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

