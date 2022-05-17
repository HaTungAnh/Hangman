#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

struct PlayerData {
	int score;
	float time;

	PlayerData(int score_ = 0, float time_ = 0) {
		score = score_;
		time = time_;
	}

	std::string toString() {
		std::string s;
		s = std::to_string(score) + ": " + std::to_string(time);
		return s;
	}
};

class GameManager
{
public:
	float time_start, time_end;


	int health;
	int mana;

protected:

	PlayerData data = PlayerData();

	std::string word;
	std::string displace_word;
	std::string word_meaning;

	std::vector<std::string> wordlist;
	std::vector<std::string> wordmeaninglist;

	std::vector<std::string> scorelist;
	
	std::vector<char> guessedchar;

public:
	void addHealth(int add) {
		if (health == 100 && add > 0) return;
		health = health + add;
		if (health < 0) {
			health = 0;
			return;
		}
	}

	GameManager() {
		health = 100;
		mana = 100;

		loadWord();
		setRandom();
	}

	void reset() {
		health = 100;
		mana = 100;

		setRandom();
	}

	void loadWord() {
		std::ifstream wordinput; 
		std::string temp;

		wordinput.open("Word.txt", std::ifstream::in);
		
		while (wordinput >> temp) {
			wordlist.push_back(temp);
		}

		wordinput.close();

		int length = wordlist.size();

		wordinput.open("WordMeaning.txt", std::ifstream::in);

		int i = 0;

		while (i < length) {
			std::getline(wordinput, temp);
			wordmeaninglist.push_back(temp);
			i++;
		}

		wordinput.close();

	}

	void setRandom() {
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

};

