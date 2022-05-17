#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>
class Texture
{
private:
	SDL_Texture* texture;
	int w;
	int h;

	std::string PATH;

public:
	Texture(){
		texture = NULL;
		w = 0;
		h = 0;
	}

	Texture(std::string path) {
		PATH = path;
	}

	void load(SDL_Renderer* renderer);

	int getWidth() {
		return w;
	}

	int getHeight() {
		return h;
	}

	SDL_Texture* getTexture() {
		return texture;
	}

	void free() {
		if (texture == NULL) return;
		SDL_DestroyTexture(texture);
		texture = NULL;
	}

	~Texture() {
		free();
	}

};

