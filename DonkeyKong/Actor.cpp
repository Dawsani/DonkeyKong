// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include "SpriteComponent.h"
#include "RectangleColliderComponent.h"
#include <algorithm>

Actor::Actor(Game* pGame)
    :_state(EActive)
    , _position(Vector2::Zero)
    , _scale(1.0f)
    , _rotation(0.0f)
    , _pGame(pGame) {

    // Add me to the game
    _pGame->AddActor(this);
}

Actor::~Actor() {
    // Remove me from the game
    _pGame->RemoveActor(this);
    
    // Need to delete components
    // Because ~Component calls RemoveComponent, need a different style loop
    while (!_vecComponents.empty()) {
        delete _vecComponents.back();
    }
    
    while (!_vecSprites.empty()) {
        delete _vecSprites.back();
    }
}

// Update this Actor.
void Actor::ProcessInput(const uint8_t* keyState) {
    if (_state == EActive) {
        for (auto comp : _vecComponents) {
            comp->ProcessInput(keyState);
        }
    }
}

void Actor::Update(float deltaTime) {
    if (_state == EActive) {
        UpdateComponents(deltaTime);
    }
}

void Actor::Draw(SDL_Renderer *pRenderer) {
    if (_state == EActive) {
        DrawComponent(pRenderer);
    }
}

void Actor::UpdateComponents(float deltaTime) {
    for (auto comp : _vecComponents) {
        comp->Update(deltaTime);
    }
}

void Actor::DrawComponent(SDL_Renderer *pRenderer) {
    for (SpriteComponent* spr : _vecSprites) {
        spr->Draw(pRenderer);
    }
}

void Actor::AddComponent(Component* pComponent) {
    // Find the insertion point in the sorted vector
    // (The first element with a order higher than me)
    int myOrder = pComponent->GetUpdateOrder();
    auto iter = _vecComponents.begin();
    for (; iter != _vecComponents.end(); ++iter) {
        if (myOrder < (*iter)->GetUpdateOrder()) {
            break;
        }
    }

    // Inserts element before position of iterator
    _vecComponents.insert(iter, pComponent);
}

void Actor::RemoveComponent(Component* component) {
    auto iter = std::find(_vecComponents.begin(), _vecComponents.end(), component);
    if (iter != _vecComponents.end()) {
        _vecComponents.erase(iter);
    }
}

// Add a SpriteComponent to the sprite list.
void Actor::AddSprite(SpriteComponent* pSprite) {
    // Find the insertion point in the sorted vector
    // (The first element with a higher draw order than me)
    int myDrawOrder = pSprite->GetDrawOrder();
    auto iter = _vecSprites.begin();
    for (; iter != _vecSprites.end(); ++iter) {
        if (myDrawOrder < (*iter)->GetDrawOrder()) {
            break;
        }
    }

    // Inserts element before position of iterator
    _vecSprites.insert(iter, pSprite);
}

// Remove a sprite from the game.
void Actor::RemoveSprite(SpriteComponent* sprite) {
    auto iter = std::find(_vecSprites.begin(), _vecSprites.end(), sprite);
    _vecSprites.erase(iter);
}

