#include "wall.h"

walls::walls(int x, int y, int width, int height) {
	std::cout << "Walls konstruktoius" << std::endl;
	object_pos.x = x;
	object_pos.y = y;
	object_pos.w = width;
	object_pos.h = height;

}

void walls::load_image(const char* photoName, SDL_Renderer* ren) {
	image.load(photoName, ren);
	tex = image.texture;
}

/*void walls::load_image(loadImage &picture) {
	tex = image.texture;
}*/

void walls::render(SDL_Renderer* ren, SDL_Rect wall) {
	SDL_RenderCopy(ren, tex, NULL, &wall);
}

void wall_1::events() {
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT)
			isRunning = false;
	}

	keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_UP] && object_pos.y > 0)
		object_pos.y -= 10;
	else if (keyState[SDL_SCANCODE_DOWN] && object_pos.y < 290)
		object_pos.y += 10;
}

void wall_2::events() {

	keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_W] && object_pos.y > 0)
		object_pos.y -= 10;
	else if (keyState[SDL_SCANCODE_S] && object_pos.y < 290)
		object_pos.y += 10;
}

