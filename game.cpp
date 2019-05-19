#include "game.h"
#include <vector>
#include <iostream>

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Window was initialized " << std::endl;
		win = SDL_CreateWindow("Awesome pong game!", REN_X, REN_Y, REN_W, REN_H, SDL_WINDOW_SHOWN);
		if (win) {
			std::cout << "Window was created " << std::endl;
		}
		renderer = SDL_CreateRenderer(win, -1, 0);
		if (renderer) {
			std::cout << "Renderer was created " << std::endl;
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		}
		isRunning = true;
		startAgain = false;
	}

	//initialize objects
	block1 = new Wall_1(0, 0, BLOCK_H, BLOCK_W);
	object.push_back(block1);
	block2 = new Wall_2(610, 0, BLOCK_H, BLOCK_W);
	object.push_back(block2);

	square = new Ball(100, 100, SQUARE_H_W, SQUARE_H_W);
	object.push_back(square);

	//upload images to these objects
	for (int i = 0; i < BLOCK_QUANTITY; i++)
		object[i]->load_image("Block.png", renderer);

	object[2]->load_image("ball.png", renderer);
	balls.push_back(square);
	game_over = Image_texture::load_texture("gameOver.png", renderer);

	//if load game was pressed
	bool a;
	if (!(a = start()))
		load();
	
	
}
bool Game::start()
{
	intro = Image_texture::load_texture("Intro.png", renderer);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, intro, NULL, NULL);
	SDL_RenderPresent(renderer);
	bool t = true;
	while (t) {
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				startAgain = false;
				t = false;
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (event.motion.x >= 186 && event.motion.x <= 446 && event.motion.y >= 168 && event.motion.y <= 234)
					return true;
				if (event.motion.x >= 180 && event.motion.x <= 442 && event.motion.y >= 168 && event.motion.y <= 314)
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
	//creating additional ball
	//
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
			startAgain = false;
		}
		if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym)
			{
			case SDLK_KP_PLUS:
				int num = additionals.size();
				size_t nr = object.size();
				if (balls.size() > 1) {
					additionals.push_back(new Additional_ball(*additionals[num-1]));
					std::cout << additionals[num]->get_count() << std::endl;
				}
				else {
					additionals.push_back(new Additional_ball(100, 100, SQUARE_H_W, SQUARE_H_W));
					std::cout << additionals[num]->get_count() << std::endl;
				}
				object.push_back(additionals[num]);
				object[nr]->load_image("ball.png", renderer);
				object[nr] = dynamic_cast<Ball*>(object[nr]);
				balls.push_back(additionals[num]);
			}
		}
	}
	for (size_t i = 0; i < object.size(); i++)
		object[i]->events();
	for (size_t i = 0; i < balls.size(); i++) {
		int vell_x;
		if (collision1(balls[i]) || collision2(balls[i])) {
			vell_x = balls[i]->get_x();
			balls[i]->set_x(-vell_x);
		}
		else if (balls[i]->object_pos.x == 0 || balls[i]->object_pos.x == REN_W) {
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
						isRunning = false;
						startAgain = false;
						t = false;
						break;
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym)
						{
						case SDLK_KP_ENTER:
							isRunning = false;
							startAgain = true;
							t = false;
							break;
						}
					}
				}
			}
		}
	}
	}
bool Game::collision1(Ball *square) const
{
	if (((square->object_pos.y >= block1->object_pos.y) && (square->object_pos.x > block1->object_pos.x))
		&& (square->object_pos.x < (block1->object_pos.x + BLOCK_H))
			&& (square->object_pos.y < (block1->object_pos.y + BLOCK_W))) {
		return true;
	}
	else {
		return false;
	}
	
}
bool Game::collision2(Ball *square) const
{

	if (((square->object_pos.y + SQUARE_H_W >= block2->object_pos.y) && (square->object_pos.x < block2->object_pos.x))
		&& (square->object_pos.x + SQUARE_H_W >= (block2->object_pos.x))
		&& (square->object_pos.y <= (block2->object_pos.y + BLOCK_W))) {
		return true;
	}
	else {
		return false;
	}
}
void Game::update()
{
	SDL_RenderClear(renderer);
	for (size_t i = 0; i < object.size(); i++)
		SDL_RenderCopy(renderer, object[i]->tex, NULL, &object[i]->object_pos);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderPresent(renderer);

	for (size_t i = 0; i < object.size(); i++) {
	if (object[i]->isRunning == false) {
		save();
		isRunning = false;
	}
	}
	if (!isRunning && t== true)
		save();
	
		
	if (object[0]->startAgain == false)
		startAgain = false;
}
Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_DestroyTexture(game_over);
	game_over = nullptr;
	
	for (size_t i = 0; i < object.size(); i++) {
		delete object[i];
	}
		

	SDL_Quit();
}
void Game::save()
{
	std::ofstream ofile("result.bin", std::ios::binary);
	ofile.clear();

	int count = object.size();
	ofile.write((char*)&count, sizeof(int));
	for (size_t i = 0; i < object.size(); i++) {
		ofile.write((char*)&object[i]->object_pos.x, sizeof(int));
		ofile.write((char*)&object[i]->object_pos.y, sizeof(int));
	}
	for (size_t i = 0; i < balls.size(); i++) {
		int x = balls[i]->get_x();
		int y = balls[i]->get_y();
		ofile.write((char*)&x, sizeof(int));
		ofile.write((char*)&y, sizeof(int));
	}
	additional->set_count(0);

	ofile.close();
}
void Game::load() 
{
	
	std::ifstream ofile("result.bin", std::ios::binary);
	ofile.seekg(0);
	int count_objects = 0;
	ofile.read((char*)&count_objects, sizeof(int));

	for (int i = 0; i < BLOCKS; i++) {
		ofile.read((char*)&object[i]->object_pos.x, sizeof(int));
		ofile.read((char*)&object[i]->object_pos.y, sizeof(int));
	}

	if (count_objects > (BLOCKS+1)) {
		for (int i = (BLOCKS+1); i < (count_objects); i++) {

			additional = new Additional_ball(100, 100, SQUARE_H_W, SQUARE_H_W);
			object.push_back(additional);
			object[i]->load_image("ball.png", renderer);
			object[i] = dynamic_cast<Ball*>(object[i]);
			balls.push_back(additional);
		}
	}
	for (size_t i = BLOCKS; i < object.size(); i++) {
		ofile.read((char*)&object[i]->object_pos.x, sizeof(int));
		ofile.read((char*)&object[i]->object_pos.y, sizeof(int));
	}
	for (size_t i = 0; i < balls.size(); i++) {
		int x, y;
		ofile.read((char*)&x, sizeof(int));
		ofile.read((char*)&y, sizeof(int));
		balls[i]->set_x(x);
		balls[i]->set_y(y);
	}
	ofile.close();
}