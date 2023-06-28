// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
//#include "SDL/SDL_image.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Actor.h"

class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    Vector2 GetWindowSize() { return _windowSize; }
    
    SDL_Texture* GetTexture(const std::string& fileName);

    std::vector<class Actor*> GetActors();

    
private:
    void _processInput();
    void _updateGame();
    void _generateOutput();
    void _loadData();
    void _unloadData();
    
    // Map of textures loaded
    std::unordered_map<std::string, SDL_Texture*> _mapTextures;

    // All the actors in the game
    std::vector<class Actor*> _vecActors;
    
    SDL_Window* _pWindow;
    SDL_Renderer* _pRenderer;
    Uint32 _ticksCount;
    bool _isRunning;
    Vector2 _windowSize;

    float _timePassed = 0;
};
