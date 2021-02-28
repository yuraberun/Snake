#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <math.h>
#include <string>
#include <stdio.h>
#include <vector>
#include "Texture.cpp"
#include "Visualizator.cpp"
#include <iostream>

int window_width = 1920;
int window_height = 1080;

SDL_Window* my_window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* gFont = NULL;
Texture Score;
int score = 0;
SDL_Color TextColor = { 255,255,255 };
Visualizer visualizer;

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		success = false;
	else
	{
		my_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);
		if (my_window == NULL)
			success = false;
		else
		{
			renderer = SDL_CreateRenderer(my_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
				success = false;
			else
			{
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
					success = false;
				if (TTF_Init() == -1)
					success = false;
			}
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	gFont = TTF_OpenFont("lazy.ttf", 80);
	if (gFont == NULL)
		success = false;
	return success;
}

void close()
{
	Score.free();
	TTF_CloseFont(gFont);
	gFont = NULL;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(my_window);
	my_window = NULL;
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

int main(int argc, char* args[])
{
	srand(time(0));
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			Uint32 Ticks;
			Uint32 Ticks2 = 0;
			int Delay = 380;
			bool ExistenceOfFruit = false;
			int FruitX, FruitY;
			visualizer.LoadGameField(renderer);    //Download all textures
			std::string direction = "";   //Head direction
			int SnakeBody = 1;            //The number of elements of the snake's body

			SDL_Event e;
			bool quit = false;
			while (!quit)
			{
				Ticks = SDL_GetTicks();
				if (Ticks - Ticks2 > Delay)
				{
					while (SDL_PollEvent(&e) != 0)
					{
						if (e.type == SDL_QUIT)
						{
							quit = true;
						}
						if (e.key.repeat == 0 && e.type == SDL_KEYDOWN)
						{
							if (e.key.keysym.sym == SDLK_RIGHT)
								direction = "RIGHT";
							if (e.key.keysym.sym == SDLK_LEFT)
								direction = "LEFT";
						}
					}

					visualizer.display_background(renderer, false);
					visualizer.DisplaySnake(renderer, SnakeBody, direction);

					if (!ExistenceOfFruit)
					{
						FruitX = rand() % 1350 + 270;
						FruitY = rand() % 630 + 200;
						ExistenceOfFruit = true;
					}

					if (visualizer.EatingFruit(FruitX, FruitY))
					{
						FruitX = 3000;
						FruitY = 3000;
						ExistenceOfFruit = false;
						SnakeBody++;
						if (Delay >= 150 && Delay <= 200)
						{
							Delay--;
							score += 20;
						}
						if (Delay >= 200 && Delay <= 250)
						{
							score += 15;
							Delay -= 2;
						}
						if (Delay >= 250 && Delay <= 300)
						{
							score += 12;
							Delay -= 3;
						}
						if (Delay >= 300 && Delay <= 350)
						{
							score += 11;
							Delay -= 4;
						}
						if (Delay >= 350)
						{
							score += 10;
							Delay -= 5;
						}
					}
					visualizer.DisplayFruit(renderer, FruitX, FruitY);

					Score.loadFromRenderedText("S C O R E:", TextColor, renderer, gFont);
					Score.render(renderer, 700, 110, NULL, 0, NULL, SDL_FLIP_NONE);

					Score.loadFromRenderedText(std::to_string(score), TextColor, renderer, gFont);
					Score.render(renderer, 1100, 110, NULL, 0, NULL, SDL_FLIP_NONE);

					direction = "";

					SDL_RenderPresent(renderer);

					Ticks2 = Ticks;

					if (!visualizer.die(SnakeBody))
					{
						visualizer.DisplayDie(renderer, 800, 430);
						SDL_RenderPresent(renderer);
						SDL_Delay(2000);
						break;
					}
				}
			}
		}
	}
	close();
	return 0;
}
