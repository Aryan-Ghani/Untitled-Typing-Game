#include "Framework.h"
#include "MainMenu.h"
#include "GamePanel.h"
#include "GameOver.h"

Framework::Framework(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size), currentpanel(nullptr) {

	SetMinSize(size);
	SetMaxSize(size);

	sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(sizer);

	show_menu();
}

void Framework::show_menu() {
	if (currentpanel)
	{
		currentpanel->Destroy();
		currentpanel = nullptr;
	}

	MainMenu* menu = new MainMenu(this);
	sizer->Add(menu, 1, wxEXPAND);
	sizer->Layout();
	currentpanel = menu;
}

void Framework::show_game(const DifficultyConfig& config) {
	if (currentpanel)
	{
		currentpanel->Destroy();
		currentpanel = nullptr;
	}

	GamePanel* game = new GamePanel(this, config);
	sizer->Add(game, 1, wxEXPAND);
	sizer->Layout();
	currentpanel = game;
	game->SetFocus();
}

void Framework::show_gameover(int score, int difficulty) {
	if (currentpanel)
	{
		currentpanel->Destroy();
		currentpanel = nullptr;
	}

	GameOver* gameover = new GameOver(this, score, difficulty);
	sizer->Add(gameover, 1, wxEXPAND);
	sizer->Layout();
	currentpanel = gameover;
}

