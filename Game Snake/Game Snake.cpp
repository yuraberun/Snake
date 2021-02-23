#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <math.h>
#include <string>
#include <stdio.h>
#include "Texture.h"

const int window_width = 1920;
const int window_height = 1080;

SDL_Window* my_window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* gFont = NULL;

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
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
					success = false;
				{
					if (TTF_Init() == -1)
						success = false;
				}
			}
		}
	}
	return success;
}

void close()
{
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
	return 0;
}
