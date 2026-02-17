# WallBall

A simple ball-bouncing game built with C and [Raylib](https://www.raylib.com/).

## How to Play

| Key | Action |
|-----|--------|
| Space | Start game |
| ← → | Move the bar |
| Esc | Quit |

Hit the ball with the bar to score +100 points. If you miss, it's game over.

## Build & Run

### Prerequisites

- CMake (3.14+)
- C compiler (gcc, clang, etc.)
- X11 dev libraries (Linux)

**Linux (Ubuntu/Debian):**

```bash
sudo apt install cmake build-essential libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl-dev
```

**macOS:**

```bash
brew install cmake
```

**Windows (MSYS2):**

```bash
pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-gcc
```

### Build & Run

```bash
cmake -B build
cmake --build build
./build/WallBall
```

Raylib is automatically downloaded during the first build.

## Tested On

- Windows 11 (WSL2 Ubuntu)

Not tested on other platforms.
