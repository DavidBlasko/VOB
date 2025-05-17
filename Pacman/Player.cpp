#include "Player.h"
#include "Map.h"
#include <conio.h>

// Constructor initializes position and score
Player::Player(int x, int y) : x(x), y(y), score(0), poweredUp(false), powerUpTimer(0) {}

// Handle movement keys and collect items
void Player::handleInput(int key, Map& map) {
    int dx = 0, dy = 0;
    switch (key) {
    case 72: dy = -1; break; // Arrow up
    case 80: dy = 1; break;  // Arrow down
    case 75: dx = -1; break; // Arrow left
    case 77: dx = 1; break;  // Arrow right
    }

    if (!map.isWall(x + dx, y + dy)) {
        x += dx;
        y += dy;

        if (map.isDot(x, y)) {
            map.collectDot(x, y);
            score++;
        }
        else if (map.isPowerUp(x, y)) {
            map.collectPowerUp(x, y);
            poweredUp = true;
            powerUpTimer = 300; // Power-up lasts 300 frames
        }
    }
}

// Decrease power-up timer every frame
void Player::updatePowerUpState() {
    if (poweredUp) {
        powerUpTimer--;
        if (powerUpTimer <= 0) poweredUp = false;
    }
}

bool Player::isPoweredUp() const { return poweredUp; }
int Player::getX() const { return x; }
int Player::getY() const { return y; }
int Player::getScore() const { return score; }
void Player::addScore(int value) { score += value; }

// Checks for collision with a ghost
bool Player::collidesWith(const Ghost& ghost) const {
    return ghost.getX() == x && ghost.getY() == y;
}