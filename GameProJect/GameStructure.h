#pragma once
#include <vector>
#include "GameObject.h"
#include <string>
#include <map>
#include "TexOb.h"
#include "ButtonList.h"
#include "AbOb.h"
#include "MultiTexOb.h"
#include "TextInput.h"
#include "Util.h"
#include "GameManager.h"
#include <SDL_mixer.h>

class GameBase
{
public:

	float oldtime, newtime, delta;

	const std::string MENU = "scene1";
	const std::string GAME = "scene2";
	const std::string ENDGAME = "scene3";
	const std::string CONTINUE = "scene4";
	const std::string SPELL = "scene5";
	const std::string CHOSECATEGORY = "scene6";

	std::vector<GameObject*> s1, s2, s3, s4, s5, s6;

	TexOb mo = TexOb(), mbo = TexOb(), pbo = TexOb(), gbo = TexOb(), tob1 = TexOb(), tob2 = TexOb(), spello = TexOb(), guesso = TexOb(), sellecto = TexOb(), yes_button = TexOb(), no_button = TexOb(), ctn_text_ob = TexOb(), end_ob = TexOb();
	TexOb t1b = TexOb(), t2b = TexOb(), t3b = TexOb(), t4b = TexOb(), volume_button = TexOb(), p_type = TexOb(), n_type = TexOb();
	
	MultiTexOb mto = MultiTexOb();
	
	ButtonList mbl = ButtonList(), ingamebuttonlist = ButtonList(), ctn_buttonlist = ButtonList(), spell_buttonlist = ButtonList(), category_buttonlist = ButtonList();
	
	AbOb ao = AbOb(), baro = AbOb(), gmo = AbOb(), bg = AbOb(), endgame_o = AbOb(), spell_o = AbOb(), message_o = AbOb(), ctn_abob = AbOb(), category_abob = AbOb();
	
	TextInput ao2 = TextInput();

	Texture* t = new Texture("Player.bmp");
	Texture* menu = new Texture("GameMenu.png"); //256 x 128
	Texture* mb = new Texture("GameMenuBackGroud.png"); //600 x 600
	Texture* pb = new Texture("PlayButton.png"); //100 x 50
	Texture* test = new Texture("PlayerHead1.png");
	Texture* gb = new Texture("GameBackground.png");
	Texture* test2 = new Texture("PlayerHead2.png");
	Texture* test3 = new Texture("PlayerHead3.png");
	Texture* test4 = new Texture("PlayerHead4.png");
	Texture* test5 = new Texture("PlayerHead5.png");
	Texture* test6 = new Texture("PlayerHead6.png");
	Texture* test7 = new Texture("PlayerHead7.png");
	Texture* test8 = new Texture("PlayerHead8.png");
	Texture* spellbutton = new Texture("spell.png");
	Texture* guessbutton = new Texture("guess.png");
	Texture* sellectbutton = new Texture("sellectchar.png");
	Texture* yes_texture = new Texture("Yes.png");
	Texture* no_texture = new Texture("No.png");
	Texture* health_tool = new Texture("tool4.png");
	Texture* mana_tool = new Texture("tool3.png");
	Texture* near_tool = new Texture("tool2.png");
	Texture* future_tool = new Texture("tool1.png");
	Texture* volume = new Texture("Volume.png");
	Texture* pokemontype = new Texture("PokemonType.png");
	Texture* normaltype = new Texture("NormalType.png");

	Text tutor1, tutor2, h_m_display, ctn_y_n_text;

	Text placeholder, selectedchar;

	Text endgame, score_text;

	Mix_Music* music = NULL;

	Mix_Chunk* endgame_effect = NULL;
	Mix_Chunk* hit_effect = NULL;
	Mix_Chunk* health_effect = NULL;
	Mix_Chunk* click_effect = NULL;

	GameManager manager = GameManager();
	
private:
	bool running = true;

	std::map<std::string, std::vector<GameObject*>> scene;
	std::string presentedscene;

	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event Event;

	const std::string VERSION = "0.3.0";
	const std::string TITLE = "Hang Man";

public:
	void addScene(std::string name, std::vector<GameObject*> objects);

	void changeScene(std::string name);

	GameBase(){}

	void init();

	void render();

	void eventCheck(SDL_Event* Event);

	void tick();

	void quit();

	void run();

	~GameBase() {
		quit();
	}
};


