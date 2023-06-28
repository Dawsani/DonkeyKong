// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Actor* pActor, int drawOrder)
    :Component(pActor)
    ,_pTexture(nullptr)
    ,_drawOrder(drawOrder)
    ,_texWidth(0)
    ,_texHeight(0) {
    _pActor->AddSprite(this);
    _rendererFlip = SDL_FLIP_NONE;
}

SpriteComponent::~SpriteComponent() {
    _pActor->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* pRenderer) {
    if (_pTexture) {
        SDL_Rect r;
        // Scale the width/height by owner's scale
        r.w = static_cast<int>(_texWidth * _pActor->GetScale());
        r.h = static_cast<int>(_texHeight * _pActor->GetScale());
        
        // Center the rectangle around the position of the owner
        r.x = static_cast<int>(_pActor->GetPosition().x );
        r.y = static_cast<int>(_pActor->GetPosition().y );

        // Draw (have to convert angle from radians to degrees, and clockwise to counter)
        SDL_RenderCopyEx(pRenderer,
            _pTexture,
            nullptr,
            &r,
            -Math::ToDegrees(_pActor->GetRotation()),
            nullptr,
            _rendererFlip);
    }
}

void SpriteComponent::SetTexture(SDL_Texture* pTexture) {
    _pTexture = pTexture;
    
    // Set width/height
    SDL_QueryTexture(_pTexture, nullptr, nullptr, &_texWidth, &_texHeight);
}
