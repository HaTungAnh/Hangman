#pragma once
#include "GameObject.h"

class Button : GameObject
{
	void setAction() {

	}

	void init(SDL_Renderer* renderer) override;

	void render(SDL_Renderer* renderer) override;

	void eventCheck(SDL_Event* Event) override;

	void tick() override;

	void free() override;

	std::string getName() override {
		return NAME;
	}

	virtual void setTexture(Texture* a) override {
		texture = a;
	}
};

