// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "InputComponent.h"
#include "SpriteComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner) : MoveComponent(owner)
{
	_rightKey = 0;
	_leftKey = 0;
	_jumpKey = 0;
}

void InputComponent::ProcessInput(const uint8_t* keyState) {
	// Calculate forward/backward speed for MoveComponent
    // based on forward/backward custom keys.
	Vector2 velocity = Vector2(0.0f, 0.0f);
	if (keyState[_rightKey]) {
		velocity.x += _maxSpeed;
		// EVIL CODE
		_pActor->GetComponent<SpriteComponent>()->SetIsFlipped(SDL_FLIP_HORIZONTAL);
	}
	if (keyState[_leftKey]) {
		velocity.x -= _maxSpeed;
		_pActor->GetComponent<SpriteComponent>()->SetIsFlipped(SDL_FLIP_NONE);

	}
	if (keyState[_jumpKey]) {
		velocity.y = -40;
	}
	SetVelocity(velocity);
}
