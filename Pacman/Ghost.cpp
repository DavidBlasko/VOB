#include "Ghost.h"
#include "Map.h"
#include <cstdlib>

Ghost::Ghost(int x, int y) : x(x), y(y), alive(true) {}

// Move randomly in one of the four directions, if not blocked by a wall
void Ghost::move(const Map& map) {
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; ++i) {
        int dir = rand() % 4;
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (!map.isWall(nx, ny)) {
            x = nx;
            y = ny;
            break;
        }
    }
}

int Ghost::getX() const { return x; }
int Ghost::getY() const { return y; }
bool Ghost::isAlive() const { return alive; }
void Ghost::setAlive(bool value) { alive = value; }