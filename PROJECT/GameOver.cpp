#include "GameOver.h"
#include "Framework.h"

int scores = 0;

GameOver::GameOver(Framework* parent, int score, int difficulty) : wxPanel(parent, wxID_ANY), myframe(parent) {
	SetBackgroundColour(*wxBLACK);
	scores = score;
	wxString diffLabels[] = { "EASY", "MEDIUM", "HARD", "INSANE" };
	wxString difflabel = diffLabels[difficulty];
	mydifficulty = difficulty;

	wxBoxSizer* root = new wxBoxSizer(wxVERTICAL);

	wxStaticText* overtxt = new wxStaticText(this, wxID_ANY, "GAME OVER");
	overtxt->SetForegroundColour(*wxRED);
	overtxt->SetFont(wxFont(42, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	
	wxStaticText* difftxt = new wxStaticText(this, wxID_ANY, wxString::Format("Difficulty: %s", difflabel));
	difftxt->SetForegroundColour(*wxLIGHT_GREY);
	difftxt->SetFont(wxFont(14, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	wxStaticText* scoretxt = new wxStaticText(this, wxID_ANY, wxString::Format("Score: %d", score));
	scoretxt->SetForegroundColour(*wxWHITE);
	scoretxt->SetFont(wxFont(24, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	wxStaticText* nameLbl = new wxStaticText(this, wxID_ANY, "Enter your name:");
	nameLbl->SetForegroundColour(wxColour(160, 160, 160));
	nameLbl->SetFont(wxFont(12, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	mynameCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(220, 32));
	mynameCtrl->SetMaxLength(16);
	mynameCtrl->SetFont(wxFont(13, wxFONTFAMILY_TELETYPE,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	wxButton* returnBtn = new wxButton(this, wxID_ANY, "SAVE AND RETURN TO MENU", wxDefaultPosition, wxSize(300, 48));
	returnBtn->SetBackgroundColour(*wxBLACK);
	returnBtn->SetForegroundColour(*wxWHITE);
	returnBtn->SetFont(wxFont(14, wxFONTFAMILY_TELETYPE,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	root->AddStretchSpacer(2);
	root->Add(overtxt, 0, wxALIGN_CENTER | wxBottom, 10);
	root->Add(difftxt, 0, wxALIGN_CENTER | wxBottom, 6);
	root->Add(scoretxt, 0, wxALIGN_CENTER | wxBottom, 30);
	root->Add(nameLbl, 0, wxALIGN_CENTER | wxBottom, 6);
	root->Add(mynameCtrl, 0, wxALIGN_CENTER | wxBottom, 16);
	root->Add(returnBtn, 0, wxALIGN_CENTER | wxBottom, 12);
	root->AddStretchSpacer(3);

	SetSizer(root);

	returnBtn->Bind(wxEVT_BUTTON, &GameOver::OnReturnClick, this);
}

void GameOver::OnReturnClick(wxCommandEvent&) {
	wxString name = mynameCtrl->GetValue().Trim();
	const wxString diffLabels[] = { "Easy", "Medium", "Hard", "Insane" };

	myframe->GetLeaderboard().AddEntry(
		name.IsEmpty() ? "Anonymous" : name,
		scores,
		diffLabels[mydifficulty]
	);
	myframe->show_menu();
}
