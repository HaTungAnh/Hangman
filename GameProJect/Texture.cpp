#include "Texture.h"
#include <iostream>

void Texture::load(SDL_Renderer* renderer) {
	SDL_Surface* sur;

	SDL_Log("---load texture : '%s'", PATH.c_str());

	sur = IMG_Load(PATH.c_str());
	if (sur == NULL) {
		SDL_Log("Cannot load Texture %s", SDL_GetError());
	}

	w = sur->w;
	h = sur->h;

	texture = SDL_CreateTextureFromSurface(renderer, sur);
	if (texture == NULL) {
		SDL_Log("Cannot create Texture %s", SDL_GetError());
	}

	SDL_FreeSurface(sur);
	sur = NULL;
}