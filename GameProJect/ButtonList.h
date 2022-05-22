#pragma once
#include "GameObject.h"
#include <vector>
#include "TexOb.h"
#include <functional>
#include <map>

struct SButton {
	TexOb* button;
	std::function<void()> action;

	SButton(TexOb* _button, std::function<void()> _action) {
		button = _button;
		action = _action;
	}
};

class ButtonList : GameObject
{
private:
	std::map<int,SButton> buttonlist;

	

	int length = 0;

	int cur = 0;

public:
	bool isChangeButton = true;

	void canChangeButton(bool c) {
		isChangeButton = c;
	}

	void init(SDL_Renderer* renderer) override;

	void render(SDL_Renderer* renderer) override;

	void eventCheck(SDL_Event* Event) override;

	void tick() override;

	void free() override;

	std::string getName() override {
		return NAME;
	}

	void setTexture(Texture* a) override {
		texture = a;
	}

	void addButton(TexOb* button, std::function<void()> action, int index) {
		buttonlist.insert(std::pair<int, SButton>(index, SButton(button, action)));
		length++;
	}
	SButton getButton(int index) {
		std::map<int, SButton>::iterator i = buttonlist.find(index);
		if (i != buttonlist.end()) {
			return (*i).second;
		}
	}
	SButton getButton() {
		std::map<int, SButton>::iterator iter = buttonlist.begin();
		for (int i = 0; i <= cur; i++) {
			iter++;
		}
		return (*iter).second;
	}
};

