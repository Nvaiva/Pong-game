#pragma once
#define SDL_MAIN_HANDLED
#include <iostream>
#include <fstream>
#include <list>
#include "SDL.h"
#include "SDL_image.h"
#include "loadImage.h"
#include "ball.h"
#include "wall.h"
#include "objects.h"
#include "memory.h"
#include <map>
#include <iterator>
#include <utility>
#include "renderer_error.h"
#include <time.h>
#include <algorithm>

class Game
{
public:
	void events();
	void update();
	bool start(bool* player_2);
	void save();
	void load();
	bool running() const { return is_running; }
	bool again() const { return start_again;  }
	bool collision1(Ball *square) const;
	Game();
	~Game();

private:
	//Object_pos<int> object_pos;
	std::vector <Object*> object;
	std::vector<Object*>::iterator it;
	const Uint8 *keyState;
	SDL_Rect pos;
	bool t = true;
	bool is_running;
	bool start_again;
	bool player_2 = false;
	SDL_Window* win;
	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Texture *game_over;
	SDL_Texture* intro;
	const Uint8 *key;
	Wall_1 *block1;
	Wall_2 *block2;
	Ball *square;

	static clock_t time;
	int nr_time;
};

