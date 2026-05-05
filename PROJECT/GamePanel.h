#pragma once
#include <wx/wx.h>
#include <vector>
#include "Asteroid.h"
#include "Player.h"
#include "DifficultyConfig.h"
#include "Framework.h"
#include "GameOver.h"
#include "WordList.h"

class GamePanel : public wxPanel
{
public:
	GamePanel(Framework* parent, DifficultyConfig config);

private:
	Player myplayer;
	std::vector<Asteroid> myasteroids;
	WordList mywords;
	bool gameover;

	int tickCount;
	int spawnInterval;

	bool isfrozen;
	int freezeticks;
	int freezeduration;

	wxTimer gametimer;
	DifficultyConfig myconfig;
	Framework* myframe;

	void OnTick(wxTimerEvent& evt);
	void OnPaint(wxPaintEvent& evt);
	void OnKeyDown(wxKeyEvent& evt);

	void UpdateSpawnRate();

	int calcScore(const Asteroid& a);
	void SpawnAsteroid();
	void UpdateAsteroid();
	void CheckCollisions();
	void HandleTyping(wxChar ch);
	void Draw(wxDC& dc);
	PowerUpType RollPowerup();
	void ApplyPowerup(PowerUpType p);


	wxDECLARE_EVENT_TABLE();

};

