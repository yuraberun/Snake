#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
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

	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
	{
		SDL_Rect renderQuad = { x, y, TextureWidth, TextureHeight };
		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}
		SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
	}

	auto loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* gFont)
	{
		free();
		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		TextureWidth = textSurface->w;
		TextureHeight = textSurface->h;
		SDL_FreeSurface(textSurface);
	}

	bool loadFromFile(std::string path, SDL_Renderer* renderer)
	{
		SDL_Texture* newTexture = NULL;
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		TextureWidth = loadedSurface->w;
		TextureHeight = loadedSurface->h;
		SDL_FreeSurface(loadedSurface);
		texture = newTexture;
		return texture != NULL;
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

	~Texture()
	{
		free();
	}
};
