#include "Map.h"
#include <iostream>
#include <algorithm>

// Constructor initializes the map layout with walls, dots, and power-ups
Map::Map() {
    data = {
        "####################",
        "#........##........#",
        "#.####.#.##.####.#.#",
        "#.#  #.#.##.#  #.#.#",
        "#.####.#.##.####.#.#",
        "#..o...........o.. #",
        "#.####.######.####.#",
        "#.####.######.####.#",
        "#........##........#",
        "####################"
    };
}

// Draws the entire map with player and ghosts
void Map::draw(const Player& player, const std::vector<Ghost>& ghosts) const {
    for (int y = 0; y < data.size(); ++y) {
        for (int x = 0; x < data[y].size(); ++x) {
            if (x == player.getX() && y == player.getY()) {
                std::cout << '@';  // Player character
            }
            else {
                bool ghostPrinted = false;
                for (const auto& ghost : ghosts) {
                    if (ghost.isAlive() && x == ghost.getX() && y == ghost.getY()) {
                        std::cout << 'G';  // Ghost character
                        ghostPrinted = true;
                        break;
                    }
                }
                if (!ghostPrinted) std::cout << data[y][x];  // Print map element
            }
        }
        std::cout << std::endl;
    }
}

bool Map::isWall(int x, int y) const {
    return data[y][x] == '#';
}

bool Map::isDot(int x, int y) const {
    return data[y][x] == '.';
}

bool Map::isPowerUp(int x, int y) const {
    return data[y][x] == 'o';
}

void Map::collectDot(int x, int y) {
    if (data[y][x] == '.') data[y][x] = ' ';
}

void Map::collectPowerUp(int x, int y) {
    if (data[y][x] == 'o') data[y][x] = ' ';
}

// Returns number of remaining dots
int Map::remainingDots() const {
    int count = 0;
    for (const auto& row : data) {
        count += std::count(row.begin(), row.end(), '.');
    }
    return count;
}