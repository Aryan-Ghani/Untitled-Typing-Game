#pragma once

enum class Difficulty{easy, medium, hard, insane};

class DifficultyConfig
{
public:
	Difficulty difficulty;
	int spawn_interval;
	int min_spawn_interval;
	float asteroid_speed;
	int powerup_chance;
	int starting_lives;

	static DifficultyConfig Make(Difficulty d) {
		DifficultyConfig gamediff;
		gamediff.difficulty = d;
		switch (d) {
		case Difficulty::easy:
			gamediff.spawn_interval = 180;
			gamediff.min_spawn_interval = 90;
			gamediff.asteroid_speed = 0.6f;
			gamediff.powerup_chance = 25;
			gamediff.starting_lives = 5;
			break;
		case Difficulty::medium:
			gamediff.spawn_interval = 120;
			gamediff.min_spawn_interval = 60;
			gamediff.asteroid_speed = 1.0f;
			gamediff.powerup_chance = 20;
			gamediff.starting_lives = 3;
			break;
		case Difficulty::hard:
			gamediff.spawn_interval = 70;
			gamediff.min_spawn_interval = 40;
			gamediff.asteroid_speed = 1.2f;
			gamediff.powerup_chance = 15;
			gamediff.starting_lives = 3;
			break;
		case Difficulty::insane:
			gamediff.spawn_interval = 50;
			gamediff.min_spawn_interval = 20;
			gamediff.powerup_chance = 10;
			gamediff.asteroid_speed = 1.4f;
			gamediff.starting_lives = 2;
			break;
		}
		return gamediff;
	}

};

