// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Component.h"
#include "Actor.h"

Component::Component(Actor* pActor, int updateOrder):_pActor(pActor),_updateOrder(updateOrder) {
    // Add to actor's vector of components
    _pActor->AddComponent(this);
}

Component::~Component() {
    _pActor->RemoveComponent(this);
}

void Component::Update(float deltaTime) {

}

void Component::ProcessInput(const uint8_t* keyState) {
    
}
