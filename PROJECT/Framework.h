#pragma once
#include <wx/wx.h>
#include "DifficultyConfig.h"
#include "Leaderboard.h"

//class MainMenu;
//class GamePanel;
//class GameOver;


class Framework : public wxFrame
{
private:
	wxPanel* currentpanel;
	wxBoxSizer* sizer;
	Leaderboard myleaderboard;

public:
	Framework(const wxString& title, const wxPoint& pos, const wxSize& size);

	void show_menu();
	void show_game(const DifficultyConfig& config);
	void show_gameover(int score, int difficulty);
	void ShowLeaderboard();

	Leaderboard& GetLeaderboard() { return myleaderboard; };
};

