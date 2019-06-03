#include "ball.h"

int Additional_ball::count_balls = 0;

Ball::Ball(int x, int y, int height, int width) {
	object_pos.x = x;
	object_pos.y = y;
	object_pos.h= height;
	object_pos.w = width;
}
Ball::Ball(int x, int y, int height, int width, int vell_x, int vell_y) {
	object_pos.x = x;
	object_pos.y = y;
	object_pos.h = height;
	object_pos.w = width;
	vell_x = vell_x;
	vell_y = vell_y;
}
Ball::Ball(const Ball &ball) {
	object_pos.x = ball.object_pos.x;
	object_pos.y = ball.object_pos.y;
	object_pos.h = ball.object_pos.h;
	object_pos.w = ball.object_pos.w;
}
Ball& operator -= (Ball& ball, const int& scale){
	if (ball.vell_x < 0 ? ball.vell_x += scale : ball. vell_x -= scale);
	if (ball.vell_y < 0 ? ball.vell_y += scale : ball.vell_y -= scale);
	return ball;
}
void Ball::load_image(const char* photoName, SDL_Renderer* ren) {
	image.load(photoName, ren);
	tex = image.texture;
}

void Ball::render(SDL_Renderer* ren, SDL_Rect ball){
	SDL_RenderCopy(ren, tex, NULL, &ball);
}

void Ball::events() {
	if (object_pos.x <= 0)
		vell_x = -vell_x;

	if (object_pos.x >= REN_W)
		vell_x = -vell_x;

	if (object_pos.y <= 0)
		vell_y = -vell_y;

	if (object_pos.y >= REN_H - REN_Y)
		vell_y = -vell_y;

	object_pos.x += vell_x;
	object_pos.y += vell_y;
}
void Ball::default_coordinates() {
	x = object_pos.x;
	y = object_pos.y;
	w = object_pos.w;
	h = object_pos.h;
	vell_x_d = vell_x;
	vell_y_d = vell_y;
}
void Additional_ball::events() {
	if (object_pos.x <= 0)
		vell_x = -vell_x;

	if (object_pos.x >= REN_W)
		vell_x = -vell_x;

	if (object_pos.y <= 0)
		vell_y = -vell_y;

	if (object_pos.y >= REN_H - REN_Y)
		vell_y = -vell_y;

	if (count_balls / 2 == 0) {
		object_pos.x -= vell_x;
		object_pos.y -= vell_y;
	}
	else {
		object_pos.x += vell_x;
		object_pos.y -= vell_y;
	}
}


