// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* pActor, int updateOrder) : Component(pActor, updateOrder)
{
    _velocity = Vector2(0.0, 0.0);
}

void MoveComponent::Update(float deltaTime) {	
    // Get the actor's current position and add to it.
	Vector2 pos = _pActor->GetPosition();
    pos = Vector2(pos.x + _velocity.x * deltaTime, pos.y + _velocity.y * deltaTime);
        
    _pActor->SetPosition(pos);
}
