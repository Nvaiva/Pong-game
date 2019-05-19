#pragma once
#include "SDL.h"
#include "SDL_image.h"

class Image_texture
{
public:
	Image_texture () {}
	void load(const char* photoName, SDL_Renderer* ren);
	static SDL_Texture* load_texture(const char* photoName, SDL_Renderer* ren);
	SDL_Texture *texture;
};

