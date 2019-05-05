#pragma once
#include "figure.h"
#include "objects.h"
class ball : public objects
{
protected:
	loadImage image;
	int vell_x = 5, vell_y = 5; //vellocity of the ball
public:
	ball() {}
	ball(int x, int y, int height, int width);
	void load_image(const char* photoName, SDL_Renderer* ren);
	void render(SDL_Renderer* ren, SDL_Rect ball);
	void events();

	int get_x() { return vell_x; }
	int get_y() { return vell_y; }
	void set_x(int x) { vell_x = x; }
	void set_y(int y) { vell_y = y; }
};

