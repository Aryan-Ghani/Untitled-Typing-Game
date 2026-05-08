#pragma once
#include <wx/wx.h>
#include "Leaderboard.h"

class Framework;

class LeaderboardPanel : public wxPanel {
public:
    LeaderboardPanel(Framework* parent, Leaderboard& leaderboard);

private:
    void OnBackClick(wxCommandEvent&);
    Framework* myframe;
};