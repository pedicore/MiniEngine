#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "InputState.h"
#include "TextureManager.h"

class Engine {
    struct Bullet { float x = 0, y = 0; SDL_Rect rect{}; };
    enum class State { Playing, Won, Lost };
    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 600;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool running = false;
    Uint32 lastTime = 0;
    InputState input{};
    TextureManager textureManager;
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<Bullet> bullets;
    State state = State::Playing;
    int score = 0;
    int lives = 3;
    int wave = 1;
    float shootCooldown = 0;
    float invulnerability = 0;
    void spawnEnemy(int x, int y, float animationSpeed);
    void resetGame();
    void startWave();
    void shoot();
    void updateTitle() const;
    void clean();
public:
    Engine() = default;
    ~Engine();
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    bool init();
    void handleEvents();
    void update();
    void render();
    bool isRunning() const { return running; }
};
