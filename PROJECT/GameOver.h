#pragma once
#include <wx/wx.h>

class Framework;

class GameOver : public wxPanel
{
private:
	wxTextCtrl* mynameCtrl;
	int myscore = 0;
	int mydifficulty = 0;
	Framework* myframe;
	void OnReturnClick(wxCommandEvent&);
public:
	GameOver(Framework* parent, int score, int difficulty);
};

