#pragma once
#include <wx/wx.h>
#include "WordList.h"

//add file handling
//think about virtual functions

enum class PowerUpType {
    None,
    ExtraLife,
    FreezeTime
};

class Asteroid
{
public:
    wxString word;
    int typedsofar;
    bool targeted;
    double x, y;
    double velx, vely;
    float speed;
    PowerUpType powerup;
    wordtier tier;

    Asteroid(const wxString w, wordtier t, double startx, double starty, double vx, double vy,
        float spd, PowerUpType p = PowerUpType::None) {
        word = w;
        tier = t;
        x = startx;
        y = starty;
        velx = vx;
        vely = vy;
        speed = spd;
        powerup = p;
        typedsofar = 0;
        targeted = false;
    }

    bool haspowerup() {
        return powerup != PowerUpType::None;
    }

    void update() {
        x += velx * speed;
        y += vely * speed;
    }

    wxString typedpart() {
        return word.Left(typedsofar);
    }
    wxString remainingpart() {
        return word.Mid(typedsofar);
    }
};

