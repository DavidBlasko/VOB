# 🟡 Pacman CLI Game (C++)

This project is a simplified, console-based Pacman game written in modern **C++** using **Object-Oriented Programming (OOP)**. It simulates core game mechanics like player movement, enemy (ghost), item collection, power-ups, and win/lose conditions — all within a terminal window.

---

## 🎮 Gameplay Overview

You control Pacman (`@`) in a maze filled with small dots (`.`) and large power-up cookies (`o`). Two ghosts (`G`) roam randomly. Your goal is to **collect all dots or eliminate both ghosts** after using a power-up.

- **If you collect all dots:** You win.
- **If a ghost touches you without power-up:** Game over.
- **If you eat a power-up (`o`)**: You have 5 seconds to "eat" ghosts.
- **Eliminated ghosts disappear permanently.**

---

## 🧠 Game Logic

The game runs on a loop:

```cpp
while (isRunning) {
    handleInput();   // arrow keys or ESC
    update();        // move player/ghosts, collision check
    render();        // draw map to console
}
```

- **Power-ups** last for ~5 seconds (300 frames at 60 FPS).
- Ghosts move randomly, one step per frame.
- Player can collect dots, power-ups, and eliminate ghosts when powered up.
- Game ends with either victory or defeat and waits for a key press.

---

## 📁 Project Structure

```
Pacman/
├── main.cpp              // Starts the game
├── Game.h / Game.cpp     // Game loop, input, update, rendering
├── Map.h / Map.cpp       // Map layout and logic
├── Player.h / Player.cpp // Player logic and score
└── Ghost.h / Ghost.cpp   // Ghost behavior
```

---

## 🔍 Class Responsibilities

### `Game`
- Manages main game loop (`run()`).
- Processes input, updates state, checks win/loss.
- Holds references to player, ghosts, map.
- Handles rendering and end game messages.

### `Player`
- Tracks position, score, and power-up state.
- Handles arrow key movement.
- Interacts with map (collect dots/power-ups).
- Can collide with ghosts.

### `Ghost`
- Has position and alive state.
- Moves randomly if alive.
- Disappears permanently when defeated.

### `Map`
- Stores a static 2D map layout using `std::vector<std::string>`.
- Tracks dots and power-ups.
- Renders full game state including player and ghosts.

---

## 🕹️ Controls

| Key       | Action       |
|-----------|--------------|
| ↑ ↓ ← →  | Move player  |
| ESC       | Exit game    |

---

## 🧱 Requirements

- Windows (uses `conio.h`, `system("cls")`)
- C++11 or newer
- Console terminal with monospace font
- Recommended: Visual Studio, Code::Blocks or `g++`

---

## ⚙️ How to Compile and Run

### 🧪 Compile via g++
```bash
g++ main.cpp Game.cpp Map.cpp Player.cpp Ghost.cpp -o pacman.exe
pacman.exe
```

### 🧪 Compile via Visual Studio
- Open `.sln` or `.vcxproj` file.
- Press **F5** to run in Debug mode.

---

## 📸 Game Preview

```
####################
#........##........#
#.####.#.##G####.#.#
#.#  #.#.##.#  #.#.#
#.####.#.##.####.#.#
#..@...........o.. #
#G####.######.####.#
#.####.######.####.#
#........##........#
####################

Score: 12
POWER-UP ACTIVE!
```

---

## 📄 License

This project is free and open source.  
Use and modify it freely for learning, education or personal projects.

---