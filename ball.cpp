#include "ball.h"

ball::ball(int x, int y, int height, int width) {
	object_pos.x = x;
	object_pos.y = y;
	object_pos.h= height;
	object_pos.w = width;
}

void ball::load_image(const char* photoName, SDL_Renderer* ren) {
	image.load(photoName, ren);
	tex = image.texture;
}

void ball::render(SDL_Renderer* ren, SDL_Rect ball) {
	SDL_RenderCopy(ren, tex, NULL, &ball);
}

void ball::events() {
	if (object_pos.x <= 0)
		vell_x = -vell_x;

	if (object_pos.x >= 590)
		vell_x = -vell_x;

	if (object_pos.y <= 0)
		vell_y = -vell_y;

	if (object_pos.y >= 290)
		vell_y = -vell_y;

	object_pos.x += vell_x;
	object_pos.y += vell_y;
}


