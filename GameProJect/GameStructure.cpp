#include "GameStructure.h"
#include <iostream>
#include <SDL_ttf.h>
#include "Util.h"

using namespace Util;

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

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
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

	manager.renderer = renderer;

	//Load Score
	SDL_Log("Load Score");
	manager.loadScore();

	//Load Music
	SDL_Log("Load Music");
	music = Mix_LoadMUS("137-sylph company.mp3");
	if (music == NULL) {
		std::cout << "a";
	}
	Mix_VolumeMusic(60);

	endgame_effect = Mix_LoadWAV("111-pokemon recovery.ogg");

	hit_effect = Mix_LoadWAV("270332__littlerobotsoundfactory__hit-03.wav");
	
	health_effect = Mix_LoadWAV("270323__littlerobotsoundfactory__jump-03.wav");

	click_effect = Mix_LoadWAV("270338__littlerobotsoundfactory__open-01.wav");

	//Load Texture
	SDL_Log("Loading Texture:");
	t->load(renderer);
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
	yes_texture->load(renderer);
	no_texture->load(renderer);
	health_tool->load(renderer);
	mana_tool->load(renderer);
	near_tool->load(renderer);
	future_tool->load(renderer);
	volume->load(renderer);
	pokemontype->load(renderer);
	normaltype->load(renderer);

	load(tutor1, renderer, "TAB to change Button", "font.ttf", 12);
	load(tutor2, renderer, "SPACE to select", "font.ttf", 12);
	load(ctn_y_n_text, renderer, "Continue ?", "font.ttf", 36);
	load(endgame, renderer, "END!", "font.ttf", 48);

	//Setup Object
	SDL_Log("Setup Object");

	category_abob.addVar("Volume", 1);

	p_type.setTexture(pokemontype);
	p_type.setPos(300 - pokemontype->getWidth() / 2, 200);

	n_type.setTexture(normaltype);
	n_type.setPos(300 - normaltype->getWidth() / 2, 400);

	category_buttonlist.addButton(&n_type, [=]() {
		manager.type = manager.NORMAL;
		manager.loadWord();
		manager.reset();
		Mix_PlayMusic(music, -1);
		changeScene(GAME);
		}, 0);

	category_buttonlist.addButton(&p_type, [=]() {
		manager.type = manager.POKEMON;
		manager.loadWord();
		manager.reset();
		Mix_PlayMusic(music, -1);
		changeScene(GAME);
		}, 1);

	message_o.setRender([=](SDL_Renderer* renderer) {
		if (manager.message.texture != NULL) {
			SDL_Rect pos; pos.x = 300; pos.y = 20; pos.w = manager.message.w; pos.h = manager.message.h;
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, manager.message.a);
			SDL_RenderCopy(renderer, manager.message.texture, NULL, &pos);
		}
		});

	t1b.setPos(50, 200);
	t2b.setPos(50, 300);
	t3b.setPos(50, 400);
	t4b.setPos(50, 500);
	t1b.setTexture(future_tool);
	t2b.setTexture(near_tool);
	t3b.setTexture(mana_tool);
	t4b.setTexture(health_tool);

	spell_buttonlist.addButton(&t1b, [=]() {
		Mix_PlayChannel(-1, click_effect, 0);
		manager.tool1();
		changeScene(GAME);
		}, 0);

	spell_buttonlist.addButton(&t2b, [=]() {
		Mix_PlayChannel(-1, click_effect, 0);
		manager.tool2();
		changeScene(GAME);
		}, 1);

	spell_buttonlist.addButton(&t3b, [=]() {
		Mix_PlayChannel(-1, click_effect, 0);
		manager.tool3();
		changeScene(GAME);
		}, 2);

	spell_buttonlist.addButton(&t4b, [=]() {
		Mix_PlayChannel(-1, click_effect, 0);
		manager.tool4();
		changeScene(GAME);
		}, 3);

	spell_o.setEvent([=](SDL_Event* Event) {
		if (Event->type == SDL_KEYDOWN){ 
			if (Event->key.keysym.sym == SDLK_ESCAPE) {
				Mix_PlayChannel(-1, click_effect, 0);
				changeScene(GAME);
			}
		}
		});

	spell_o.setRender([=](SDL_Renderer* renderer) {
		load(placeholder, renderer, "Random guess one word : -30 Mana", "font.ttf", 18);
		SDL_Rect pos; pos.x = 120; pos.y = 220; pos.w = placeholder.w; pos.h = placeholder.h;
		SDL_RenderCopy(renderer, placeholder.texture, NULL, &pos);
		deload(placeholder);

		load(placeholder, renderer, std::to_string(manager.tool1_), "font.ttf", 18);
		pos; pos.x = 20; pos.y = 220; pos.w = placeholder.w; pos.h = placeholder.h;
		SDL_RenderCopy(renderer, placeholder.texture, NULL, &pos);
		deload(placeholder);

		load(placeholder, renderer, "Guessing word entirely : -80 Mana", "font.ttf", 18);
		pos; pos.x = 120; pos.y = 320; pos.w = placeholder.w; pos.h = placeholder.h;
		SDL_RenderCopy(renderer, placeholder.texture, NULL, &pos);
		deload(placeholder);

		load(placeholder, renderer, std::to_string(manager.tool2_), "font.ttf", 18);
		pos; pos.x = 20; pos.y = 320; pos.w = placeholder.w; pos.h = placeholder.h;
		SDL_RenderCopy(renderer, placeholder.texture, NULL, &pos);
		deload(placeholder);

		load(placeholder, renderer, "Regenerate 20 Mana : -0 Mana", "font.ttf", 18);
		pos; pos.x = 120; pos.y = 420; pos.w = placeholder.w; pos.h = placeholder.h;
		SDL_RenderCopy(renderer, placeholder.texture, NULL, &pos);
		deload(placeholder);

		load(placeholder, renderer, std::to_string(manager.tool3_), "font.ttf", 18);
		pos; pos.x = 20; pos.y = 420; pos.w = placeholder.w; pos.h = placeholder.h;
		SDL_RenderCopy(renderer, placeholder.texture, NULL, &pos);
		deload(placeholder);

		load(placeholder, renderer, "Regenerate 20 Health : -10 Mana", "font.ttf", 18);
		pos; pos.x = 120; pos.y = 520; pos.w = placeholder.w; pos.h = placeholder.h;
		SDL_RenderCopy(renderer, placeholder.texture, NULL, &pos);
		deload(placeholder);

		load(placeholder, renderer, std::to_string(manager.tool4_), "font.ttf", 18);
		pos; pos.x = 20; pos.y = 520; pos.w = placeholder.w; pos.h = placeholder.h;
		SDL_RenderCopy(renderer, placeholder.texture, NULL, &pos);
		deload(placeholder);

		load(placeholder, renderer, "<SPELL LIST>", "font.ttf", 48);
		pos; pos.x = 300 - placeholder.w/2; pos.y = 50; pos.w = placeholder.w; pos.h = placeholder.h;
		SDL_RenderCopy(renderer, placeholder.texture, NULL, &pos);
		deload(placeholder);
		});

	bg.setRender([=](SDL_Renderer* renderer) {
		SDL_Rect rect = { 0,0,600,600 };
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	});

	ctn_text_ob.setPos(300 - ctn_y_n_text.w/2, 50);
	ctn_text_ob.setTexture(&ctn_y_n_text);
	ctn_text_ob.setSize(1, 1);
	ctn_text_ob.setColorMod(255, 0, 0);

	yes_button.setPos(30 + 60, 300);
	yes_button.setTexture(yes_texture);
	yes_button.setSize(1, 1);

	no_button.setPos(600 - 120 - 30, 300);
	no_button.setTexture(no_texture);
	no_button.setSize(1, 1);

	ctn_buttonlist.addButton(&yes_button, [=]() {
		manager.setRandom();
		changeScene(GAME);
	}, 0);

	ctn_buttonlist.addButton(&no_button, [=]() {
		Mix_PauseMusic();
		Mix_PlayChannel(-1, endgame_effect, 0);
		changeScene(ENDGAME);
	}, 1);

	gmo.addVar("getinputperiod", 0);

	gmo.setTick([=]() {
		manager.timer(delta);
		if (manager.guessingtime <= 0) {
			manager.addHealth(-20);
			Mix_PlayChannel(-1, hit_effect, 0);
			manager.guessingtime = 30;
		}
		if (manager.health <= 0) {
			manager.saveScore(false);
			Mix_PauseMusic();
			Mix_PlayChannel(-1, endgame_effect, 0);
			changeScene(ENDGAME);
		}
		else if (manager.getDisplay_Word() == manager.getWord()) {
			changeScene(CONTINUE);
			manager.useMana(50);
			manager.getItem();
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

		load(placeholder, renderer,std::to_string((int) manager.guessingtime), "font.ttf", 24);
		pos; pos.x = 340; pos.y = 240; pos.w = placeholder.w; pos.h = placeholder.h;
		SDL_RenderCopy(renderer, placeholder.texture, NULL, &pos);
		deload(placeholder);

		load(placeholder, renderer, "Score:" + std::to_string((int)manager.score), "font.ttf", 24);
		pos; pos.x = 270 ; pos.y = 200; pos.w = placeholder.w; pos.h = placeholder.h;
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
		Mix_PlayChannel(-1, click_effect, 0);
		changeScene(SPELL);
		return;
		}, 0);

	ingamebuttonlist.addButton(&guesso, [=]() {
		manager.guessingtime = 30;
		if (!manager.guessChar(ao2.getVar("input"))) {
			manager.addHealth(-10);
			Mix_PlayChannel(-1, hit_effect, 0);
			manager.score -= 5;
		}
		else {
			manager.addHealth(10);
			Mix_PlayChannel(-1, health_effect, 0);
			manager.score += 10;
		}
		return;
	}, 1);

	ingamebuttonlist.addButton(&sellecto, [=]() {
		Mix_PlayChannel(-1, click_effect, 0);
		(ao2.getVar("checkinput") == 1) ? ao2.setVar("checkinput", 0) : ao2.setVar("checkinput", 1);
		(ingamebuttonlist.isChangeButton) ? ingamebuttonlist.canChangeButton(false) : ingamebuttonlist.canChangeButton(true);
		return;
	}, 2);

	tob1.setTexture(&tutor1);
	tob1.setSize(1, 1);
	tob1.setPos(30, 600 - 25);
	tob2.setTexture(&tutor2);
	tob2.setSize(1, 1);
	tob2.setPos(300, 600 - 25);
	

	mbo.setTexture(mb);
	mbo.setSize(1, 1);
	mbo.setPos(0, 0);

	mo.setTexture(menu);
	mo.setSize(1.5, 1.5);
	mo.setPos(30, 30);

	pbo.setTexture(pb);
	pbo.setSize(1.5, 1.5);
	pbo.setPos(30, 30 + 128 + 30 );

	volume_button.setTexture(volume);
	volume_button.setSize(1.5, 1.5);
	volume_button.setPos(30, 30 + 128 + 30 + 50 + 30);

	mbl.addButton(&pbo, [=]() {
		changeScene(CHOSECATEGORY);
		return;
		}, 0);

	mbl.addButton(&volume_button, [=]() {
		if (category_abob.getVar("Volume") == 1) {
			Mix_VolumeMusic(0);
			category_abob.setVar("Volume", 0);
		}
		else {
			Mix_VolumeMusic(60);
			category_abob.setVar("Volume", 1);
		}
		
		return;
	}, 1);

	gbo.setTexture(gb);
	gbo.setSize(1, 1);
	gbo.setPos(0, 0);

	mto.addTex(test); mto.addTex(test2); mto.addTex(test3); mto.addTex(test4); mto.addTex(test5); mto.addTex(test6); mto.addTex(test7); mto.addTex(test8);
	mto.setCurTexture();
	mto.setSize(2.5, 2.5);
	mto.setPos(45 / 2.5, 10 / 2.5 );

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


	endgame_o.setRender([=](SDL_Renderer* renderer) {

		load(score_text, renderer, "<ENDGAME>", "font.ttf", 64);
		SDL_Rect pos; pos.x = 300 - score_text.w / 2; pos.y = 50; pos.w = score_text.w; pos.h = score_text.h;
		SDL_RenderCopy(renderer, score_text.texture, NULL, &pos);
		deload(score_text);

		auto iter = manager.scorelist.rbegin();
		load(score_text, renderer, (* iter).toString(), "font.ttf", 24);
		pos; pos.x = 300 - score_text.w / 2; pos.y = 250; pos.w = score_text.w; pos.h = score_text.h;
		SDL_RenderCopy(renderer, score_text.texture, NULL, &pos);
		deload(score_text);

		iter++;
		load(score_text, renderer, (*iter).toString(), "font.ttf", 24);
		pos; pos.x = 300 - score_text.w/2; pos.y = 300; pos.w = score_text.w; pos.h = score_text.h;
		SDL_RenderCopy(renderer, score_text.texture, NULL, &pos);
		deload(score_text);

		iter++;
		load(score_text, renderer, (*iter).toString(), "font.ttf", 24);
		pos; pos.x = 300 - score_text.w / 2; pos.y = 350; pos.w = score_text.w; pos.h = score_text.h;
		SDL_RenderCopy(renderer, score_text.texture, NULL, &pos);
		deload(score_text);

		iter++;
		load(score_text, renderer, (*iter).toString(), "font.ttf", 24);
		pos; pos.x = 300 - score_text.w / 2; pos.y = 400; pos.w = score_text.w; pos.h = score_text.h;
		SDL_RenderCopy(renderer, score_text.texture, NULL, &pos);
		deload(score_text);

		iter++;
		load(score_text, renderer, (*iter).toString(), "font.ttf", 24);
		pos; pos.x = 300 - score_text.w / 2; pos.y = 450; pos.w = score_text.w; pos.h = score_text.h;
		SDL_RenderCopy(renderer, score_text.texture, NULL, &pos);
		deload(score_text);

		iter++;
		load(score_text, renderer, (*iter).toString(), "font.ttf", 24);
		pos; pos.x = 300 - score_text.w / 2; pos.y = 500; pos.w = score_text.w; pos.h = score_text.h;
		SDL_RenderCopy(renderer, score_text.texture, NULL, &pos);
		deload(score_text);

		load(score_text, renderer, "Your score is: " + std::to_string(manager.score), "font.ttf", 24);
		pos; pos.x = 300 - score_text.w / 2; pos.y = 150; pos.w = score_text.w; pos.h = score_text.h;
		SDL_RenderCopy(renderer, score_text.texture, NULL, &pos);
		deload(score_text);

		load(score_text, renderer, "You play in: " + std::to_string((float) ((int)(manager.time_end - manager.time_start) / 10) / 100), "font.ttf", 24);
		pos; pos.x = 300 - score_text.w / 2; pos.y = 200; pos.w = score_text.w; pos.h = score_text.h;
		SDL_RenderCopy(renderer, score_text.texture, NULL, &pos);
		deload(score_text);

	});

	endgame_o.setEvent([=](SDL_Event* Event) {
		if (Event->type == SDL_KEYDOWN) {
			if (Event->key.keysym.sym == SDLK_SPACE) {
				changeScene(MENU);
			}
		}
	});

	ctn_abob.setRender([=](SDL_Renderer* renderer) {
		load(placeholder, renderer, "The Word is " + manager.getWord(), "font.ttf", 24);
		SDL_Rect pos; pos.x = 300 - placeholder.w / 2; pos.y = 200; pos.w = placeholder.w; pos.h = placeholder.h;
		SDL_RenderCopy(renderer, placeholder.texture, NULL, &pos);
		deload(placeholder);
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
	s2.push_back((GameObject*)&baro);
	s2.push_back((GameObject*)&gmo);
	s2.push_back((GameObject*)&ingamebuttonlist);
	s2.push_back((GameObject*)&tob1);
	s2.push_back((GameObject*)&tob2);
	s2.push_back((GameObject*)&message_o);

	s3.push_back((GameObject*)&bg);
	s3.push_back((GameObject*)&endgame_o);

	s4.push_back((GameObject*)&bg);
	s4.push_back((GameObject*)&ctn_text_ob);
	s4.push_back((GameObject*)&ctn_buttonlist);
	s4.push_back((GameObject*)&ctn_abob);

	s5.push_back((GameObject*)&bg);
	s5.push_back((GameObject*)&spell_buttonlist);
	s5.push_back((GameObject*)&spell_o);

	s6.push_back((GameObject*)&bg);
	s6.push_back((GameObject*)&category_buttonlist);
	s6.push_back((GameObject*)&category_abob);

	addScene(MENU, s1);
	addScene(GAME, s2);
	addScene(ENDGAME, s3);
	addScene(CONTINUE, s4);
	addScene(SPELL, s5);
	addScene(CHOSECATEGORY, s6);

	changeScene(MENU);

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
	Mix_CloseAudio();

	manager.saveScore(true);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	delete t;
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
	delete yes_texture;
	delete no_texture;
	delete health_tool;
	delete mana_tool;
	delete near_tool;
	delete future_tool;
	delete volume;
	delete pokemontype;
	delete normaltype;

	pokemontype = NULL;
	normaltype = NULL;
	volume = NULL;
	future_tool = NULL;
	near_tool = NULL;
	mana_tool = NULL;
	health_tool = NULL;
	spellbutton = NULL;
	guessbutton = NULL;
	sellectbutton = NULL;
	gb = NULL;
	t = NULL;
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
	yes_texture = NULL;
	no_texture = NULL;

	Mix_FreeMusic(music);
	music = NULL;
	Mix_FreeChunk(endgame_effect);
	endgame_effect = NULL;
	Mix_FreeChunk(hit_effect);
	hit_effect = NULL;
	Mix_FreeChunk(health_effect);
	health_effect = NULL;
	Mix_FreeChunk(click_effect);
	click_effect = NULL;
	
	SDL_Quit();
	IMG_Quit();
	TTF_Quit;
}


void GameBase::run() {

	init();

	oldtime = 0;

	while (running) {

		newtime = SDL_GetTicks64();
		delta = (newtime - oldtime)/1000;

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





