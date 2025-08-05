# Pacman Clone in C (SDL2)

Welcome to a complete, retro-style Pacman clone built in **C** using the **SDL2** library suite.
This project faithfully recreates the classic arcade experience, including ghost AI behavior, power pellets, scores, menus, and much more.

![screenshot](assets/images/menu_title.png)

---

## 🎮 Features

* Classic Pacman gameplay
* Ghost AI: Blinky, Pinky, Inky, Clyde (with original behavior logic)
* Scared ghost mode with visual flash warning
* Dot/orb collecting and scoring system
* Extra lives and reward items
* Sound effects and music (SDL\_mixer)
* Custom font UI (SDL\_ttf)
* Scoreboard with persistent high scores
* User input name entry
* Help menu, pause mode, and ranking screen

---

## 🚀 Getting Started

### 📦 Dependencies

Make sure to have the following libraries installed:

* `SDL2`
* `SDL2_ttf`
* `SDL2_image`
* `SDL2_mixer`

On Ubuntu/Debian-based systems:

```bash
sudo apt install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev
```

### 🔨 Build

Use the included Makefile:

```bash
make
```

This will compile the game into `bin/pacman`.

### ▶️ Run

```bash
./bin/pacman
```

---

## 🕹️ Controls

| Key          | Action          |
| ------------ | --------------- |
| `Arrow Keys` | Move Pacman     |
| `S`          | Start Game      |
| `H`          | Help Menu       |
| `R`          | Show Scoreboard |
| `ESC`        | Pause/Quit      |

---

## 📂 Project Structure

```
Pacman/
├── assets/             # Images, sounds, font
├── src/                # C source files
├── include/            # Header files
├── bin/                # Compiled binary
├── scores.bin          # Saved high scores
├── Makefile            # Build script
└── README.md           # Project documentation
```

---

## 📝 High Score System

* Top 10 scores saved to `scores.bin`
* Players enter their name after each game
* Scores persist between runs

---

## 🖼️ Assets

* Font: [Press Start 2P](https://fonts.google.com/specimen/Press+Start+2P)
* Sprites and sounds: Inspired by original Pacman, created manually or adapted

---

## 🧠 Ghost AI Behavior

Each ghost uses a different strategy:

* **Blinky**: Follows Pacman directly
* **Pinky**: Targets 4 tiles ahead of Pacman's direction
* **Inky**: Double-vector chase using Blinky and Pacman's position
* **Clyde**: Chases Pacman but retreats when close

---

## 📜 License

This project is open-source under the MIT License.

---

## 👨‍💻 Author

**Facundo Gauna**
Feel free to fork, contribute, or reach out!

---

## ✅ TODO / Suggestions

* Add music support
* Add more reward animations
* Package as `.AppImage` or `.exe`
* Add level editor or multiple map support

---

Enjoy the classic experience!
