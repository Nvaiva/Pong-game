#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "loadImage.h"
#include "objects.h"

class walls : public objects
{
protected:
	loadImage image;
public:
	walls() {}
	walls(int x, int y, int width, int height);
	~walls() {}

	void load_image(const char* photoName, SDL_Renderer* ren);
	//void load_image(loadImage &picture);
	void render(SDL_Renderer* ren, SDL_Rect wall);
	void events() {}
};

class wall_1 : public walls {
public:
	wall_1() {}
	wall_1 (int x, int y, int width, int height) {
		walls::walls(x, y, width, height);
	}
	~wall_1 () {}
	void events();
};

class wall_2 : public walls {
public:
	wall_2() {}
	wall_2(int x, int y, int width, int height) {
		std::cout << "Wall_2 konstruktoius" << std::endl;
		walls::walls(x, y, width, height);
	}

	~wall_2() {}
	void events();
};


