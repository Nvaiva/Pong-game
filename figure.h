#pragma once
#include <SDL.h>
#include <SDL_image.h>
class figure
{
public:
	figure() {}
	virtual void set_coordinates(int x, int y, int height, int width) {}

	static SDL_Texture* load(const char* photoName, SDL_Renderer* ren) {

		SDL_Surface* tempSur = IMG_Load(photoName);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSur);
		SDL_FreeSurface(tempSur);
		return tex;
	}
};

