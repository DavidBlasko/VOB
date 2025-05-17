#include "Game.h"
#include <iostream>
#include <thread>
#include <conio.h>
#include <algorithm>

Game::Game() : player(1, 1), isRunning(true) {
    // Initialize two ghosts at different positions
    ghosts.emplace_back(18, 1);
    ghosts.emplace_back(1, 8);
}

void Game::run() {
    while (isRunning) {
        handleInput();  // Get player input
        update();       // Update positions and game logic
        render();       // Draw current state to console
        std::this_thread::sleep_for(std::chrono::milliseconds(60)); // 60 FPS
    }
    std::cout << endMessage << std::endl;
}

void Game::handleInput() {
    if (_kbhit()) {
        int key = _getch();                 // Read a key press
        player.handleInput(key, map);       // Let player move
        if (key == 27) isRunning = false;   // Exit on ESC key
    }
}

void Game::update() {
    player.updatePowerUpState();  // Decrease power-up timer

    for (auto& ghost : ghosts) {
        if (!ghost.isAlive()) continue;
        ghost.move(map);  // Move ghost randomly

        // Handle collision with player
        if (player.collidesWith(ghost)) {
            if (player.isPoweredUp()) {
                ghost.setAlive(false);  // Ghost defeated
                player.addScore(10);    // Bonus points
            }
            else {
                endMessage = "GAME OVER!";
                isRunning = false;
            }
        }
    }

    // Check win condition
    bool allGhostsDefeated = std::all_of(ghosts.begin(), ghosts.end(), [](const Ghost& g) { return !g.isAlive(); });
    if (map.remainingDots() == 0 || allGhostsDefeated) {
        endMessage = "YOU WIN!";
        isRunning = false;
    }
}

void Game::render() {
    system("cls");              // Clear console screen
    map.draw(player, ghosts);   // Render game map with player and ghosts
    std::cout << "Score: " << player.getScore() << std::endl;
    if (player.isPoweredUp()) {
        std::cout << "POWER-UP ACTIVE!" << std::endl;
    }
}