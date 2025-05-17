#pragma once
#include "Ghost.h"

class Map;

// Handling player movement and interactions (score, power-up)
class Player {
public:
    Player(int x, int y);
    void handleInput(int key, Map& map);
    void updatePowerUpState();
    bool isPoweredUp() const;
    int getX() const;
    int getY() const;
    int getScore() const;
    void addScore(int value);
    bool collidesWith(const Ghost& ghost) const;
private:
    int x, y;
    int score;
    bool poweredUp;
    int powerUpTimer;
};