#define SDL_MAIN_HANDLED
#include "loadImage.h"
#include <SDL.h>
#include <SDL_image.h>

void loadImage::load(const char* photoName, SDL_Renderer* ren) {

	SDL_Surface* tempSur = IMG_Load(photoName);
	texture = SDL_CreateTextureFromSurface(ren, tempSur);
	SDL_FreeSurface(tempSur);
}