#pragma once
#include <SDL.h>
#include <string>
#include "Vector2D.h"
#include "Texture.h"


class Animator {

};

class GameObject {

protected:
	std::string CLASS;

	std::string NAME;

	std::string PATH;
	
	Texture* texture;

	Vector2D position;
	
public:
	GameObject(){
		PATH = "";
		NAME = "";
		CLASS = "";
		texture = NULL;
		position = Vector2D(0, 0);
	}

	GameObject(std::string _NAME, std::string _PATH){
		NAME = _NAME;
		PATH = _PATH;
	}

	virtual void init(SDL_Renderer* renderer) = 0;

	virtual void render(SDL_Renderer* renderer) = 0;

	virtual void eventCheck(SDL_Event* Event) = 0;

	virtual void tick() = 0;

	virtual void free() = 0;

	virtual std::string getName() {
		return NAME;
	}

	virtual void setTexture(Texture* a) {
		texture = a;
	}

	virtual void a();

	Vector2D getPos() {
		return position;
	}

	virtual void setPos(float x, float y){}

	void setPosition(Vector2D v) {
		position = v;
	}

	~GameObject() {
	}

};

