#include "ButtonList.h"
#include <iostream>

void ButtonList::init(SDL_Renderer* renderer)
{
}

void ButtonList::render(SDL_Renderer* renderer)
{
	std::map<int, SButton>::iterator iter = buttonlist.begin();
	for (int i = 0; i < length; i++) {
		if (i == cur) {
			(*iter).second.button->setColorMod(100, 100, 100);
			//SDL_SetRenderDrawColor(renderer, 0.5, 0.5, 0.5, 100);
			(*iter).second.button->render(renderer);
			//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
			(*iter).second.button->setColorMod(255, 255, 255);

			Vector2D pos = (*iter).second.button->getPos();

			(*iter).second.button->setPosition(pos + Vector2D(5, 5));

			(*iter).second.button->render(renderer);

			(*iter).second.button->setPosition(pos);
			//std::cout << "select: " << pos.getX() << " " << pos.getY() << " ";
		}
		else {
			(*iter).second.button->render(renderer);

			Vector2D pos = (*iter).second.button->getPos();
			//std::cout << "unselected: " << pos.getX() << " " << pos.getY() << " ";
		}
		
		//std::cout << cur << " " << i << std::endl;
		iter++;
	}
}

void ButtonList::eventCheck(SDL_Event* Event)
{
	if (Event->type == SDL_KEYDOWN) {
		switch (Event->key.keysym.sym){
			case SDLK_TAB: 
				cur++;
				cur = cur % length;
				break;
				
			case SDLK_SPACE: {
				std::map<int, SButton>::iterator iter = buttonlist.begin();
				for (int i = 0; i < cur; i++) {
					iter++;
				}
				std::function<void()> b = (*iter).second.action;
				b();
				break;
				}
			default:
				break;
		}
	}
}

void ButtonList::tick()
{
	
}

void ButtonList::free()
{
	
}
