#include "GamePanel.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

wxBEGIN_EVENT_TABLE(GamePanel, wxPanel)
EVT_TIMER(wxID_ANY, GamePanel::OnTick)
EVT_PAINT(GamePanel::OnPaint)
EVT_KEY_DOWN(GamePanel::OnKeyDown)
wxEND_EVENT_TABLE()

GamePanel::GamePanel(Framework* parent, DifficultyConfig config) : wxPanel(parent, wxID_ANY), 
myplayer(config.starting_lives), 
gameover(false), tickCount(0), myconfig(config), spawnInterval(config.spawn_interval),
myframe(parent),
isfrozen(false),
freezeticks(0),
freezeduration(360)
{
	srand(time(0));
	SetBackgroundColour(*wxBLACK);
	SetFocus();

	gametimer.Bind(wxEVT_TIMER, &GamePanel::OnTick, this);
	gametimer.Start(16);

}

void GamePanel::OnTick(wxTimerEvent&) {
	if (gameover) {
		return;
	}

	if (isfrozen) {
		freezeticks--;
		if (freezeticks <= 0)
		{
			isfrozen = false;
		}
		Refresh();
		return;
	}

	tickCount++;
	if (tickCount % spawnInterval == 0)
	{
		SpawnAsteroid();
	}
	UpdateAsteroid();
	UpdateSpawnRate();
	CheckCollisions();
	Refresh();
}


PowerUpType GamePanel::RollPowerup() {
	int roll = rand() % 100;
	if (roll < 60)
	{
		return PowerUpType::ExtraLife;
	}
	return PowerUpType::FreezeTime;
}

void GamePanel::SpawnAsteroid(){
	wxSize size = GetSize();
	int centrex = size.GetWidth() / 2;
	int centrey = size.GetHeight() / 2;

	double sidex, sidey;
	int edge = rand() % 4;
	if (edge == 0)
	{
		sidex = rand() % size.GetWidth();
		sidey = 0;
	}
	else if (edge == 1)
	{
		sidex = rand() % size.GetWidth();
		sidey = size.GetHeight();
	}
	else if (edge == 2)
	{
		sidex = 0;
		sidey = rand() % size.GetHeight();
	}
	else {
		sidex = size.GetWidth();
		sidey = rand() % size.GetHeight();
	}

	double directionx = centrex - sidex;
	double directiony = centrey - sidey;
	double len = std::sqrt(directionx * directionx + directiony * directiony);
	directionx /= len;
	directiony /= len;

	wordentry entry = mywords.getoneword(myconfig.difficulty);
	float speed = myconfig.asteroid_speed * WordList::speed_multiplier(entry.tier);

	PowerUpType p = PowerUpType::None;
	if ((rand() % 100) < myconfig.powerup_chance)
	{
		p = RollPowerup();
	}

	myasteroids.emplace_back(entry.word, entry.tier, sidex, sidey, directionx, directiony, speed, p);
}

void GamePanel::UpdateAsteroid() {
	for (auto& a : myasteroids)
	{
		a.update();
	}
}

void GamePanel::UpdateSpawnRate() {
	const int scorecap = 5000;
	float t = std::min((float)myplayer.score / scorecap, 1.0f);

	int start = myconfig.spawn_interval;
	int min_interval = myconfig.min_spawn_interval;
	spawnInterval = int(start + t * (min_interval - start));
}

void GamePanel::CheckCollisions() {
	wxSize size = GetSize();
	int centerx = size.GetWidth() / 2;
	int centery = size.GetHeight() / 2;
	const int hit_radius = 40;
	auto it = myasteroids.begin();
	while (it != myasteroids.end())
	{
		double directionx = it->x - centerx;
		double directiony = it->y - centery;
		double dist = std::sqrt(directionx * directionx + directiony * directiony);

		if (dist < hit_radius)
		{
			myplayer.loselife();
			it = myasteroids.erase(it);

			if (!myplayer.isAlive())
			{
				gameover = true;
				gametimer.Stop();
				int gamediff;
				myframe->show_gameover(myplayer.score, int(myconfig.difficulty));
				return;
			}
		}
		else
		{
			++it;
		}

	}
}

void GamePanel::ApplyPowerup(PowerUpType p) {
	switch (p)
	{
	case PowerUpType::ExtraLife:
		myplayer.gainlife();
		break;
	case PowerUpType::FreezeTime:
		isfrozen = true;
		freezeticks = freezeduration;
		break;
	default:
		break;
	}
}

int GamePanel::calcScore(const Asteroid& a) {
	int basepoints = a.word.length() * 10;

	float tierMultiplier;
	switch (a.tier)
	{
	case wordtier::easy:
		tierMultiplier = 1.0f;
		break;
	case wordtier::medium:
		tierMultiplier = 1.5f;
		break;
	case wordtier::hard:
		tierMultiplier = 2.5f;
		break;
	case wordtier::insane:
		tierMultiplier = 4.0f;
		break;
	default:
		tierMultiplier = 1.0f;
		break;
	}

	return (int)(basepoints * tierMultiplier);
}

void GamePanel::HandleTyping(wxChar ch) {
	Asteroid* target = nullptr;
	for (auto& a : myasteroids )
	{
		if (a.targeted)
		{
			target = &a;
			break;
		}
	}

	if (!target)
	{
		for (auto& a : myasteroids )
		{
			if (!a.word.IsEmpty() && a.word[0] == ch)
			{
				a.targeted = true;
				a.typedsofar = 1;
				target = &a;
				break;
			}
		}
		return;
	}

	if (target->typedsofar < (int)target->word.length() &&
		target->word[target->typedsofar] == ch)
	{
		target->typedsofar++;

		if (target->typedsofar == (int)target->word.Len())
		{
			myplayer.add_score(calcScore(*target));
			if (target->haspowerup())
			{
				ApplyPowerup(target->powerup);
			}

			myasteroids.erase(std::remove_if(myasteroids.begin(), myasteroids.end(),
				[](const Asteroid& a) {return a.targeted;}), myasteroids.end());
		}
	}
	else
	{
		myplayer.loselife();
		target->targeted = false;
		target->typedsofar = 0;

		if (!myplayer.isAlive())
		{
			gameover = true;
			gametimer.Stop();
			myframe->show_gameover(myplayer.score, (int)myconfig.difficulty);
		}
	}
}

void GamePanel::OnKeyDown(wxKeyEvent& evt) {
	if (gameover)
	{
		return;
	}

	wxChar ch = evt.GetUnicodeKey();
	if (ch != WXK_NONE && wxIsalpha(ch))
	{
		HandleTyping(wxTolower(ch));
	}
}

void GamePanel::OnPaint(wxPaintEvent&) {
	wxPaintDC dc(this);
	Draw(dc);
}

void GamePanel::Draw(wxDC& dc) {
	wxSize size = GetSize();
	int centerx = size.GetWidth() / 2;
	int centery = size.GetHeight() / 2;

	auto TierColour = [](wordtier t) -> wxColour {
		switch (t) {
		case wordtier::easy: return wxColour(*wxWHITE); break;
		case wordtier::medium: return wxColour(255, 220, 80); break;
		case wordtier::hard: return wxColour(225, 120, 40); break;
		case wordtier::insane: return wxColour(255, 50, 50); break;
		}
		return *wxWHITE;
	};

	dc.SetBackground(*wxBLACK_BRUSH);
	dc.Clear();

	dc.SetPen(wxPen(*wxCYAN, 2));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	dc.DrawCircle(centerx, centery, 20);

	dc.SetFont(wxFont(12, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	for (auto& a : myasteroids)
	{
		int ax = (int)a.x;
		int ay = (int)a.y;

		wxColour rockColour;
		if (isfrozen && !a.targeted)
		{
			rockColour = wxColour(80, 160, 255);
		}
		else if (a.targeted)
		{
			rockColour = wxColour(*wxYELLOW);
		}
		else if (a.haspowerup()) {
			switch (a.powerup) {
			case PowerUpType::ExtraLife: rockColour = wxColour(0, 220, 100); break;
			case PowerUpType::FreezeTime: rockColour = wxColour(80, 160, 255); break;
			default: rockColour = *wxWHITE; break;
			}
		}
		else {
			rockColour = TierColour(a.tier);
		}

		dc.SetPen(wxPen(rockColour, a.haspowerup() ? 2 : 1));
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		dc.DrawCircle(ax, ay, 22);

		if (a.haspowerup())
		{
			dc.SetFont(wxFont(12, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
			dc.SetTextForeground(rockColour);
			wxString label;
			switch (a.powerup) {
			case PowerUpType::ExtraLife: label = "[+LIFE]"; break;
			case PowerUpType::FreezeTime: label = "[FREEZE]"; break;
			default: break;
			}
			wxSize labelsize = dc.GetTextExtent(label);
			dc.DrawText(label, ax - labelsize.GetWidth() / 2, ay - 36);
		}

		wxString typed = a.typedpart();
		wxString remaining = a.remainingpart();

		wxSize textsize = dc.GetTextExtent(a.word);
		int tx = ax - textsize.GetWidth() / 2;
		int ty = ay + 26;

		dc.SetTextForeground(*wxGREEN);
		dc.DrawText(typed, tx, ty);

		wxSize typedsize = dc.GetTextExtent(typed);
		dc.SetTextForeground(*wxWHITE);
		dc.DrawText(remaining, tx + typedsize.GetWidth(), ty);
	}
	if (isfrozen)
	{
		float secsleft = freezeticks / 60.0f;

		dc.SetFont(wxFont(14, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
		dc.SetTextForeground(wxColour(80, 160, 255));

		wxString msg = wxString::Format("** TIME FROZEN ** %.1fs", secsleft);
		wxSize msgsize = dc.GetTextExtent(msg);
		dc.DrawText(msg, size.GetWidth() / 2 - msgsize.GetWidth() / 2, 10);
	}

	dc.SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	dc.SetTextForeground(*wxWHITE);
	dc.DrawText(wxString::Format("Lives: %d", myplayer.lives), 10, 10);
	dc.DrawText(wxString::Format("Score: %d", myplayer.score), 10, 30);
	float pressure = std::min((float)myplayer.score / 5000.0f, 1.0f) * 100.0f;
	dc.DrawText(wxString::Format("Intensity: %d%%", (int)pressure), 10, 50);

	if (gameover) 
	{
		dc.SetFont(wxFont(36, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
		dc.SetTextForeground(*wxRED);
		wxString msg = "GAME OVER";
		wxSize msgsize = dc.GetTextExtent(msg);
		dc.DrawText(msg, centerx - msgsize.GetWidth() / 2, centery - msgsize.GetHeight() / 2);
	}
}