#include "game.h"
#include <vector>
#include <iostream>
clock_t Game::time = clock();
Game::Game()
{
	//time = clock();
	nr_time = 1;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Window was initialized " << std::endl;
		win = SDL_CreateWindow("Awesome pong game!", REN_X, REN_Y, REN_W, REN_H, SDL_WINDOW_SHOWN);
			if(win == 0){
				throw error("Window was not created ");
			}
		renderer = SDL_CreateRenderer(win, -1, 0);
		if (renderer == 0) {
			throw error("Renderer was not created ");
		}
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		}
		is_running = true;
		start_again = false;
	}
	else {
		throw error("SDL_Init error ");
	}
	//initialize objects
	block1 = new Wall_1(0, 0, BLOCK_H, BLOCK_W);
	object.push_back(block1);
	block2 = new Wall_2(610, 0, BLOCK_H, BLOCK_W);
	object.push_back(block2);

	square = new Ball(100, 100, SQUARE_H_W, SQUARE_H_W);
	object.push_back(square);

	//upload images to these objects
	for (it = object.begin(); it != object.end(); ++it) {
		(*it)->load_image("Block.png", renderer);
		if ((*it)->tex == nullptr) {
			throw error("Block texture was not loaded ");
		}
	}
	object[2]->load_image("ball.png", renderer);
	if (object[2]->tex == nullptr) {
		throw error("Ball texture was not loaded ");
	}
	game_over = Image_texture::load_texture("game_over.png", renderer);
	if (game_over == nullptr) {
		throw error("Game over texture was not loaded ");
	}

	//if load game was pressed
	bool a;
	if (!(a = start(&player_2)))
		load();
	
}
bool Game::start(bool *player_2)
{
	intro = Image_texture::load_texture("Start.png", renderer);
	if (intro == nullptr) {
		throw error("Intro texture was not loaded ");
	}
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, intro, NULL, NULL);
	SDL_RenderPresent(renderer);
	bool t = true;
	while (t) {
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:
				is_running = false;
				start_again = false;
				t = false;
				break;

			case SDL_MOUSEBUTTONDOWN:
				//std::cout << event.motion.x << " " << event.motion.y << std::endl;
				if (event.motion.x >= 218 && event.motion.x <= 400 && event.motion.y >= 145 && event.motion.y <= 188) {
					*player_2 = true;
					return true;
				}
				if (event.motion.x >= 210 && event.motion.x <= 391 && event.motion.y >= 199 && event.motion.y <= 238)
					return true;
				if (event.motion.x >= 186 && event.motion.x <= 446 && event.motion.y >= 260 && event.motion.y <= 306)
					return false;
				break;
			}
		}
	SDL_DestroyTexture(intro);
	}
	return true;
}
void Game::events()
{
	time = clock();
	if (time / CLOCKS_PER_SEC > nr_time * 10) {
		nr_time += 1;
	}
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			is_running = false;
			start_again = false;
		}
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_KP_PLUS:
				(*square += 1);
				break;
			case SDLK_KP_MINUS:
				(*square -= 1);
				break;
			}
		}
	}
	if (!player_2) {
		for (it = object.begin(); it != object.end(); ++it)
			(*it)->events();
	}
	else {
		object[0]->events();
		int y = object[2]->object_pos.y;
		block2->AI_wall(y);
		object[2]->events();
	}
	int vell_x;
	if (collision1(square)) {
		vell_x = square->get_x();
		square->set_x(-vell_x);
	}
	if (square->object_pos.x < 5 || square->object_pos.x > REN_W-5) {
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, game_over, NULL, NULL);
		SDL_RenderPresent(renderer);

		bool t = true;
		while (t) {
			while (SDL_PollEvent(&event) > 0)
			{
				switch (event.type)
				{
				case SDL_QUIT:
					is_running = false;
					start_again = false;
					t = false;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_KP_ENTER:
						is_running = false;
						start_again = true;
						t = false;
						break;
					}
				}
			}
		}
	}
}
bool Game::collision1(Ball *square) const
{
	if ((((square->object_pos.y >= block1->object_pos.y) && (square->object_pos.x > block1->object_pos.x))
		&& (square->object_pos.x < (block1->object_pos.x + BLOCK_H))
			&& (square->object_pos.y < (block1->object_pos.y + BLOCK_W))) ||
				((square->object_pos.y + SQUARE_H_W >= block2->object_pos.y) 
					&& (square->object_pos.x < block2->object_pos.x)
						&& (square->object_pos.x + SQUARE_H_W >= (block2->object_pos.x))
							&& (square->object_pos.y <= (block2->object_pos.y + BLOCK_W))))
	
	{
		return true;
	}
	else {
		return false;
	}
	
}

void Game::update()
{
	SDL_RenderClear(renderer);
	for (it = object.begin(); it != object.end(); ++it) {
		(*it)->pos.x = (*it)->object_pos.x;
		(*it)->pos.y = (*it)->object_pos.y;
		(*it)->pos.w = (*it)->object_pos.w;
		(*it)->pos.h = (*it)->object_pos.h;
	}
	for (it = object.begin(); it != object.end(); ++it)
		SDL_RenderCopy(renderer, (*it)->tex, NULL, &(*it)->pos);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderPresent(renderer);

	for (it = object.begin(); it != object.end(); ++it) {
	if ((*it)->is_running == false) {
		save();
		is_running = false;
	}
	}
	if (!is_running && t== true)
		save();
	
		
	if (object[0]->start_again == false)
		start_again = false;
}
Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_DestroyTexture(game_over);
	game_over = nullptr;
	
	for (it = object.begin(); it != object.end(); ++it) {
		delete (*it);
	}
		

	SDL_Quit();
}
void Game::save()
{
	std::ofstream ofile("result.bin", std::ios::binary);
	ofile.clear();

	size_t count = object.size();
	ofile.write((char*)&count, sizeof(int));
	for (size_t i = 0; i < count ; ++i) {
		ofile.write((char*)&object[i]->object_pos.x, sizeof(int));
		ofile.write((char*)&object[i]->object_pos.y, sizeof(int));
	}
	int x = square->get_x();
	int y = square->get_y();
	ofile.write((char*)&x, sizeof(int));
	ofile.write((char*)&y, sizeof(int));
	ofile.write((char*)&player_2, sizeof(bool));
	ofile.close();
}
void Game::load() 
{
	
	std::ifstream ofile("result.bin", std::ios::binary);
	ofile.seekg(0);
	int count_objects = 0;
	ofile.read((char*)&count_objects, sizeof(int));

	for (int i = 0; i < count_objects; i++) {
		ofile.read((char*)&object[i]->object_pos.x, sizeof(int));
		ofile.read((char*)&object[i]->object_pos.y, sizeof(int));
	}
	int x, y;
	ofile.read((char*)&x, sizeof(int));
	ofile.read((char*)&y, sizeof(int));
	square->set_x(x);
	square->set_y(y);
	ofile.read((char*)&player_2, sizeof(bool));
	ofile.close();
}
