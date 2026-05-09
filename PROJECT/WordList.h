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
		//this gonna be long

		//Easy Words
		//Add("cat", wordtier::easy); Add("dog", wordtier::easy); Add("sun", wordtier::easy); Add("sky", wordtier::easy);
		//Add("pen", wordtier::easy); Add("cup", wordtier::easy); Add("hat", wordtier::easy); Add("map", wordtier::easy);
		//Add("bed", wordtier::easy); Add("box", wordtier::easy); Add("car", wordtier::easy); Add("bus", wordtier::easy);
		//Add("run", wordtier::easy); Add("walk", wordtier::easy); Add("jump", wordtier::easy); Add("sit", wordtier::easy);
		//Add("top", wordtier::easy); Add("red", wordtier::easy); Add("blue", wordtier::easy); Add("green", wordtier::easy);
		//Add("pink", wordtier::easy); Add("gray", wordtier::easy); Add("door", wordtier::easy); Add("wall", wordtier::easy);
		//Add("roof", wordtier::easy); Add("floor", wordtier::easy); Add("tree", wordtier::easy); Add("leaf", wordtier::easy);
		//Add("rock", wordtier::easy); Add("sand", wordtier::easy); Add("fish", wordtier::easy); Add("bird", wordtier::easy);
		//Add("milk", wordtier::easy); Add("food", wordtier::easy); Add("rice", wordtier::easy); Add("cake", wordtier::easy);
		//Add("ship", wordtier::easy); Add("boat", wordtier::easy); Add("wave", wordtier::easy); Add("wind", wordtier::easy);
		//Add("fire", wordtier::easy); Add("heat", wordtier::easy); Add("cold", wordtier::easy); Add("snow", wordtier::easy);
		//Add("rain", wordtier::easy); Add("storm", wordtier::easy); Add("time", wordtier::easy); Add("hour", wordtier::easy);
		//Add("day", wordtier::easy); Add("week", wordtier::easy); Add("game", wordtier::easy); Add("play", wordtier::easy);
		//Add("win", wordtier::easy); Add("lose", wordtier::easy); Add("code", wordtier::easy); Add("data", wordtier::easy);
		//Add("byte", wordtier::easy); Add("bit", wordtier::easy); Add("grid", wordtier::easy); Add("node", wordtier::easy);
		//Add("link", wordtier::easy); Add("list", wordtier::easy); Add("heap", wordtier::easy); Add("stack", wordtier::easy);
		//Add("key", wordtier::easy); Add("lock", wordtier::easy); Add("ring", wordtier::easy); Add("bell", wordtier::easy);
		//Add("song", wordtier::easy); Add("note", wordtier::easy); Add("tone", wordtier::easy); Add("beat", wordtier::easy);
		//Add("hero", wordtier::easy); Add("king", wordtier::easy); Add("queen", wordtier::easy); Add("lord", wordtier::easy);
		//Add("wolf", wordtier::easy); Add("lion", wordtier::easy); Add("bear", wordtier::easy); Add("deer", wordtier::easy);
		//Add("frog", wordtier::easy); Add("duck", wordtier::easy); Add("goat", wordtier::easy); Add("lamb", wordtier::easy);
		//Add("seed", wordtier::easy); Add("root", wordtier::easy); Add("vine", wordtier::easy); Add("bark", wordtier::easy);
		//Add("dust", wordtier::easy); Add("ash", wordtier::easy); Add("gold", wordtier::easy); Add("iron", wordtier::easy);
		//Add("silk", wordtier::easy); Add("wool", wordtier::easy); Add("coat", wordtier::easy); Add("shoe", wordtier::easy);
		//Add("sock", wordtier::easy); Add("belt", wordtier::easy); Add("mask", wordtier::easy); Add("cape", wordtier::easy);
		//Add("rope", wordtier::easy); Add("tool", wordtier::easy); Add("gear", wordtier::easy); Add("bolt", wordtier::easy);
		//Add("nail", wordtier::easy); Add("wood", wordtier::easy);

		////Medium Words
		//Add("apple", wordtier::medium); Add("table", wordtier::medium); Add("chair", wordtier::medium); Add("plant", wordtier::medium);
		//Add("stone", wordtier::medium); Add("water", wordtier::medium); Add("bread", wordtier::medium); Add("clock", wordtier::medium);
		//Add("paper", wordtier::medium); Add("pencil", wordtier::medium); Add("window", wordtier::medium); Add("bottle", wordtier::medium);
		//Add("button", wordtier::medium); Add("school", wordtier::medium); Add("garden", wordtier::medium); Add("street", wordtier::medium);
		//Add("bridge", wordtier::medium); Add("castle", wordtier::medium); Add("forest", wordtier::medium); Add("desert", wordtier::medium);
		//Add("island", wordtier::medium); Add("river", wordtier::medium); Add("animal", wordtier::medium); Add("rabbit", wordtier::medium);
		//Add("monkey", wordtier::medium); Add("tiger", wordtier::medium); Add("donkey", wordtier::medium); Add("ladder", wordtier::medium);
		//Add("hammer", wordtier::medium); Add("wallet", wordtier::medium); Add("pocket", wordtier::medium); Add("circle", wordtier::medium);
		//Add("square", wordtier::medium); Add("orange", wordtier::medium); Add("banana", wordtier::medium); Add("grapes", wordtier::medium);
		//Add("carrot", wordtier::medium); Add("potato", wordtier::medium); Add("tomato", wordtier::medium); Add("pepper", wordtier::medium);
		//Add("onion", wordtier::medium); Add("garlic", wordtier::medium); Add("cheese", wordtier::medium); Add("butter", wordtier::medium);
		//Add("silver", wordtier::medium); Add("golden", wordtier::medium); Add("summer", wordtier::medium); Add("winter", wordtier::medium);
		//Add("spring", wordtier::medium); Add("autumn", wordtier::medium); Add("cloudy", wordtier::medium); Add("rainy", wordtier::medium);
		//Add("sunny", wordtier::medium); Add("stormy", wordtier::medium); Add("bright", wordtier::medium); Add("simple", wordtier::medium);
		//Add("strong", wordtier::medium); Add("steady", wordtier::medium); Add("random", wordtier::medium); Add("silent", wordtier::medium);
		//Add("loudly", wordtier::medium); Add("travel", wordtier::medium); Add("planet", wordtier::medium); Add("rocket", wordtier::medium);
		//Add("galaxy", wordtier::medium); Add("meteor", wordtier::medium);

		////Hard Words
		//Add("picture", wordtier::hard); Add("measure", wordtier::hard); Add("mountain", wordtier::hard); Add("continue", wordtier::hard);
		//Add("balance", wordtier::hard); Add("battery", wordtier::hard); Add("weather", wordtier::hard); Add("whisper", wordtier::hard);
		//Add("capture", wordtier::hard); Add("treasure", wordtier::hard); Add("danger", wordtier::hard); Add("journey", wordtier::hard);
		//Add("mystery", wordtier::hard); Add("adventure", wordtier::hard); Add("control", wordtier::hard); Add("produce", wordtier::hard);
		//Add("perform", wordtier::hard); Add("imagine", wordtier::hard); Add("promise", wordtier::hard); Add("freedom", wordtier::hard);
		//Add("problem", wordtier::hard); Add("program", wordtier::hard); Add("element", wordtier::hard); Add("factory", wordtier::hard);
		//Add("machine", wordtier::hard); Add("diagram", wordtier::hard); Add("network", wordtier::hard); Add("history", wordtier::hard);
		//Add("library", wordtier::hard); Add("country", wordtier::hard); Add("language", wordtier::hard); Add("package", wordtier::hard);
		//Add("diamond", wordtier::hard); Add("sunlight", wordtier::hard); Add("rainbow", wordtier::hard); Add("starlight", wordtier::hard);
		//Add("firework", wordtier::hard); Add("airplane", wordtier::hard); Add("backpack", wordtier::hard); Add("doorbell", wordtier::hard);
		//Add("handmade", wordtier::hard); Add("blueprint", wordtier::hard); Add("keyboard", wordtier::hard); Add("notebook", wordtier::hard);
		//Add("rainstorm", wordtier::hard); Add("earthquake", wordtier::hard); Add("waterfall", wordtier::hard); Add("blackboard", wordtier::hard);
		//Add("football", wordtier::hard); Add("basketball", wordtier::hard); Add("sandstorm", wordtier::hard); Add("checkpoint", wordtier::hard);
		//Add("framework", wordtier::hard); Add("highlight", wordtier::hard); Add("overlap", wordtier::hard); Add("backward", wordtier::hard);
		//Add("forward", wordtier::hard); Add("somewhere", wordtier::hard);Add("somebody", wordtier::hard); Add("anything", wordtier::hard);

		////Insane Words
		//Add("extraordinary", wordtier::insane); Add("unbelievable", wordtier::insane);
		//Add("responsibility", wordtier::insane); Add("misunderstanding", wordtier::insane);
		//Add("communication", wordtier::insane); Add("international", wordtier::insane);
		//Add("transportation", wordtier::insane); Add("administration", wordtier::insane);
		//Add("configuration", wordtier::insane); Add("identification", wordtier::insane);
		//Add("representation", wordtier::insane); Add("rehabilitation", wordtier::insane);
		//Add("implementation", wordtier::insane); Add("authentication", wordtier::insane);
		//Add("synchronization", wordtier::insane); Add("recommendation", wordtier::insane);
		//Add("characterization", wordtier::insane); Add("classification", wordtier::insane);
		//Add("revolutionary", wordtier::insane); Add("extraordinary", wordtier::insane);
		//Add("extraordinary", wordtier::insane); Add("counterattack", wordtier::insane);
		//Add("overwhelming", wordtier::insane); Add("interruption", wordtier::insane);
		//Add("disappointment", wordtier::insane); Add("misinformation", wordtier::insane);
		//Add("understanding", wordtier::insane); Add("overestimation", wordtier::insane);
		//Add("miscommunication", wordtier::insane); Add("disqualification", wordtier::insane);
		//Add("reconstruction", wordtier::insane); Add("standardization", wordtier::insane);
		//Add("personalization", wordtier::insane); Add("globalization", wordtier::insane);
		//Add("industrialization", wordtier::insane); Add("capitalization", wordtier::insane);
		//Add("decentralization", wordtier::insane); Add("centralization", wordtier::insane);
		//Add("electromagnetic", wordtier::insane); Add("photosynthesis", wordtier::insane);
		//Add("cryptocurrency", wordtier::insane); Add("pseudoscientific", wordtier::insane);
		//Add("psychological", wordtier::insane); Add("philosophical", wordtier::insane);
		//Add("unpredictable", wordtier::insane); Add("incomprehensible", wordtier::insane);
		//Add("irreversibility", wordtier::insane); Add("irreconcilable", wordtier::insane);
		//Add("uncontrollable", wordtier::insane); Add("irreproducible", wordtier::insane);
		//Add("hyperventilation", wordtier::insane); Add("microtransaction", wordtier::insane);
		//Add("overcomplicated", wordtier::insane); Add("disproportionate", wordtier::insane);

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

