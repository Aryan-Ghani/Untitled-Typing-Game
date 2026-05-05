#include "GameOver.h"
#include "Framework.h"

GameOver::GameOver(Framework* parent, int score, int difficulty) : wxPanel(parent, wxID_ANY), myframe(parent) {
	SetBackgroundColour(*wxBLACK);

	wxString diffLabels[] = { "EASY", "MEDIUM", "HARD", "INSANE" };
	wxString difflabel = diffLabels[difficulty];

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

	wxButton* returnBtn = new wxButton(this, wxID_ANY, "RETURN TO MENU", wxDefaultPosition, wxSize(220, 48));
	returnBtn->SetBackgroundColour(*wxBLACK);
	returnBtn->SetForegroundColour(*wxWHITE);
	returnBtn->SetFont(wxFont(14, wxFONTFAMILY_TELETYPE,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	root->AddStretchSpacer(2);
	root->Add(overtxt, 0, wxALIGN_CENTER | wxBottom, 10);
	root->Add(difftxt, 0, wxALIGN_CENTER | wxBottom, 6);
	root->Add(scoretxt, 0, wxALIGN_CENTER | wxBottom, 30);
	root->Add(returnBtn, 0, wxALIGN_CENTER | wxBottom, 12);
	root->AddStretchSpacer(3);

	SetSizer(root);

	returnBtn->Bind(wxEVT_BUTTON, &GameOver::OnReturnClick, this);
}

void GameOver::OnReturnClick(wxCommandEvent&) {
	myframe->show_menu();
}
