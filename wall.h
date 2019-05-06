#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "loadImage.h"
#include "objects.h"
#include "ball.h"

class Walls : public Object
{
protected:
	Image_texture image;
public:
	Walls() {}
	Walls(int x, int y, int width, int height);
	virtual ~Walls() {}
	void load_image(const char* photoName, SDL_Renderer* ren);
	void render(SDL_Renderer* ren, SDL_Rect wall);
	void events() {}

	//const values
	const int BLOCK_W = 90;
	const int BLOCK_H = 30;
	const int REN_Y = 100;
	const int REN_W = 640;
	const int REN_H = 400;

};

class Wall_1 : public Walls {
public:
	Wall_1() {}
	Wall_1 (int x, int y, int width, int height):Walls(x, y, width, height) {} 
	~Wall_1 () {}
	void events();
};

class Wall_2 : public Walls {
public:
	Wall_2() {}
	Wall_2(int x, int y, int width, int height):Walls(x, y, width, height) {}
	
	~Wall_2() {}
	void events();
};


