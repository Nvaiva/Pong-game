#pragma once
#include "objects.h"
#include "object_pos.h"
#include <iostream>

class Ball : public Object
{
protected:
	Image_texture image;
	
	int vell_x  = 5, vell_y = 5; //vellocity of the ball
public:

	Ball() {}
	Ball(int x, int y, int height, int width);
	Ball(int x, int y, int height, int width, int vell_x, int vell_y);
	Ball(const Ball &ball);
	virtual ~Ball() {}

	void load_image(const char* photoName, SDL_Renderer* ren);
	void render(SDL_Renderer* ren, SDL_Rect ball);
	void events();
	int get_x() const { return vell_x; }
	int get_y() const { return vell_y; }
	void set_x(int x) { vell_x = x; }
	void set_y(int y) { vell_y = y; }

	Ball& operator += (const int& scale) {
		if (vell_x < 0 ? vell_x -= scale : vell_x +=scale);
		if (vell_y < 0 ? vell_y -= scale : vell_y += scale);
		return *this;
	}
	Ball& operator -= (const int& scale) {
		if (vell_x < 0 ? vell_x += scale : vell_x -= scale);
		if (vell_y < 0 ? vell_y += scale : vell_y -= scale);
		return *this;
	}
	/*Ball operator * (const int scale) {
		return Ball(100, 100, SQUARE_H_W, SQUARE_H_W, vell_x * scale, vell_y * scale);
	}*/
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

