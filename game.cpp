#include "game.h"
#include <vector>
#include <iostream>
clock_t Game::time = clock();
Game::Game()
{
	//time = clock();
	nr_time = 1;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		TTF_Init();
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
		middle_line_pos = { (REN_W - REN_X + 80) / 2, 0,2,REN_H };
		font = TTF_OpenFont("Arial.ttf", 20); //Arial font 
		color = { 255, 255, 255 }; //font color
		points1_pos = { 250,30,40,40 }; //position of block1 points
		points2_pos = { 330,30,40,40 }; //position of block2 points
		game_over_pos = {140,160,400,30}; //game over text position
		points = { 0,0 };
	}
	else {
		throw error("SDL_Init error ");
	}
	//initialize objects
	block1 = new Wall_1(5, 5, BLOCK_W, BLOCK_H);
	block1->default_coordinates();
	object.push_back(block1);
	blocks.push_back(block1);

	block2 = new Wall_2(615, 5, BLOCK_W, BLOCK_H);
	block2->default_coordinates();
	object.push_back(block2);
	blocks.push_back(block2);

	square = new Ball(100, 100, SQUARE_H_W, SQUARE_H_W);
	square->default_coordinates();
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
	middle_line = Image_texture::load_texture("middle.png", renderer);
	if (middle_line == nullptr) {
		throw error("Middle lines texture was not loaded");
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
		if (nr_time >= 2) {
			object.erase(std::remove_if(object.begin(), object.end(), [&](const Object* x) { return x == ad_block; }), object.end());
			blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [&](const Object* x) {return x == ad_block; }), blocks.end());
		}
		ad_block = new Additional_wall(0, 0, 0, 0);
		blocks.push_back(ad_block);
		object.push_back(ad_block);
		ad_block->load_image("Block.png", renderer);
		if (ad_block->tex == nullptr)
			throw error("Block image for additioal block was not created ");
		if (square->object_pos.x < middle_line_pos.x) {
			ad_block->object_pos.x = rand() % ((REN_W - REN_X - 80) - (middle_line_pos.x + 50) + 1) + (middle_line_pos.x + 50);
			ad_block->object_pos.y = rand() % REN_H + 1;
			ad_block->object_pos.w = 15;
			ad_block->object_pos.h = 50;
		}
		else
		{
		ad_block->object_pos.x = rand() % ((middle_line_pos.x - 50) - 80 + 1) + 80;
		ad_block->object_pos.y = rand() % REN_H + 0;
		ad_block->object_pos.w = 15;
		ad_block->object_pos.h = 50;
		}
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
	for (blo = blocks.begin(); blo != blocks.end(); ++blo) {
		if (collision1(square, (*blo))) {
			vell_x = square->get_x();
			square->set_x(-vell_x);
		}
	}
	if (square->object_pos.x < 5 || square->object_pos.x > REN_W - 5) {
		if (square->object_pos.x < 5) {
			block2_points_new += 1;
		}
		else {
			block1_points_new += 1;
		}
		game_over = Image_texture::load_ttf("Game over. Press enter to play again", font, color, renderer);
		SDL_RenderCopy(renderer, game_over, NULL, &game_over_pos);

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
bool Game::collision1(Ball *square, Object* wall) const
{
	//collision with walls right side
	if (((square->object_pos.x > wall->object_pos.x) && (square->object_pos.x <= wall->object_pos.x + BLOCK_W))
		&& ((square->object_pos.y + SQUARE_H_W >= wall->object_pos.y) && (square->object_pos.y <= wall->object_pos.y + BLOCK_H))) {
		return true;
	}
	//collision with walls left side
	if ((square->object_pos.x + SQUARE_H_W <= wall->object_pos.x + BLOCK_W) && (square->object_pos.x + SQUARE_H_W >= wall->object_pos.x)
		&& (square->object_pos.y + SQUARE_H_W <= wall->object_pos.y + BLOCK_H) && (square->object_pos.y + SQUARE_H_W >= wall->object_pos.y)) {
		return true;
	}
	//collision with walls upper side
	if ((square->object_pos.x <= wall->object_pos.x + BLOCK_W) && (square->object_pos.x + SQUARE_H_W >= wall->object_pos.x)
		&& (square->object_pos.y == wall->object_pos.y)) {
		return true;
	}
	//colllsion with walls bottom side
	if (((square->object_pos.x <= wall->object_pos.x) && (square->object_pos.x >= wall->object_pos.x + BLOCK_H))
		&& (square->object_pos.y == wall->object_pos.y + BLOCK_H)){
		return true;
	}
	return false;
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
	if (block1_points_new == 0 && block2_points_new == 0) {
		points1 = Image_texture::load_ttf("0", font, color, renderer);
		points2 = Image_texture::load_ttf("0", font, color, renderer);
	}
	
	if (std::any_of(points.begin(), points.end(), [&](size_t a) {return (a == block1_points_new || a == block2_points_new);})) {
		points[0] = block1_points_new;
		points[1] = block2_points_new;
		a = std::to_string(points[0]);
		b = std::to_string(points[1]);
		points1 = Image_texture::load_ttf(a.c_str(), font, color, renderer);
		points2 = Image_texture::load_ttf(b.c_str(), font, color, renderer);
	}
	SDL_RenderCopy(renderer, points2, NULL, &points2_pos);
	SDL_RenderCopy(renderer, points1, NULL, &points1_pos);
	SDL_RenderCopy(renderer, middle_line, NULL, &middle_line_pos);
	SDL_RenderCopy(renderer,middle_line, NULL,&middle_line_pos);

	std::for_each(object.begin(), object.end(), [&](Object* a) {a->render(renderer,a->pos); });
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
	TTF_CloseFont(font);
	TTF_Quit();
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
	ofile.write((char*)&block1_points_new, sizeof(size_t));
	ofile.write((char*)&block2_points_new, sizeof(size_t));
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
	ofile.read((char*)&block1_points_new, sizeof(size_t));
	ofile.read((char*)&block2_points_new, sizeof(size_t));
	ofile.close();
}
void Game::game_start_again() {
	blo = std::remove(blocks.begin(), blocks.end(), ad_block);
	it = std::remove(object.begin(), object.end(), ad_block);
	time = 0;
	square->object_pos.x = square->x;
	square->object_pos.y = square->y;
	square->object_pos.w = square->w;
	square->object_pos.h = square->h;
	square->set_x(square->vell_x_d);
	square->set_y(square->vell_y_d);

}