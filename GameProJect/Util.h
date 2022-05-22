#pragma once
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include "Vector2D.h"
#include <iostream>

struct Text {
	SDL_Texture* texture;
	int w;
	int h;
	int r = 0, g = 0, b = 0, a = 255;
	int test = 0;

	~Text() {
		if (texture != NULL) {
			SDL_DestroyTexture(texture);
			texture = NULL;
		}
	}
};

namespace Util {
	void load(Text& res, SDL_Renderer* renderer, std::string text, std::string font, int size);

	void deload(Text& res);

	SDL_Rect toSDL_Rect(Vector2D position, int w, int h);
}

static int tool_theard(void* ptr) {
	Text* a = (Text*)ptr;
	SDL_Delay(3000);
	Util::deload(*a);
	a->a = 200;
	return 0;
}