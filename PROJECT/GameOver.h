#pragma once
#include <wx/wx.h>

class Framework;

class GameOver : public wxPanel
{
private:
	Framework* myframe;
	void OnReturnClick(wxCommandEvent&);
public:
	GameOver(Framework* parent, int score, int difficulty);
};

