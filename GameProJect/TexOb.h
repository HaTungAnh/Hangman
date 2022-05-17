#pragma once
#include "GameObject.h"
#include "Util.cpp"
class TexOb : public GameObject
{
private:
	float sizex,sizey;
	bool visiable = true;

	Text* text;

public:
	void setVisible(bool isVisivle) {
		visiable = isVisivle;
	}

	TexOb(){
		sizex = 1;
		sizey = 1;
		text = NULL;
	}

	void setPos(float x, float y) override;

	void setSize(float x, float y);

	void init(SDL_Renderer* renderer) override;

	void render(SDL_Renderer* renderer) override;

	void eventCheck(SDL_Event* Event) override;

	void tick() override;

	void free() override;

	void setTexture(Texture* a) override;

	void setTexture(Text* a);

	void setColorMod(Uint8 r, Uint8 g, Uint8 b) {
		SDL_SetTextureColorMod((text == NULL) ? texture->getTexture() : text->texture, r, g, b);
	}

	~TexOb();
};

