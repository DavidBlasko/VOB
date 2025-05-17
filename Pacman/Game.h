#pragma once
#include "Player.h"
#include "Ghost.h"
#include "Map.h"
#include <vector>

// Main class that manages the game loop and interactions
class Game {
public:
    Game();
    void run();
private:
    Map map;                        // Game map
    Player player;                  // Player object
    std::vector<Ghost> ghosts;      // List of ghosts
    bool isRunning;                 // Game running flag
    std::string endMessage;         // Holds the win/lose message to show after loop

    void handleInput();             // Handles user input
    void update();                  // Updates game state
    void render();                  // Renders the game to console
};