#include <wx/statline.h>
#include "leaderboardPanel.h"
#include "Framework.h"

LeaderboardPanel::LeaderboardPanel(Framework* parent, Leaderboard& leaderboard)
    : wxPanel(parent, wxID_ANY), myframe(parent)
{
    SetBackgroundColour(*wxBLACK);
    wxBoxSizer* root = new wxBoxSizer(wxVERTICAL);

    wxStaticText* title = new wxStaticText(this, wxID_ANY, "LEADERBOARD");
    title->SetForegroundColour(*wxWHITE);
    title->SetFont(wxFont(32, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    root->AddStretchSpacer(1);
    root->Add(title, 0, wxALIGN_CENTER | wxBOTTOM, 30);

    wxBoxSizer* headerRow = new wxBoxSizer(wxHORIZONTAL);
    auto MakeHeader = [&](const wxString& text, int width) {
        wxStaticText* t = new wxStaticText(this, wxID_ANY, text,
            wxDefaultPosition, wxSize(width, -1));
        t->SetForegroundColour(wxColour(160, 160, 160));
        t->SetFont(wxFont(11, wxFONTFAMILY_TELETYPE,
            wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        return t;
        };

    headerRow->Add(MakeHeader("#", 40), 0, wxALIGN_CENTER_VERTICAL);
    headerRow->Add(MakeHeader("NAME", 200), 0, wxALIGN_CENTER_VERTICAL);
    headerRow->Add(MakeHeader("SCORE", 120), 0, wxALIGN_CENTER_VERTICAL);
    headerRow->Add(MakeHeader("DIFFICULTY", 120), 0, wxALIGN_CENTER_VERTICAL);
    root->Add(headerRow, 0, wxALIGN_CENTER | wxBOTTOM, 8);

    wxStaticLine* line = new wxStaticLine(this, wxID_ANY,
        wxDefaultPosition, wxSize(480, 1));
    root->Add(line, 0, wxALIGN_CENTER | wxBOTTOM, 12);

    const auto& entries = leaderboard.GetEntries();

    wxColour rankColours[] = {
        wxColour(255, 215,   0),
        wxColour(192, 192, 192),
        wxColour(205, 127,  50),
        wxColour(200, 200, 200),
        wxColour(200, 200, 200),
    };

    for (int i = 0; i < Leaderboard::MAX_ENTRIES; i++)
    {
        wxBoxSizer* row = new wxBoxSizer(wxHORIZONTAL);
        wxColour col = (i < (int)entries.size()) ? rankColours[i] : wxColour(80, 80, 80);

        auto MakeCell = [&](const wxString& text, int width) {
            wxStaticText* t = new wxStaticText(this, wxID_ANY, text, wxDefaultPosition, wxSize(width, -1));
            t->SetForegroundColour(col);
            t->SetFont(wxFont(13, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
            return t;
            };

        if (i < (int)entries.size())
        {
            const auto& e = entries[i];
            row->Add(MakeCell(wxString::Format("%d.", i + 1), 40));
            row->Add(MakeCell(e.name, 200));
            row->Add(MakeCell(wxString::Format("%d", e.score), 120));
            row->Add(MakeCell(e.difficulty, 120));
        }
        else
        {
            row->Add(MakeCell("-", 40));
            row->Add(MakeCell("---", 200));
            row->Add(MakeCell("---", 120));
            row->Add(MakeCell("---", 120));
        }
        root->Add(row, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    }

    wxButton* backBtn = new wxButton(this, wxID_ANY, "BACK TO MENU",
        wxDefaultPosition, wxSize(220, 44));
    backBtn->SetBackgroundColour(*wxBLACK);
    backBtn->SetForegroundColour(*wxWHITE);
    backBtn->SetFont(wxFont(13, wxFONTFAMILY_TELETYPE,
        wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    root->AddSpacer(24);
    root->Add(backBtn, 0, wxALIGN_CENTER);
    root->AddStretchSpacer(1);

    SetSizer(root);
    backBtn->Bind(wxEVT_BUTTON, &LeaderboardPanel::OnBackClick, this);
}

void LeaderboardPanel::OnBackClick(wxCommandEvent&) {
    myframe->show_menu();
}