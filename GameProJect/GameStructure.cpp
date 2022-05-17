#include "GameStructure.h"
#include <iostream>
#include <SDL_ttf.h>
#include "Util.cpp"

void GameBase::init() {

	//test
	/*int w, h;
	SDL_GetWindowSize(window, &w, &h);
	std::cout << mb->getWidth() << " " << mb->getHeight() << std::endl << w << " " << h << std::endl;*/


	//Initialize Environment
	SDL_Log("Initializing Game");

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return;
	}

	if (TTF_Init() == -1)
	{
		SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return;
	}

	if ((window = SDL_CreateWindow((TITLE + " - " + VERSION).c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_OPENGL)) == NULL) {
		SDL_Log("Unable to create Window: %s", SDL_GetError());
		return;
	}

	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
		SDL_Log("Unable to create Renderer: %s", SDL_GetError());
		return;
	}

	//Load Texture
	SDL_Log("Loading Texture:");
	menu->load(renderer);
	mb->load(renderer);
	pb->load(renderer);
	test->load(renderer);
	test2->load(renderer);
	test3->load(renderer);
	test4->load(renderer);
	test5->load(renderer);
	test6->load(renderer);
	test7->load(renderer);
	test8->load(renderer);
	gb->load(renderer);
	spellbutton->load(renderer);
	guessbutton->load(renderer);
	sellectbutton->load(renderer);
	load(tutor1, renderer, "TAB to change Button", "font.ttf", 12);
	load(tutor2, renderer, "SPACE to select", "font.ttf", 12);
	load(tutor3, renderer, "ESCAPE to back to Menu", "font.ttf", 12);
	load(ctn_y_n, renderer, "Continue?","font.ttf", 36);
	load(end_game, renderer, "END GAME", "font.ttf", 36);
	y->load(renderer);
	n->load(renderer);
	

	//Setup Object
	SDL_Log("Setup Object");

	gmo.addVar("getinputperiod", 0);

	yes.setSize(1, 1);
	no.setSize(1, 1);
	yes.setTexture(y);
	no.setTexture(n);
	yes.setPos(150, 400);
	no.setPos(350, 400);
	ctno.setSize(1, 1);
	ctno.setTexture(&ctn_y_n);
	ctno.setPos(0, 0);
	ctno.setColorMod(255, 0, 255);
	endgame.setSize(1, 1);
	endgame.setTexture(&end_game);
	endgame.setPos(300 - (end_game.h/2), 300);


	bg_ctno.setRender([=](SDL_Renderer* Renderer) {
			SDL_Rect bg_black = { 0, 0, 600, 600 };
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderDrawRect(renderer, &bg_black);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		});

	yes_no_buttonlist.addButton(&yes, [=]() {
		changeScene(GAME);
	}, 0);
	yes_no_buttonlist.addButton(&no, [=]() {
		changeScene(MENU);
	}, 1);

	cso.setEvent([=](SDL_Event* Event) {
		if (Event->type == SDL_KEYDOWN) {
			if (Event->key.keysym.sym == SDLK_SPACE) {
				changeScene(MENU);
			}
		}
	});

	gmo.setTick([=]() {

		if (manager.health <= 0) {
			changeScene(ENDGAME);
		}
		else if (manager.getDisplay_Word() == manager.getWord()) {
			manager.setRandom();
			changeScene(CONTINUE);
		}

	});

	gmo.setRender([=](SDL_Renderer* renderer) {
		if (ao2.getVar("input") != 0) {
			load(selectedchar, renderer, std::string(1, (char)ao2.getVar("input")), "font.ttf", 120);
			SDL_Rect pos; pos.x = 480 + 5; pos.y = 210 - 15; pos.w = selectedchar.w; pos.h = selectedchar.h;
			SDL_RenderCopy(renderer, selectedchar.texture, NULL, &pos);
			deload(selectedchar);
		}
		load(placeholder, renderer, manager.getDisplay_Word() + "  :  " + manager.getWord_Meaning(), "font.ttf", 24);
		SDL_Rect pos; pos.x = 40; pos.y = 300; pos.w = placeholder.w; pos.h = placeholder.h;
		SDL_RenderCopy(renderer, placeholder.texture, NULL, &pos);
		deload(placeholder);

		load(placeholder, renderer, manager.getGuessedWord(), "font.ttf", 24);
		pos; pos.x = 40; pos.y = 240; pos.w = placeholder.w; pos.h = placeholder.h;
		SDL_RenderCopy(renderer, placeholder.texture, NULL, &pos);
		deload(placeholder);

	});

	spello.setTexture(spellbutton);
	spello.setPos(60, 420);
	spello.setSize(1, 1);

	guesso.setTexture(guessbutton);
	guesso.setPos(60 + 120 + 60, 420);
	guesso.setSize(1, 1);

	sellecto.setTexture(sellectbutton);
	sellecto.setPos(60 + 120 + 60 + 120 + 60, 420);
	sellecto.setSize(1, 1);

	ingamebuttonlist.addButton(&spello, [=]() {

		return;
		}, 0);

	ingamebuttonlist.addButton(&guesso, [=]() {
		if (!manager.guessChar(ao2.getVar("input"))) {
			manager.addHealth(-10);
		}
		else {
			manager.addHealth(10);
		}
		return;
	}, 1);

	ingamebuttonlist.addButton(&sellecto, [=]() {
		(ao2.getVar("checkinput") == 1) ? ao2.setVar("checkinput", 0) : ao2.setVar("checkinput", 1);
		return;
	}, 2);

	tob1.setTexture(&tutor1);
	tob1.setSize(1, 1);
	tob1.setPos(30, 600 - 50);
	tob2.setTexture(&tutor2);
	tob2.setSize(1, 1);
	tob2.setPos(30, 600 - 80);
	tob3.setTexture(&tutor3);
	tob3.setSize(1, 1);
	tob3.setPos(600 - 300, 30);

	mbo.setTexture(mb);
	mbo.setSize(1, 1);
	mbo.setPos(0, 0);

	mo.setTexture(menu);
	mo.setSize(1.5, 1.5);
	mo.setPos(30, 30);

	pbo.setTexture(pb);
	pbo.setSize(1.5, 1.5);
	pbo.setPos(30, 30 + 128 + 30 );

	mbl.addButton(&pbo, [=]() {
		changeScene(GAME);
		manager.reset();
		return;
		}, 0);

	ao.setEvent([=](SDL_Event* Event) {
		if (Event->type == SDL_KEYDOWN && Event->key.keysym.sym == SDLK_ESCAPE) {
			changeScene(MENU);
		}
		return;
		});

	gbo.setTexture(gb);
	gbo.setSize(1, 1);
	gbo.setPos(0, 0);

	mto.addTex(test); mto.addTex(test2); mto.addTex(test3); mto.addTex(test4); mto.addTex(test5); mto.addTex(test6); mto.addTex(test7); mto.addTex(test8);
	mto.setCurTexture();
	mto.setSize(2.5, 2.5);
	mto.setPos(45 / 2.5, 45 / 2.5 - 15);

	baro.setRender([=](SDL_Renderer* renderer) {
		SDL_Rect outline; outline.y = 100; outline.h = 30; outline.w = 280; outline.x = 600 - 30 - 300;
		SDL_Rect fill = outline;
		fill.w = (int) ((((float)manager.health) / 100) * outline.w);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &fill);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &outline);

		load(h_m_display, renderer, std::to_string(manager.health), "font.ttf", 24);
		outline.x += 5;
		outline.w = h_m_display.w;
		outline.h = h_m_display.h;
		SDL_RenderCopy(renderer, h_m_display.texture, NULL, &outline);
		deload(h_m_display);

		outline.y = 100 + 50; outline.h = 30; outline.w = 280; outline.x = 600 - 30 - 300;
		fill = outline;
		fill.w = (int)((((float)manager.mana) / 100) * outline.w);
		SDL_SetRenderDrawColor(renderer, 30, 144, 255, 255);
		SDL_RenderFillRect(renderer, &fill);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &outline);

		load(h_m_display, renderer, std::to_string(manager.mana), "font.ttf", 24);
		outline.x += 5;
		outline.w = h_m_display.w;
		outline.h = h_m_display.h;
		SDL_RenderCopy(renderer, h_m_display.texture, NULL, &outline);
		deload(h_m_display);
		
	});
	baro.setTick([=]() {
		if (manager.health >= 80) {
			mto.setCurTexture(0);
			gbo.setColorMod(255, 255, 255);
		}
		else if (manager.health >= 70) {
			mto.setCurTexture(1);
			gbo.setColorMod(255, 230, 230);
		}
		else if (manager.health >= 60) {
			mto.setCurTexture(2);
			gbo.setColorMod(255, 200, 200);
		}
		else if (manager.health >= 50) {
			mto.setCurTexture(3);
			gbo.setColorMod(255, 175, 175);
		}
		else if (manager.health >= 40) {
			mto.setCurTexture(4);
			gbo.setColorMod(255, 150, 150);
		}
		else if (manager.health >= 30) {
			mto.setCurTexture(5);
			gbo.setColorMod(255, 125, 125);
		}
		else if (manager.health >= 20) {
			mto.setCurTexture(6);
			gbo.setColorMod(255, 100, 100);
		}
		else if (manager.health >= 10) {
			mto.setCurTexture(7);
			gbo.setColorMod(255, 50, 50);
		}
		else {
			mto.setCurTexture(7);
			gbo.setColorMod(255, 0, 0);
		}
	});
	
	//Setup Scene
	SDL_Log("Setup Scene");
	s1.push_back((GameObject*)&mbo);
	s1.push_back((GameObject*)&mo);
	s1.push_back((GameObject*)&mbl);
	s1.push_back((GameObject*)&tob1);
	s1.push_back((GameObject*)&tob2);

	s2.push_back((GameObject*)&gbo);
	s2.push_back((GameObject*)&mto);
	s2.push_back((GameObject*)&ao);
	s2.push_back((GameObject*)&ao2);
	s2.push_back((GameObject*)&tob3);
	s2.push_back((GameObject*)&baro);
	s2.push_back((GameObject*)&gmo);
	s2.push_back((GameObject*)&ingamebuttonlist);

	s3.push_back((GameObject*)&endgame);
	s3.push_back((GameObject*)&cso);

	s4.push_back((GameObject*)&bg_ctno);
	s4.push_back((GameObject*)&yes_no_buttonlist);
	s4.push_back((GameObject*)&ctno);
	

	addScene("scene1", s1);
	addScene("scene2", s2);
	addScene("scene4", s4);

	changeScene("scene1");

	SDL_Log("Complete");
}


void GameBase::render(){
	SDL_RenderClear(renderer);

	for (GameObject* a : (scene[presentedscene])) {
		a->render(renderer);
	}

	SDL_RenderPresent(renderer);
}


void GameBase::eventCheck(SDL_Event* Event) {
	if (Event->type == SDL_QUIT) {
		running = false;
		return;
	}

	for (GameObject* a : (scene[presentedscene])) {
		a->eventCheck(Event);
	}
}


void GameBase::tick() {
	for (GameObject* a : (scene[presentedscene])) {
		a->tick();
	}
}


void GameBase::quit() {
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	delete menu;
	delete mb;
	delete pb;
	delete test;
	delete gb;
	delete test2;
	delete test3;
	delete test4;
	delete test5;
	delete test6;
	delete test7;
	delete test8;
	delete spellbutton;
	delete guessbutton;
	delete sellectbutton;
	delete y;
	delete n;
	std::cout << std::endl;
	//delete tutor1;
	//delete tutor2;
	gb = NULL;
	menu = NULL;
	mb = NULL;
	pb = NULL;
	test = NULL;
	test2 = NULL;
	test3 = NULL;
	test4 = NULL;
	test5 = NULL;
	test6 = NULL;
	test7 = NULL;
	test8 = NULL;
	spellbutton = NULL;
	guessbutton = NULL;
	sellectbutton = NULL;
	y = NULL;
	n = NULL;

	SDL_Quit();
	IMG_Quit();
}


void GameBase::run() {

	init();

	oldtime = 0;

	while (running) {

		newtime = SDL_GetTicks64();
		delta = newtime - oldtime;

		while (SDL_PollEvent(&Event)) {
			eventCheck(&Event);
		}

		tick();

		render();

		SDL_Delay(1);

		oldtime = newtime;

	}

	quit();
	
}

void GameBase::addScene(std::string name, std::vector<GameObject*> objects) {
	scene.insert(std::pair<std::string, std::vector<GameObject*>>(name, objects));
}

void GameBase::changeScene(std::string name) {
	presentedscene = name;
}