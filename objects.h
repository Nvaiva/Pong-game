#pragma once
#include <vector>
#include "loadImage.h"

class objects
{
//How to keep these variables not public but at the same time visable to game.cpp file 
// Do I have to use set and get methods ?

public:
	bool isRunning = true;
	//loadImage texture;
	SDL_Rect object_pos;
	SDL_Texture* tex;
	const Uint8 *keyState;
	SDL_Event event;

public:
	//Why error LNK2001 function was declaired but not defined ?

	objects();
	~objects();
	virtual void load_image(const char* photoName, SDL_Renderer* ren) {}
	//virtual void load_image(loadImage &picture);
	virtual void render(SDL_Renderer* ren, SDL_Rect wall) {}
	virtual void events() {}
};

