# Neon Drop

A fast-paced SFML arcade game where colorful shapes fall from the sky and you click them before they reach the bottom.

## 🎮 Gameplay

- You are playing a survival clicker.
- Falling enemies spawn at random positions.
- Each shape has a different score value.
- Clicking a target destroys it and adds points.
- If too many enemies slip past you, your health drops.
- When health reaches zero, the game ends.

## 🕹️ Controls

- Left click: destroy a falling enemy
- Enter: restart after game over
- Esc: exit the game

## ✨ Why this game feels fun

- Simple arcade loop
- Quick reactions
- Randomized enemy sizes and colors
- Score chasing and retry loop
- Clean SFML rendering with a minimal UI

## 🚀 Running the game

### Prerequisites

- CMake
- A C++ compiler
- Git

### Build and run

```bash
git clone <your-repo-url>
cd neon-drop
cmake -S . -B build
cmake --build build
./build/bin/MyGame
```

## 🧩 Project type

This project is built with:

- C++20
- SFML 3
- CMake

## 📁 Main files

- `src/main.cpp` — application entry point
- `src/Game.cpp` — game loop, spawning, updates, rendering
- `src/Game.h` — game class and state
- `CMakeLists.txt` — build configuration

## 💡 Recommended repo name

I’d suggest naming the GitHub repo:

`neon-drop`

It feels short, memorable, and matches the game’s visual style.

## 🛠️ Optional next upgrades

- add sound effects
- add a start menu
- add multiple difficulty levels
- add a high-score system
- add sprite art and background music

---

Made with C++ and SFML.
