#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <string>
#include <stdio.h>
#include "Texture.cpp"
#include <iostream>
#include <vector>
class Visualizer
{
private:
	Texture all_textures;      //All textures in one texture
	SDL_Rect GameTextures[100];       //An array of game textures
	SDL_Rect BackgroundTextures[3];   //An array of Background textures
	int CoordinateListX[100];  //The array of coordinates x elements of the body of the snake
	int CoordinateListY[100];  //The array of coordinates in the elements of the snake's body
	int GegreesList[100];      //Array of directions of snake body elements in degrees (0 (360, 360), 90 (-270), 180 (-180), 270 (-90))

	//New positions of the chairman
	int NewPositionX;
	int NewPositionY;
public:

	//Creating texture
	void CreatingTexture(SDL_Rect& NewTexture, int x, int y, int w, int h, SDL_Renderer* renderer)
	{
		all_textures.loadFromFile("my_texture3.png", renderer);
		NewTexture.x = x;
		NewTexture.y = y;
		NewTexture.w = w;
		NewTexture.h = h;
	}

	//Texture display
	void DisplayTexture(SDL_Rect& Texture, int x, int y, int limitX, int limitY, int stepX, int stepY, SDL_Renderer* renderer)
	{
		for (int i = x; i <= limitX; i += stepX)
		{
			for (int j = y; j <= limitY; j += stepY)
			{
				all_textures.render(renderer, i, j, &Texture, 0, NULL, SDL_FLIP_NONE);
			}
		}
	}

	void LoadGameField(SDL_Renderer* renderer)
	{
		CreatingTexture(BackgroundTextures[0], 0, 0, 190, 190, renderer);   //Creating a background texture
		CreatingTexture(BackgroundTextures[1], 208, 0, 16, 16, renderer);   //Creating a wall texture
		CreatingTexture(BackgroundTextures[2], 240, 0, 16, 16, renderer);   //Creating a background texture behind the walls
		CreatingTexture(GameTextures[0], 0, 208, 63, 63, renderer);         //Creating a snake head texture
		CreatingTexture(GameTextures[1], 0, 336, 63, 63, renderer);         //Creating a snake tail texture
		CreatingTexture(GameTextures[98], 64, 224, 47, 47, renderer);       //Creating a fruit texture
		CreatingTexture(GameTextures[99], 0, 436, 300, 168, renderer);

		for (int i = 2; i <= 97; i++)     //Creating a snake body texture
		{
			CreatingTexture(GameTextures[i], 0, 272, 63, 63, renderer);   //body textures so much,
		}                                                                 //because so do the mechanics of the snake

		//Assign initial coordinates to the snake's head
		CoordinateListX[0] = 950;
		CoordinateListY[0] = 508;
		GegreesList[0] = 0;

		//Assign initial coordinates to the snake's tail
		CoordinateListX[1] = 950;
		CoordinateListY[1] = 616;
		GegreesList[1] = 0;

		//Assign initial coordinates to the snake's body
		CoordinateListX[2] = 950;
		CoordinateListY[2] = 572;
		GegreesList[2] = 0;

	}
	void display_background(SDL_Renderer* renderer, bool DisplayDieBackGround)
	{
		if (DisplayDieBackGround)
			DisplayTexture(BackgroundTextures[2], 0, 0, 1920, 1080, 1, 1, renderer);
		else
		{
			DisplayTexture(BackgroundTextures[0], 0, 0, 1920, 1080, 190, 190, renderer);   //The main background
			DisplayTexture(BackgroundTextures[2], 0, 0, 1920, 174, 15, 6, renderer);       //Background behind the wall
			DisplayTexture(BackgroundTextures[2], 0, 893, 1920, 1080, 15, 1, renderer);    //Background behind the wall
			DisplayTexture(BackgroundTextures[1], 238, 174, 1658, 175, 1, 1, renderer);    //The upper wall
			DisplayTexture(BackgroundTextures[1], 238, 883, 1648, 884, 1, 1, renderer);    //Lower wall
			DisplayTexture(BackgroundTextures[2], 0, 174, 238, 893, 14, 15, renderer);     //Background behind the wall
			DisplayTexture(BackgroundTextures[2], 1657, 174, 1920, 893, 14, 15, renderer); //Background behind the wall
			DisplayTexture(BackgroundTextures[1], 238, 174, 239, 893, 1, 15, renderer);    //Left wall
			DisplayTexture(BackgroundTextures[1], 1647, 174, 1648, 893, 1, 15, renderer);  //Right wall
		}
	}
	void DisplaySnake(SDL_Renderer* renderer, int ShakeBody, std::string Direction)
	{

		//If the SDLK_RIGHT key was pressed, the direction of the snake's head changes
		if (Direction == "RIGHT")
		{
			//This assignment is required for intuitive control
			if (GegreesList[0] == 180 || GegreesList[0] == -180)
				GegreesList[0] = 0;
			GegreesList[0] += 90;
		}

		//If the SDLK_LEFT key was pressed, the direction of the snake's head changes
		if (Direction == "LEFT")
		{
			//This assignment is required for intuitive control
			if (GegreesList[0] == 180 || GegreesList[0] == -180)
				GegreesList[0] = 0;
			GegreesList[0] -= 90;
		}

		//Checking the direction of the head, and assigning the appropriate coordinates to the appropriate direction
		if (GegreesList[0] == 0 || GegreesList[0] == -360 || GegreesList[0] == 360)
		{
			NewPositionX = CoordinateListX[0];
			NewPositionY = CoordinateListY[0] - 63;

		}
		if (GegreesList[0] == 90)
		{
			NewPositionX = CoordinateListX[0] + 63;
			NewPositionY = CoordinateListY[0];

		}
		if (GegreesList[0] == 180 || GegreesList[0] == -180)
		{
			NewPositionX = CoordinateListX[0];
			NewPositionY = CoordinateListY[0] + 63;

		}
		if (GegreesList[0] == -90)
		{
			NewPositionX = CoordinateListX[0] - 63;
			NewPositionY = CoordinateListY[0];


		}

		//The next one is assigned to each element, new coordinates are assigned to the head
		CoordinateListX[1] = CoordinateListX[ShakeBody + 1];
		CoordinateListY[1] = CoordinateListY[ShakeBody + 1];
		GegreesList[1] = GegreesList[ShakeBody + 1];


		for (int i = 0; i < 96; i++)
		{
			if (ShakeBody + 2 - i == 2)
				break;
			CoordinateListX[ShakeBody + 2 - i] = CoordinateListX[ShakeBody + 1 - i];
			CoordinateListY[ShakeBody + 2 - i] = CoordinateListY[ShakeBody + 1 - i];
			GegreesList[ShakeBody + 2 - i] = GegreesList[ShakeBody + 1 - i];
		}

		CoordinateListX[2] = CoordinateListX[0];
		CoordinateListY[2] = CoordinateListY[0];
		GegreesList[2] = GegreesList[0];

		CoordinateListX[0] = NewPositionX;
		CoordinateListY[0] = NewPositionY;


		//Output of the snake in render
		for (int i = 0; i <= ShakeBody + 1; i++)
		{
			all_textures.render(renderer, CoordinateListX[i], CoordinateListY[i], &GameTextures[i], GegreesList[i], NULL, SDL_FLIP_NONE);
		}
	}

	void DisplayFruit(SDL_Renderer* renderer, int FruitX, int FruitY)
	{
		all_textures.render(renderer, FruitX, FruitY, &GameTextures[98], 0, NULL, SDL_FLIP_NONE);
	}

	void DisplayDie(SDL_Renderer* renderer, int x, int y)
	{
		all_textures.render(renderer, x, y, &GameTextures[99], 0, NULL, SDL_FLIP_NONE);
	}

	//Check if the snake ate the fruit
	bool EatingFruit(int FruitX, int FruitY)
	{
		for (int i = FruitX; i < FruitX + 47; i++)
		{
			for (int j = FruitY; j < FruitY + 47; j++)
			{
				for (int x = CoordinateListX[0] + 5; x <= CoordinateListX[0] + 54; x++)
				{
					for (int y = CoordinateListY[0] + 5; y <= CoordinateListY[0] + 54; y++)
					{
						if (x == i && y == j)
							return true;
					}
				}
			}
		}
		return false;
	}

	//Check the conditions of the end of the game
	bool die(int ShakeBody)
	{
		//exit from the field
		if (CoordinateListY[0] < 174 || CoordinateListY[0] > 880 || CoordinateListX[0] < 238 || CoordinateListX[0] > 1600)
			return false;

		//collision with the tail
		for (int n = 1; n <= ShakeBody; n++)
		{
			for (int i = CoordinateListX[n + 4] + 15; i <= CoordinateListX[n + 4] + 30; i++)
			{
				for (int j = CoordinateListY[n + 4] + 15; j <= CoordinateListY[n + 4] + 30; j++)
				{
					if (CoordinateListX[0] + 23 == i && CoordinateListY[0] + 21 == j)//|| CoordinateListX[0] + 40 == i && CoordinateListY[0] == j + 21 || CoordinateListX[0] + 23 == i && CoordinateListY[0] + 40 == j || CoordinateListX[0] == i && CoordinateListY[0] + 21 == j)
						return false;
				}
			}
		}
		return true;
	}
};