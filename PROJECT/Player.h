#pragma once
class Player
{
public:
	int lives;
	int score;
	int max_lives;

	Player(int startingLives = 3) : lives(startingLives), score(startingLives), max_lives(5) {}

	bool isAlive() {
		return lives > 0;
	}
	bool gainlife() {
		if (lives < max_lives)
		{
			lives++;
			return true;
		}
		return false;
	}
	void add_score(int n) {
		score += n;
	}
	void loselife() {
		if (lives > 0)
		{
			lives--;
		}
	}
};
