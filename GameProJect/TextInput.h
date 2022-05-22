#pragma once
#include "AbOb.h"
#include <iostream>

class TextInput : public AbOb {

public:
	TextInput() {
		addVar("checkinput", 0);
		addVar("input", 0);
		actionevent = [=](SDL_Event* Event) {
			if (this->getVar("checkinput") == 1) {
				//std::cout << getVar("checkinput") << std::endl;
				if (Event->type == SDL_KEYDOWN) {
					switch (Event->key.keysym.sym)
					{
					case SDLK_a:
						setVar("input", 'a');
						break;
					case SDLK_b:
						setVar("input", 'b');
						break;
					case SDLK_c:
						setVar("input", 'c');
						break;
					case SDLK_d:
						setVar("input", 'd');
						break;
					case SDLK_e:
						setVar("input", 'e');
						break;
					case SDLK_f:
						setVar("input", 'f');
						break;
					case SDLK_g:
						setVar("input", 'g');
						break;
					case SDLK_h:
						setVar("input", 'h');
						break;
					case SDLK_i:
						setVar("input", 'i');
						break;
					case SDLK_j:
						setVar("input", 'j');
						break;
					case SDLK_k:
						setVar("input", 'k');
						break;
					case SDLK_l:
						setVar("input", 'l');
						break;
					case SDLK_m:
						setVar("input", 'm');
						break;
					case SDLK_n:
						setVar("input", 'n');
						break;
					case SDLK_o:
						setVar("input", 'o');
						break;
					case SDLK_p:
						setVar("input", 'p');
						break;
					case SDLK_q:
						setVar("input", 'q');
						break;
					case SDLK_r:
						setVar("input", 'r');
						break;
					case SDLK_s:
						setVar("input", 's');
						break;
					case SDLK_t:
						setVar("input", 't');
						break;
					case SDLK_u:
						setVar("input", 'u');
						break;
					case SDLK_v:
						setVar("input", 'v');
						break;
					case SDLK_w:
						setVar("input", 'w');
						break;
					case SDLK_x:
						setVar("input", 'x');
						break;
					case SDLK_y:
						setVar("input", 'y');
						break;
					case SDLK_z:
						setVar("input", 'z');
						break;
					default:
						break;
					}

				}
			}
		};
		actiontick = [=]() {
			return;
		};
	}

};