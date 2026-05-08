#pragma once
#include <wx/wx.h>,
#include "DifficultyConfig.h"

class Framework;

class MainMenu : public wxPanel
{
public:
	MainMenu(Framework* parent);

private:
	void EasySelect(wxCommandEvent&);
	void MediumSelect(wxCommandEvent&);
	void HardSelect(wxCommandEvent&);
	void InsaneSelect(wxCommandEvent&);
	void LeaderboardSelect(wxCommandEvent&);

	void StartGame(Difficulty diff);

	Framework* myframe;
};

