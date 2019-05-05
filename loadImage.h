#pragma once
#include "SDL.h"
#include "SDL_image.h"

class loadImage 
{
public:
	loadImage () {}
	void load(const char* photoName, SDL_Renderer* ren);
	SDL_Texture *texture;
};

