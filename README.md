# MiniEngine — C++17 / SDL2

A compact 2D arcade shooter based on a learning project, designed to demonstrate a clean SDL2 game loop, object-oriented design, sprite-sheet animation, input, AABB collision, RAII, and resource management.

## Features
- Player movement with **Arrow keys** or **WASD**
- Shoot with **Space** (one shot per press)
- Animated enemies that bounce at screen edges
- Two waves, scoring, three lives, win/game-over states
- **R** to restart, **Esc** to quit
- Optional developer controls: **N** adds an enemy, **M** removes the last enemy
- Window title displays score, lives, wave, and end-state instructions

## Build
Requires a C++17 compiler, CMake >= 3.16, and **SDL2 development libraries**.

### Windows (vcpkg + Visual Studio toolchain)
```powershell
vcpkg install sdl2:x64-windows
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build build --config Release
```
Run `build/Release/MiniEngine.exe` from a terminal (the build copies `assets/` next to the executable).

### Linux
```bash
sudo apt install libsdl2-dev cmake g++
cmake -S . -B build
cmake --build build
./build/MiniEngine
```

## Architecture
- `Engine`: owns the SDL window/renderer, controls state, wave spawning, bullets, collisions, and game loop.
- `GameObject`: abstract base class with virtual `update` and `render`.
- `Player`: frame-independent movement and input.
- `Enemy`: sprite-sheet animation and horizontal movement.
- `TextureManager`: caches textures and destroys them during cleanup.
- `Collision.h`: AABB intersection helper.

`std::unique_ptr` owns Player and Enemy objects. SDL textures are owned by `TextureManager`, not by individual game objects. Bullets are lightweight value objects stored in a vector.

## Limitations / known issues
- The gameplay is intentionally small: two waves, no audio, no text rendering library.
- The game status is displayed in the **window title**, not as an in-game HUD.
- Enemy movement is individual rather than a synchronized Space Invaders fleet.
- Assets are original placeholder BMP images included in this repository.
- Builds require SDL2 to be installed separately; this repo does not bundle SDL2.

## Screenshots and verification
Add a real screenshot or short GIF after running the game locally. Do not fabricate screenshots.

## Learning note
This is a consolidated reference implementation. Before using it as portfolio evidence, read each class, build it locally, test all controls, and record the changes you personally make in genuine Git commits.
