#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <SDL.h>
#include <set>
#include "Util.h"
#include "SDL_thread.h"

using namespace Util;

struct PlayerData {
	int score;
	float time;

	PlayerData(int score_ = 0, float time_ = 0) {
		score = score_;
		time = time_;
	}

	PlayerData(std::string str) {
		std::stringstream s; s << str;
		std::string temp;
		s >> temp; this->score = std::stoi(temp);
		s >> temp;
		s >> temp; this->time = std::stof(temp);
	}

	std::string toString() {
		std::string s;
		s = std::to_string(score) + " : " + std::to_string(time);
		return s;
	}

	bool operator>(PlayerData d) {
		if (this->score > d.score) {
			return true;
		}
		else if(this->score == d.score) {
			return this->time < d.time;
		}
		return false;
	}

	bool operator<(PlayerData d) {
		if (this->score < d.score) {
			return true;
		}
		else if (this->score == d.score) {
			return this->time > d.time;
		}
		return false;
	}
};

class GameManager
{
private:
	SDL_Thread* thread = NULL;

public:
	SDL_Renderer* renderer;

	Text message;

	std::vector<PlayerData> scorelist;

	int score;

	float guessingtime;
	float time_start, time_end;

	int health;
	int mana;

protected:
	

	int highscore;

	std::string word;
	std::string displace_word;
	std::string word_meaning;

	std::vector<std::string> wordlist;
	std::vector<std::string> wordmeaninglist;
	
	std::vector<char> guessedchar;

public:
	int type;
	const int POKEMON = 0, NORMAL = 1;

	int tool1_ = 0, tool2_ = 0, tool3_ = 0, tool4_ = 0;

	void tool1() {
		if (tool1_ >= 1) {
			if (useMana(-30)) {
				srand(time(NULL));
				int i;
				while (true) {
					i = rand() % word.length();
					if (word[i] != displace_word[i]) break;
				}
				guessChar(word[i]);
				tool1_--;
				score += 10;
				callMessage("You have used one Eye of Future!");
			}
			else {
				callMessage("You don't have enough Mana!");
			}
		}
		else {
			callMessage("You don't have Item!");
		}
		
	}

	void tool2() {
		if (tool2_ >= 1) {
			if (useMana(-80)) {
				displace_word = word;
				tool2_--;
				score += 10 * (word.length() / 2);
				callMessage("You have used one Holy Grail!");
			}
			else {
				callMessage("You don't have enough Mana!");
			}
			
		}
		else {
			callMessage("You don't have Item!");
		}
	}

	void tool3() {
		if (tool3_ >= 1) {
			useMana(20);
			tool3_--;
			callMessage("You have used one Mana Potion!");
		}
		else {
			callMessage("You don't have Item!");
		}
	}

	void tool4() {
		if (tool4_ >= 1) {
			if (useMana(-10)) {
				addHealth(20);
				tool4_--;
				callMessage("You have used one Health Potion!");
			}
			else {
				callMessage("You don't have enough Mana!");
			}
		}
		else {
			callMessage("You don't have Item!");
		}
	}

	void timer(float time) {
		guessingtime -= time;
		if (guessingtime < 0) guessingtime = 0;
	}

	void addHealth(int add) {
		if (health == 100 && add > 0) return;
		health = health + add;
		if (health > 100) {
			health = 100;
		}
		if (health < 0) {
			health = 0;
			return;
		}
	}

	bool useMana(int add) {
		if (mana == 100 && add > 0) return true;
		mana = mana + add;
		if (mana > 100) {
			mana = 100;
			return true;
		}
		if (mana < 0) {
			mana -= add;
			return false;
		}
	}

	GameManager() {
		tool1_ = 2;
		tool2_ = 1;
		tool3_ = 2;
		tool4_ = 2;

		score = 0;

		guessingtime = 30;
		health = 100;
		mana = 100;

	}

	void reset() {
		tool1_ = 2;
		tool2_ = 1;
		tool3_ = 2;
		tool4_ = 2;

		score = 0;
		time_start = SDL_GetTicks64();
		
		guessingtime = 30;
		health = 100;
		mana = 100;

		setRandom();
	}

	void loadWord() {
		std::ifstream wordinput; 
		std::string temp;

		if (type > 0) {
			wordinput.open("Word.txt", std::ifstream::in);
		}
		else {
			wordinput.open("Pokemon.txt", std::ifstream::in);
		}
		
		while (wordinput >> temp) {
			wordlist.push_back(temp);
		}

		wordinput.close();

		int length = wordlist.size();

		if (type > 0) {
			wordinput.open("WordMeaning.txt", std::ifstream::in);
		}
		else {
			wordinput.open("PokemonMeaning.txt", std::ifstream::in);
		}
		

		int i = 0;

		while (i < length) {
			std::getline(wordinput, temp);
			wordmeaninglist.push_back(temp);
			i++;
		}

		wordinput.close();

	}

	void setRandom() {
		guessingtime = 30;
		guessedchar = std::vector<char>();
		srand(time(0));

		int i = rand() % wordlist.size();
		word = wordlist[i];
		word_meaning = wordmeaninglist[i];
		displace_word = std::string(word.length(), '-');
	}

	std::string getWord() {
		return word;
	}

	std::string getDisplay_Word() {
		return displace_word;
	}

	std::string getWord_Meaning() {
		return word_meaning;
	}

	bool guessChar(char c) {
		if (std::find(guessedchar.begin(), guessedchar.end(), c) != guessedchar.end()) {
			guessedchar.push_back(c);
			return false;
		}
		bool a = false;
		for (int i = 0; i < word.length(); i++) {
			if (word[i] == c) {
				displace_word[i] = c;
				a = true;
			}
		}
		guessedchar.push_back(c);
		return a;
	}

	void loadScore() {
		SDL_Log("Load Score");
		scorelist = std::vector<PlayerData>();
		std::ifstream file("score.txt");
		int n; file >> n;
		std::string temp;
		std::getline(file, temp);
		for (int i = 0; i < n; i++) {
			std::string temp;
			std::getline(file, temp);
			PlayerData p = PlayerData(temp);
			scorelist.push_back(p);
		}
		std::sort(scorelist.begin(), scorelist.end());
		
		file.close();
		if (scorelist.empty()) {
			return;
		}
		highscore = scorelist.back().score;
	}

	std::string getGuessedWord() {
		if (guessedchar.empty()) return  "GUESSED:";
		std::string temp = "";
		/*for (auto i = guessedchar.end(); i != guessedchar.end() - 6; i--) {
			temp = temp + std::string(1, *i) + " ";
		}*/
		/*auto iter = guessedchar.end() - 1;
		int i = 0;
		int length = (guessedchar.size() < 6) ? guessedchar.size() : 6;
		while (i < length) {
			temp = temp + *iter + " ";
			i++;
			iter--;
		}*/
		if (guessedchar.size() <= 3) {
			for (char i : guessedchar) {
				temp = temp + std::string(1, i) + " ";
			}
		}
		else {
			auto iter = guessedchar.end() - 1;
			int i = 0;
			
			while (i < 3) {
				temp = temp + *iter + " ";
				i++;
				iter--;
			}
		}
		
		temp = "GUESSED: " + temp;
		return temp;
	}

	void callMessage(std::string mess) {
		load(message, renderer, mess, "font.ttf", 12);
		message.test = 100;
		thread = SDL_CreateThread(tool_theard, "tool_thread", (void*)&message);
	}

	void saveScore(bool saveFile) {
		SDL_Log("Saving Score");
		if (saveFile) {
			std::ofstream file("score.txt");
			file << scorelist.size() << "\n";
			for (PlayerData d : scorelist) {
				file << d.toString() << "\n";
			}
			file.close();
		}
		else {
			time_end = SDL_GetTicks64();
			PlayerData data = PlayerData(score, ((int)(time_end - time_start) / 10) / 100);
			scorelist.push_back(data);
			std::sort(scorelist.begin(), scorelist.end());
		}
	}

	int getItem() {
		srand(time(NULL));
		int i = rand() % 4 + 1;
		switch (i)
		{
		case 1:
			tool1_++;
			tool1_ = tool1_ % 10 + 1;
			load(message, renderer, "You Get 1 Eye of Future!", "font.ttf", 12);
			message.test = 100;
			thread = SDL_CreateThread(tool_theard, "tool_thread", (void*) &message);
			break;
		case 2:
			tool2_++;
			tool2_ = tool2_ % 10 + 1;
			load(message, renderer, "You get 1 Holy Grail!", "font.ttf", 12);
			message.test = 100;
			thread = SDL_CreateThread(tool_theard, "tool_thread", (void*)&message);
			break;
		case 3:
			tool3_++;
			tool3_ = tool3_ % 10 + 1;
			load(message, renderer, "You get 1 Mana Potion!", "font.ttf", 12);
			message.test = 100;
			thread = SDL_CreateThread(tool_theard, "tool_thread", (void*)&message);
			break;
		case 4:
			tool4_++;
			tool4_ = tool4_ % 10 + 1;
			load(message, renderer, "You get 1 Health Potion!", "font.ttf", 12);
			message.test = 100;
			thread = SDL_CreateThread(tool_theard, "tool_thread", (void*)&message);
			break;
		default:
			break;
		}
		if (thread == NULL) {
			std::cout << i << " " << "adudu" << "\n";
		}
		return i;
	}

};

