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
						setVar("checkinput", 0);
						break;
					case SDLK_b:
						setVar("input", 'b');
						setVar("checkinput", 0);
						break;
					case SDLK_c:
						setVar("input", 'c');
						setVar("checkinput", 0);
						break;
					case SDLK_d:
						setVar("input", 'd');
						setVar("checkinput", 0);
						break;
					case SDLK_e:
						setVar("input", 'e');
						setVar("checkinput", 0);
						break;
					case SDLK_f:
						setVar("input", 'f');
						setVar("checkinput", 0);
						break;
					case SDLK_g:
						setVar("input", 'g');
						setVar("checkinput", 0);
						break;
					case SDLK_h:
						setVar("input", 'h');
						setVar("checkinput", 0);
						break;
					case SDLK_i:
						setVar("input", 'i');
						setVar("checkinput", 0);
						break;
					case SDLK_j:
						setVar("input", 'j');
						setVar("checkinput", 0);
						break;
					case SDLK_k:
						setVar("input", 'k');
						setVar("checkinput", 0);
						break;
					case SDLK_l:
						setVar("input", 'l');
						setVar("checkinput", 0);
						break;
					case SDLK_m:
						setVar("input", 'm');
						setVar("checkinput", 0);
						break;
					case SDLK_n:
						setVar("input", 'n');
						setVar("checkinput", 0);
						break;
					case SDLK_o:
						setVar("input", 'o');
						setVar("checkinput", 0);
						break;
					case SDLK_p:
						setVar("input", 'p');
						setVar("checkinput", 0);
						break;
					case SDLK_q:
						setVar("input", 'q');
						setVar("checkinput", 0);
						break;
					case SDLK_r:
						setVar("input", 'r');
						setVar("checkinput", 0);
						break;
					case SDLK_s:
						setVar("input", 's');
						setVar("checkinput", 0);
						break;
					case SDLK_t:
						setVar("input", 't');
						setVar("checkinput", 0);
						break;
					case SDLK_u:
						setVar("input", 'u');
						setVar("checkinput", 0);
						break;
					case SDLK_v:
						setVar("input", 'v');
						setVar("checkinput", 0);
						break;
					case SDLK_w:
						setVar("input", 'w');
						setVar("checkinput", 0);
						break;
					case SDLK_x:
						setVar("input", 'x');
						setVar("checkinput", 0);
						break;
					case SDLK_y:
						setVar("input", 'y');
						setVar("checkinput", 0);
						break;
					case SDLK_z:
						setVar("input", 'z');
						setVar("checkinput", 0);
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