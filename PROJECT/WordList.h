#pragma once
#include <wx/wx.h>
#include "DifficultyConfig.h"
#include <vector>
#include <fstream>
#include <string>
using namespace std;

enum class wordtier{easy, medium, hard, insane};

struct wordentry {
	wxString word;
	wordtier tier;
};

class WordList
{
private:
	vector<wordentry> mywords;

	void Add(wxString w, wordtier t) {
		mywords.push_back({ w, t });
	}

	wordentry get_random_word(wordtier neededtier) {
		//load an entire tier, then single out a word form said tier to return. ez
		vector<const wordentry*> wordpool;

		for (int i = 0; i < mywords.size(); i++)
		{
			if (mywords[i].tier == neededtier)
			{
				wordpool.push_back(&mywords[i]);
			}
		}

		if (wordpool.empty()) {
			return { mywordlist_fallback(), wordtier::easy };
		}

		return *wordpool[rand() % wordpool.size()];
	}

	wordtier roll_tier(Difficulty d) {
		int roll = rand() % 100;
		switch (d) {
		case Difficulty::easy:
			if (roll < 70) return wordtier::easy;
			if (roll < 95) return wordtier::medium;
			return wordtier::hard;

		case Difficulty::medium:
			if (roll < 35) return wordtier::easy;
			if (roll < 80) return wordtier::medium;
			if (roll < 97) return wordtier::hard;
			return wordtier::insane;

		case Difficulty::hard:
			if (roll < 15) return wordtier::easy;
			if (roll < 50) return wordtier::medium;
			if (roll < 85) return wordtier::hard;
			return wordtier::insane;

		case Difficulty::insane:
			if (roll < 5) return wordtier::easy;
			if (roll < 25) return wordtier::medium;
			if (roll < 65) return wordtier::hard;
			return wordtier::insane;
		default:
			return wordtier::easy;
		}
	}

	wxString mywordlist_fallback() {
		return "fail";
	}

public:
	WordList() {

		ifstream file("wordlist.txt", ios::in);
		string word;
		while (getline(file, word))
		{
			if (word.size() <= 4)
			{
				Add(word, wordtier::easy);
			}
			else if (word.size() > 4 && word.size() <= 7)
			{
				Add(word, wordtier::medium);
			}
			else if (word.size() > 7 && word.size() <= 11)
			{
				Add(word, wordtier::hard);
			}
			else
			{
				Add(word, wordtier::insane);
			}
		}
		file.close();
	}

	wordentry getoneword(Difficulty gamediff) {
		wordtier tier = roll_tier(gamediff);
		return get_random_word(tier);
	}
	
	static float speed_multiplier(wordtier tier) {
		switch (tier) {
		case wordtier::easy:
			return 1.00f;
		case wordtier::medium:
			return 0.75f;
		case wordtier::hard:
			return 0.55f;
		case wordtier::insane:
			return 0.30f;
		default:
			return 1.00f;
		}
	}
};

