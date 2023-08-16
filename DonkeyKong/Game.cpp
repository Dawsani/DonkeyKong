// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include <algorithm>
#include "Background.h"
#include "WalkingBlock.h"
#include "Player.h"
#include "Barrel.h"
#include "Ladder.h"
#include "DonkeyKong.h"
#include <time.h>
#include <iostream>
#include <cstdlib>

Game::Game()
:_pWindow(nullptr)
,_pRenderer(nullptr)
,_isRunning(true) {
    
}

bool Game::Initialize() {
    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    
    // Create generic window.
    _windowSize.x = 224;
    _windowSize.y = 256;
    _pWindow = SDL_CreateWindow("Window Title", 100, 100, _windowSize.x, _windowSize.y, 0);
    if (!_pWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    
    // Create window renderer.
    _pRenderer = SDL_CreateRenderer(_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_pRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }
    
    // Make sure SDL can initialize images to be used.
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    // Game-specific data loading.
    _loadData();

    // Initialize tick count.
    _ticksCount = SDL_GetTicks();

    srand(time(0));
    
    return true;
}

void Game::RunLoop() {
    // Main game loop.
    while (_isRunning) {
        _processInput();
        _updateGame();
        _generateOutput();
    }
}

// Get any input from the keyboard/mouse.
void Game::_processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            // X-button on window.
            case SDL_QUIT:
                _isRunning = false;
                break;
        }
    }
    
    // Get full keyboard state in an array.
    const Uint8* state = SDL_GetKeyboardState(NULL);
    
    // Escape key exits game.
    if (state[SDL_SCANCODE_ESCAPE]) {
        _isRunning = false;
    }

    // Process any game-specific input.
    for (int i = 0; i < _vecActors.size(); i++) {
        _vecActors.at(i)->ProcessInput(state);
    }
}

// Update every actor/component in the game to any new
// transforms (position, rotation, scale).
void Game::_updateGame() {
    // Compute delta time
    // Wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), _ticksCount + 16))
        ;

    // Cap deltaTime to help with smoothness.
    float deltaTime = (SDL_GetTicks() - _ticksCount) / 1000.0f;
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    _ticksCount = SDL_GetTicks();

    // Update all actors in the game.
    //for (Actor* actor : _vecActors) { // Caused probelms when an actor created a new actor
    for (unsigned int i = 0; i < _vecActors.size(); i++) {
        _vecActors.at(i)->Update(deltaTime);
    }
    
    // Delete any dead actors.
    // Add any dead actors to a temp vector
    std::vector<Actor*> deadActors;
    for (auto actor : _vecActors) {
        if (actor->GetState() == Actor::EDead) {
            deadActors.push_back(actor);
        }
    }

    // Delete dead actors (which removes them from _actors)
    for (auto actor : deadActors) {
        delete actor;
    }

    _timePassed += deltaTime;

    /*
    if (_timePassed >= 0.5) {
        _timePassed -= 0.5;

        int randNum = rand();
        randNum = randNum * randNum;

        Vector2 startPos(randNum % (int) _windowSize.x, (randNum % (int ) 2) - 1);
        std::cout << randNum << std::endl;

        // Set position to random position

        Asteroid* asteroid = new Asteroid(this);
        asteroid->SetPosition(startPos);
    }*/
}

// Render output of this frame.
void Game::_generateOutput() {
    // Clear the screen.
    SDL_SetRenderDrawColor(_pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(_pRenderer);
    
    // Draw all sprite components
    for (auto actor : _vecActors) {
        actor->Draw(_pRenderer);
    }

    // Present the screen.
    SDL_RenderPresent(_pRenderer);
}

void Game::_loadData() {
    // Background
    //Background* background = new Background(this);

    // Need a player that can walk along walkways and jump
    Player* player = new Player(this);

    // Need platforms for the player to walk on
    // Straight platforms
    for (int i = 0; i < 6; i++) {
        WalkingBlock* walkingBlock = new WalkingBlock(this);
        walkingBlock->SetPosition(Vector2(i * walkingBlock->GetSize().x, GetWindowSize().y - walkingBlock->GetSize().y));
    }

    // First incline
    for (int i = 0; i < 8; i++) {
        WalkingBlock* walkingBlock = new WalkingBlock(this);
        walkingBlock->SetPosition(Vector2((i+6) * walkingBlock->GetSize().x, GetWindowSize().y - walkingBlock->GetSize().y - i));
    }

    // Second incline
    for (int i = 0; i < 13; i++) {
        WalkingBlock* walkingBlock = new WalkingBlock(this);
        walkingBlock->SetPosition(Vector2(i*walkingBlock->GetSize().x, GetWindowSize().y - 40 - walkingBlock->GetSize().y + i));
    }

    // Third incline
    for (int i = 0; i < 14; i++) {
        WalkingBlock* walkingBlock = new WalkingBlock(this);
        walkingBlock->SetPosition(Vector2(GetWindowSize().x - walkingBlock->GetSize().x * i, GetWindowSize().y - 74 - walkingBlock->GetSize().y + i));
    }

    // Test Barrel
    Barrel* barrel = new Barrel(this);
    barrel->SetPosition(Vector2(100, 100));

    // Ladder
    for (int i = 0; i < 2; i++) {
        Ladder* ladder = new Ladder(this);
        ladder->SetPosition(Vector2(80, GetWindowSize().y - 12 - i * 4));
    }

    // Second ladder
    for (int i = 0; i < 4; i++) {
        Ladder* ladder = new Ladder(this);
        ladder->SetPosition(Vector2(GetWindowSize().x - 40, GetWindowSize().y - 17 - i * 4));
    }

    // DK
    DonkeyKong* dk = new DonkeyKong(this);

}

// Cleanup of any actors and textures.
void Game::_unloadData() {
    // Delete actors
    // Because ~Actor calls RemoveActor, have to use a different style loop
    while (!_vecActors.empty()) {
        delete _vecActors.back();
    }

    // Destroy textures
    for (auto i : _mapTextures) {
        SDL_DestroyTexture(i.second);
    }
    _mapTextures.clear();
}

// Find a texture in the texture map.
SDL_Texture* Game::GetTexture(const std::string& fileName) {
    SDL_Texture* tex = nullptr;
    
    // Is the texture already in the map?
    auto iter = _mapTextures.find(fileName);
    if (iter != _mapTextures.end()) {
        tex = iter->second;
    }
    else {
        // Load from file
        SDL_Surface* surf = IMG_Load(fileName.c_str());
        if (!surf) {
            SDL_Log("Failed to load texture file %s", fileName.c_str());
            return nullptr;
        }

        // Create texture from surface
        tex = SDL_CreateTextureFromSurface(_pRenderer, surf);
        SDL_FreeSurface(surf);
        if (!tex) {
            SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
            return nullptr;
        }

        // Add it to the map.
        _mapTextures.emplace(fileName.c_str(), tex);
    }
    return tex;
}

std::vector<class Actor*> Game::GetActors()
{
    return _vecActors;
}

// Cleanup game and SDL.
void Game::Shutdown() {
    _unloadData();
    IMG_Quit();
    SDL_DestroyRenderer(_pRenderer);
    SDL_DestroyWindow(_pWindow);
    SDL_Quit();
}

// Add an Actor to the game list.
void Game::AddActor(Actor* actor) {
    _vecActors.push_back(actor);
}

// Remove an actor from the game list.
void Game::RemoveActor(Actor* actor) {

    // Is it in actors?
    auto iter = std::find(_vecActors.begin(), _vecActors.end(), actor);
    if (iter != _vecActors.end()) {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, _vecActors.end() - 1);
        _vecActors.pop_back();
    }
}