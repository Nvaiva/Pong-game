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
#include <list>
#include "SDL_ttf.h"
#include <array>
class Game
{
public:
	void events();
	void update();
	bool start(bool* player_2);
	void save();
	void load();
	bool running() const { return is_running; }
	void set_running() { is_running = true; }
	bool again() const { return start_again;  }
	void set_again() { start_again = false; }
	bool collision1(Ball *square, Object *wall) const;
	bool is_add_block(const Object* a) const { if (a == ad_block) true; }
	void game_start_again();
	Game();
	~Game();

private:
	//Object_pos<int> object_pos;
	std::vector <Object*> object;
	std::vector<Object*>::iterator it; // objects vector iterator
	const Uint8 *keyState;
	SDL_Rect pos;
	SDL_Rect middle_line_pos;
	bool t = true;
	bool is_running;
	bool start_again;
	bool player_2 = false;
	SDL_Window* win;
	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Texture *game_over;
	SDL_Rect game_over_pos;
	SDL_Texture *middle_line;
	SDL_Texture* intro;
	const Uint8 *key;
	Wall_1 *block1;
	Wall_2 *block2;
	Ball *square;
	Additional_wall *ad_block;

	std::list<Object*> blocks;
	std::list<Object*>::iterator blo; //blocks array iterator
	static clock_t time;
	int nr_time;

	//points rendering
	//size_t block1_points;
	//size_t block2_points;
	std::array<size_t, 2> points;
	size_t block1_points_new;
	size_t block2_points_new;
	TTF_Font * font;
	SDL_Color color;
	SDL_Texture* points1;
	SDL_Texture* points2;
	SDL_Rect points1_pos;
	SDL_Rect points2_pos;
	std::string a;//string for block1_points rendering;
	std::string b; //string for block2_points rendering;
};

