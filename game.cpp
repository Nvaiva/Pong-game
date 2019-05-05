#include "game.h"
#define BLOCK 2
#define DETAILS 3
#include <vector>
#include <iostream>


game::game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Window was initialized " << std::endl;
		win = SDL_CreateWindow("Awesome pong game!", 100, 100, 640, 400, SDL_WINDOW_SHOWN);
		if (win) {
			std::cout << "Window was created " << std::endl;
		}
		renderer = SDL_CreateRenderer(win, -1, 0);
		if (renderer) {
			std::cout << "Renderer was created " << std::endl;
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		}
		isRunning = true;
	}
	//block1 = new wall_1(0, 0, BLOCK_W, BLOCK_H);
	object.push_back(block1 = new wall_1(0, 0, BLOCK_W, BLOCK_H));
	std::cout << block1->object_pos.w << std::endl;

	block2 = new wall_2(610, 0, BLOCK_W, BLOCK_H);
	object.push_back(block2);

	object.push_back(&square);
	
	for (int i = 0; i < BLOCK; i++)
		object[i]->load_image("Block.png", renderer);
	
	object[2]->load_image("ball.png", renderer);
	std::cout <<"objects[0] w reikðme kur turetu bus skaicius" <<object[0]->object_pos.w << std::endl;
	std::cout << "tas pats tik per block1 "<<block1->object_pos.w << std::endl;
	//object[0]->object_pos = { 0, 0, BLOCK_H, BLOCK_W };
	//object[1]->object_pos = {610, 0, BLOCK_H, BLOCK_W };
	object[2]->object_pos = { 100, 100, 25, 25 };
}
void game::events()
{
	int vell_x, vell_y;
	for (int i = 0; i < DETAILS ; i++)
		object[i]->events();
	if (collision1() || collision2()) {
		vell_x = square.get_x();
		square.set_x(-vell_x);
	}
}
bool game::collision1()
{
	
	if (((square.object_pos.y >= block1->object_pos.y) && (square.object_pos.x > block1->object_pos.x))
		&& (square.object_pos.x < (block1->object_pos.x + BLOCK_H))
			&& (square.object_pos.y < (block1->object_pos.y + BLOCK_W))) {
		return true;
	}
	else {
		return false;
	}
}
bool game::collision2()
{

	if (((square.object_pos.y <= block2->object_pos.y) && (square.object_pos.x < block2->object_pos.x))
		&& (square.object_pos.x > (block2->object_pos.x + BLOCK_H))
		&& (square.object_pos.y > (block2->object_pos.y + BLOCK_W))) {
		return true;
	}
	else {
		return false;
	}
}
void game::update() 
{
	SDL_RenderClear(renderer);
	for (int i = 0; i < DETAILS; i++)
		SDL_RenderCopy(renderer, object[i]->tex, NULL, &object[i]->object_pos);
	SDL_RenderPresent(renderer);

	if(object[0]->isRunning == false)
		isRunning = false;
}
game::~game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	//delete ball;
	SDL_Quit();
}
