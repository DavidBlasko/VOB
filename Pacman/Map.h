#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Ghost.h"

//Represents the game map as 2D grid of characters
class Map {
public:
    Map();
    void draw(const Player& player, const std::vector<Ghost>& ghosts) const;
    bool isWall(int x, int y) const;
    bool isDot(int x, int y) const;
    bool isPowerUp(int x, int y) const;
    void collectDot(int x, int y);
    void collectPowerUp(int x, int y);
    int remainingDots() const;
private:
    std::vector<std::string> data; // The map layout
};