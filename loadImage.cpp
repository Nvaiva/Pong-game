#define SDL_MAIN_HANDLED
#include "loadImage.h"
#include <SDL.h>
#include <SDL_image.h>

void Image_texture::load(const char* photoName, SDL_Renderer* ren) {

	SDL_Surface* tempSur = IMG_Load(photoName);
	texture = SDL_CreateTextureFromSurface(ren, tempSur);
	SDL_FreeSurface(tempSur);
}

SDL_Texture* Image_texture::load_texture(const char* photoName, SDL_Renderer* ren) {
	SDL_Surface* tempSur = IMG_Load(photoName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSur);
	SDL_FreeSurface(tempSur);

	return tex;
}