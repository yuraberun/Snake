#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>
#include <string>
class Texture
{
private:
	int TextureWidth, TextureHeight;
	SDL_Texture* texture;
public:

	Texture()
	{
		texture = NULL;
		TextureWidth = 0;
		TextureHeight = 0;
	}

	void render(int x, int y, SDL_Renderer*& renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)
	{
		SDL_Rect renderQuad = { x, y, TextureWidth, TextureHeight };
		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}
		SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
	}

	void free()
	{
		if (texture != NULL)
		{
			SDL_DestroyTexture(texture);
			texture = NULL;
			TextureWidth = 0;
			TextureHeight = 0;
		}
	}

	auto loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer*& renderer, TTF_Font*& gFont)
	{
		free();
		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		TextureWidth = textSurface->w;
		TextureHeight = textSurface->h;
		SDL_FreeSurface(textSurface);
		return texture != NULL;
	}
	int getWidth()
	{
		return TextureWidth;
	}

	int getHeight()
	{
		return TextureHeight;
	}

	~Texture()
	{
		free();
	}
};

