// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Component.h"
#include "Actor.h"

class SpriteComponent : public Component {
public:
    // (Lower draw order corresponds with further back)
    SpriteComponent(class Actor* pActor, int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(SDL_Renderer* pRenderer);
    virtual void SetTexture(SDL_Texture* pTexture);
    void SetIsFlipped(SDL_RendererFlip rendererFlip) { _rendererFlip = rendererFlip; }

    int GetDrawOrder() const { return _drawOrder; }
    int GetTexHeight() const { return _texHeight; }
    int GetTexWidth() const { return _texWidth; }

protected:
    SDL_Texture* _pTexture;
    int _drawOrder;
    int _texWidth;
    int _texHeight;
    SDL_RendererFlip _rendererFlip;
};
