//
//  Background.cpp
//  Game-mac
//
//  Created by Kathleen Kelly on 4/7/23.
//  Copyright © 2023 Sanjay Madhav. All rights reserved.
//

#include "Background.h"
#include "Game.h"
#include "ScrollingSpriteComponent.h"

Background::Background(Game* pGame) : Actor(pGame) {
    Vector2 windowSize = pGame->GetWindowSize();
    
    // Create a background
    SpriteComponent* bg = new SpriteComponent(this);
	bg->SetTexture(pGame->GetTexture("Assets/Level.png"));
}
