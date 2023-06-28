// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include "Math.h"
#include "SDL_image.h"
#include <typeinfo>

class Actor {
public:
    enum State {
        EActive,
        EPaused,
        EDead
    };

    Actor(class Game* game);
    virtual ~Actor();

    // ProcessInput / Update / Draw functions called from Game
    virtual void ProcessInput(const uint8_t* keyState);
    virtual void Update(float deltaTime);
    virtual void Draw(SDL_Renderer* pRenderer);
    
    // Updates all the components attached to the actor (not overridable)
    void UpdateComponents(float deltaTime);
    
    // Any actor-specific update code (overridable)
    void DrawComponent(SDL_Renderer* pRenderer);

    // Getters/setters
    const Vector2& GetPosition() const { return _position; }
    void SetPosition(const Vector2& pos) { _position = pos; }
    float GetScale() const { return _scale; }
    void SetScale(float scale) { _scale = scale; }
    float GetRotation() const { return _rotation; }
    void SetRotation(float rotation) { _rotation = rotation; }

    Vector2 GetForward() const { return Vector2(Math::Cos(_rotation), -Math::Sin(_rotation)); }
    
    State GetState() const { return _state; }
    void SetState(State state) { _state = state; }

    class Game* GetGame() { return _pGame; }

    // Add/remove components
    void AddComponent(class Component* pComponent);
    void RemoveComponent(class Component* pComponent);

    // Add/remove sprites
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);

    // Get component
    template <class T>
    T* GetComponent() {
        for (Component* component : _vecComponents) {
            if (dynamic_cast<T*>(component) != nullptr) {
                return (T*) component;
            }
        }

        return NULL;
    }

    template <typename T>
    bool GetTrue() { return true; }
    
private:
    // Actor's state
    State _state;

    // Transform
    Vector2 _position;
    float _scale;
    float _rotation;

    std::vector<class Component*> _vecComponents;
    class Game* _pGame;
    
    // All the sprite components drawn
    std::vector<class SpriteComponent*> _vecSprites;
};
