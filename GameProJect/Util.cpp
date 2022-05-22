#pragma once
#include "Util.h"
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include "Vector2D.h"


void Util::load(Text &res , SDL_Renderer* renderer, std::string text, std::string font, int size) {
	TTF_Font* f = TTF_OpenFont(font.c_str(), size);
	SDL_Surface* sur;
	if (f == NULL)
	{
		SDL_Log("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	SDL_Color color = { 255,255,255,255 };
	sur = TTF_RenderText_Solid(f, text.c_str(), color);
	if (sur == NULL) {
		SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	res.w = sur->w;
	res.h = sur->h;
	res.texture = SDL_CreateTextureFromSurface(renderer, sur);
	if (res.texture == NULL)
	{
		printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
	}
	SDL_FreeSurface(sur);
	sur = NULL;
	TTF_CloseFont(f);
	f = NULL;
	return;
}

void Util::deload(Text& res) {
	SDL_DestroyTexture(res.texture);
}

SDL_Rect Util::toSDL_Rect(Vector2D position, int w, int h) {
	SDL_Rect a;
	a.x = (int)position.getX();
	a.y = (int)position.getY();
	a.w = w;
	a.h = h;
	return a;
}