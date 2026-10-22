#include "Engine.h"
#include "Collision.h"
#include <algorithm>
#include <iostream>
#include <string>

Engine::~Engine() { clean(); }

bool Engine::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { std::cerr << "SDL_Init: " << SDL_GetError() << '\n'; return false; }
    window = SDL_CreateWindow("MiniEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) { std::cerr << SDL_GetError() << '\n'; clean(); return false; }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer) { std::cerr << SDL_GetError() << '\n'; clean(); return false; }
    if (!textureManager.load(renderer, "player", "assets/player.bmp") ||
        !textureManager.load(renderer, "enemy", "assets/enemy_sheet.bmp")) {
        clean(); return false;
    }
    resetGame();
    running = true;
    lastTime = SDL_GetTicks();
    return true;
}

void Engine::spawnEnemy(int x, int y, float animationSpeed) {
    auto* texture = textureManager.get("enemy");
    if (texture) enemies.push_back(std::make_unique<Enemy>(x, y, texture, animationSpeed));
}

void Engine::startWave() {
    enemies.clear();
    bullets.clear();
    const int cols = 6;
    const int rows = 2 + (wave > 1 ? 1 : 0);
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            spawnEnemy(60 + c * 115, 60 + r * 65, 0.10f + 0.025f * r);
    updateTitle();
}

void Engine::resetGame() {
    player = std::make_unique<Player>(WINDOW_WIDTH / 2.0f - 16, WINDOW_HEIGHT - 75.0f,
                                      320.0f, textureManager.get("player"));
    state = State::Playing;
    score = 0;
    lives = 3;
    wave = 1;
    shootCooldown = 0;
    invulnerability = 0;
    startWave();
}

void Engine::shoot() {
    if (!player || shootCooldown > 0 || state != State::Playing) return;
    const auto& p = player->getRect();
    Bullet b;
    b.x = static_cast<float>(p.x + p.w / 2 - 3);
    b.y = static_cast<float>(p.y - 14);
    b.rect = {static_cast<int>(b.x), static_cast<int>(b.y), 6, 14};
    bullets.push_back(b);
    shootCooldown = 0.22f;
}

void Engine::handleEvents() {
    SDL_Event event{};
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) running = false;
        if (event.type != SDL_KEYDOWN || event.key.repeat != 0) continue;
        if (event.key.keysym.sym == SDLK_ESCAPE) running = false;
        if (event.key.keysym.sym == SDLK_r) resetGame();
        if (state != State::Playing) continue;
        if (event.key.keysym.sym == SDLK_SPACE) shoot();
        // Optional debugging controls retained from the learning project.
        if (event.key.keysym.sym == SDLK_n) spawnEnemy(80, 150, 0.15f);
        if (event.key.keysym.sym == SDLK_m && !enemies.empty()) enemies.pop_back();
    }
}

void Engine::updateTitle() const {
    if (!window) return;
    std::string title = "MiniEngine | Score: " + std::to_string(score) +
                        " | Lives: " + std::to_string(lives) +
                        " | Wave: " + std::to_string(wave);
    if (state == State::Won) title += " | YOU WIN! Press R to restart";
    if (state == State::Lost) title += " | GAME OVER! Press R to restart";
    SDL_SetWindowTitle(window, title.c_str());
}

void Engine::update() {
    const Uint32 now = SDL_GetTicks();
    const float dt = std::min((now - lastTime) / 1000.0f, 0.05f);
    lastTime = now;
    if (state != State::Playing) return;
    const Uint8* keys = SDL_GetKeyboardState(nullptr);
    input.moveRight = keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D];
    input.moveLeft = keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A];
    input.moveUp = keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W];
    input.moveDown = keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S];
    player->setInput(input, WINDOW_WIDTH, WINDOW_HEIGHT);
    player->update(dt);
    shootCooldown = std::max(0.0f, shootCooldown - dt);
    invulnerability = std::max(0.0f, invulnerability - dt);
    for (auto& e : enemies) { e->update(dt); e->keepInBounds(WINDOW_WIDTH); }
    for (auto& b : bullets) {
        b.y -= 480.0f * dt;
        b.rect.y = static_cast<int>(b.y);
    }
    // Erase in reverse to avoid invalidating indices when bullets hit enemies.
    for (std::size_t bi = bullets.size(); bi-- > 0;) {
        bool removeBullet = bullets[bi].rect.y + bullets[bi].rect.h < 0;
        if (!removeBullet) {
            for (std::size_t ei = enemies.size(); ei-- > 0;) {
                if (checkCollision(bullets[bi].rect, enemies[ei]->getRect())) {
                    enemies.erase(enemies.begin() + static_cast<std::ptrdiff_t>(ei));
                    score += 10;
                    removeBullet = true;
                    break;
                }
            }
        }
        if (removeBullet) bullets.erase(bullets.begin() + static_cast<std::ptrdiff_t>(bi));
    }
    if (invulnerability <= 0) {
        for (const auto& e : enemies) {
            if (checkCollision(player->getRect(), e->getRect())) {
                --lives;
                invulnerability = 1.5f;
                if (lives <= 0) state = State::Lost;
                break;
            }
        }
    }
    for (const auto& e : enemies) {
        if (e->getRect().y + e->getRect().h >= WINDOW_HEIGHT - 15) {
            state = State::Lost;
            break;
        }
    }
    if (state == State::Playing && enemies.empty()) {
        if (wave == 2) state = State::Won;
        else { ++wave; startWave(); }
    }
    updateTitle();
}

void Engine::render() {
    if (!renderer) return;
    SDL_SetRenderDrawColor(renderer, 15, 21, 39, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 50, 60, 90, 255);
    SDL_Rect ground{0, WINDOW_HEIGHT - 15, WINDOW_WIDTH, 15};
    SDL_RenderFillRect(renderer, &ground);
    if (player && (invulnerability <= 0 || (SDL_GetTicks() / 120) % 2 == 0)) player->render(renderer);
    for (const auto& e : enemies) e->render(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 220, 95, 255);
    for (const auto& b : bullets) SDL_RenderFillRect(renderer, &b.rect);
    if (state != State::Playing) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, state == State::Won ? 40 : 150,
                               state == State::Won ? 160 : 30, 50, 130);
        SDL_Rect overlay{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_RenderFillRect(renderer, &overlay);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(1);
}

void Engine::clean() {
    bullets.clear();
    enemies.clear();
    player.reset();
    textureManager.clear();
    if (renderer) { SDL_DestroyRenderer(renderer); renderer = nullptr; }
    if (window) { SDL_DestroyWindow(window); window = nullptr; }
    SDL_Quit();
    running = false;
}
