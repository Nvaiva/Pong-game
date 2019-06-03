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
	//Object_pos<int> object_pos;
	Walls() {}
	Walls(int x, int y, int width, int height);
	virtual ~Walls() {}
	void load_image(const char* photoName, SDL_Renderer* ren);
	void render(SDL_Renderer* ren, SDL_Rect wall);
	void events() {}
};

class Wall_1 : public Walls {
public:
	Wall_1() {}
	Wall_1 (int x, int y, int width, int height):Walls(x, y, width, height) {} 
	void default_coordinates();
	void render(SDL_Renderer* ren, SDL_Rect wall);
	~Wall_1 () {}
	void events();
};

class Wall_2 : public Walls {
public:
	Wall_2() {}
	Wall_2(int x, int y, int width, int height):Walls(x, y, width, height) {}
	~Wall_2() {}
	void events();
	void default_coordinates();
	void render(SDL_Renderer* ren, SDL_Rect wall);
	void AI_wall(int y);
};
class Additional_wall : public Walls {
public:
	Additional_wall(): Walls() { }
	Additional_wall(int x, int y, int width, int height) :Walls(x, y, width, height) {}
	~Additional_wall() {}
	void events() { }
	void default_coordinates() {}
	void render(SDL_Renderer* ren, SDL_Rect wall);
};

