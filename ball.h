#pragma once
#include "objects.h"
class Ball : public Object
{
protected:
	Image_texture image;
	int vell_x  = 5, vell_y = 5; //vellocity of the ball
public:
	Ball() {}
	Ball(int x, int y, int height, int width);
	Ball(const Ball &ball);
	virtual ~Ball() {}

	void load_image(const char* photoName, SDL_Renderer* ren);
	void render(SDL_Renderer* ren, SDL_Rect ball);
	void events();
	int get_x() const { return vell_x; }
	int get_y() const { return vell_y; }
	void set_x(int x) { vell_x = x; }
	void set_y(int y) { vell_y = y; }

	//const values
	const int SQUARE_H_W = 25;
	const int REN_X = 100;
	const int REN_Y = 100;
	const int REN_W = 640;
	const int REN_H = 400;
};

class Additional_ball : public Ball
{
public:
	static int count_balls;
public:
	Additional_ball() {}
	Additional_ball(int x, int y, int width, int height) :Ball(x, y, width, height) { count_balls += 1; }
	Additional_ball(const Additional_ball &ad_ball) :Ball(ad_ball) { count_balls += 1; }
	~Additional_ball() {}
	static int get_count () { return count_balls; }
	static void set_count(int a) { count_balls = a; }
	void events();
};

