#include "MainMenu.h"
#include "Framework.h"

MainMenu::MainMenu(Framework* parent) : wxPanel(parent, wxID_ANY), myframe(parent)
{
	SetBackgroundColour(*wxBLACK);

	wxBoxSizer* mylayout = new wxBoxSizer(wxVERTICAL);


	wxStaticText* title = new wxStaticText(this, wxID_ANY, "UNTITLED TYPING GAME");
	title->SetForegroundColour(*wxWHITE);
	title->SetFont(wxFont(42, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	wxStaticText* subtitle = new wxStaticText(this, wxID_ANY, "Select Difficulty");
	subtitle->SetForegroundColour(*wxLIGHT_GREY);
	subtitle->SetFont(wxFont(16, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));


	auto MakeButton = [&](const wxString& label, const wxColour& color, int id) {
		wxButton* btn = new wxButton(this, id, label, wxDefaultPosition, wxSize(220, 50));
		btn->SetBackgroundColour(*wxBLACK);
		btn->SetForegroundColour(color);
		btn->SetFont(wxFont(15, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

		return btn;
		};

	wxButton* easybutton = MakeButton("EASY", *wxWHITE, wxID_HIGHEST + 1);
	wxButton* mediumbutton = MakeButton("MEDIUM", *wxWHITE, wxID_HIGHEST + 2);
	wxButton* hardbutton = MakeButton("HARD", *wxWHITE, wxID_HIGHEST + 3);
	wxButton* insanebutton = MakeButton("INSANE", *wxWHITE, wxID_HIGHEST + 4);


	mylayout->AddStretchSpacer(2);
	mylayout->Add(title, 0, wxALIGN_CENTER | wxBOTTOM, 6);
	mylayout->Add(subtitle, 0, wxALIGN_CENTER | wxBOTTOM, 40);
	mylayout->Add(easybutton, 0, wxALIGN_CENTER | wxBOTTOM, 12);
	mylayout->Add(mediumbutton, 0, wxALIGN_CENTER | wxBOTTOM, 12);
	mylayout->Add(hardbutton, 0, wxALIGN_CENTER | wxBOTTOM, 12);
	mylayout->Add(insanebutton, 0, wxALIGN_CENTER | wxBOTTOM, 12);
	mylayout->AddStretchSpacer(3);

	
	SetSizer(mylayout);

	easybutton->Bind(wxEVT_BUTTON, &MainMenu::EasySelect, this);
	mediumbutton->Bind(wxEVT_BUTTON, &MainMenu::MediumSelect, this);
	hardbutton->Bind(wxEVT_BUTTON, &MainMenu::HardSelect, this);
	insanebutton->Bind(wxEVT_BUTTON, &MainMenu::InsaneSelect, this);
}

void MainMenu::EasySelect(wxCommandEvent&) { StartGame(Difficulty::easy); };
void MainMenu::MediumSelect(wxCommandEvent&) { StartGame(Difficulty::medium); };
void MainMenu::HardSelect(wxCommandEvent&) { StartGame(Difficulty::hard); };
void MainMenu::InsaneSelect(wxCommandEvent&) { StartGame(Difficulty::insane); };

void MainMenu::StartGame(Difficulty d) {
	myframe->show_game(DifficultyConfig::Make(d));
}
