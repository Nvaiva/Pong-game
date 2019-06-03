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
SDL_Texture* Image_texture::load_ttf(const char* text,TTF_Font* font, SDL_Color color, SDL_Renderer* ren) {
	SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	return texture;

}