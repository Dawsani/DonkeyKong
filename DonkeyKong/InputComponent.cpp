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
#include "Game.h"
#include <iostream>

InputComponent::InputComponent(class Actor* owner) : MoveComponent(owner)
{
	_rightKey = 0;
	_leftKey = 0;
	_jumpKey = 0;
}

void InputComponent::ProcessInput(const uint8_t* keyState) {
	// Calculate forward/backward speed for MoveComponent
    // based on forward/backward custom keys.

	// Can't control if not on ground
	if (!_isGrounded) {
		return;
	}

	Vector2 velocity = GetVelocity();
	_status = IDLE;
	if (keyState[_rightKey]) {
		velocity.x = _maxSpeed;
		// EVIL CODE
		_pActor->GetComponent<SpriteComponent>()->SetIsFlipped(SDL_FLIP_HORIZONTAL);
		_status = RUNNING;
	}
	if (keyState[_leftKey]) {
		velocity.x = -_maxSpeed;
		_pActor->GetComponent<SpriteComponent>()->SetIsFlipped(SDL_FLIP_NONE);
		_status = RUNNING;
	}
	if (keyState[_jumpKey]) {
		velocity.y = -JUMP_SPEED;
		_pActor->GetComponent<SpriteComponent>()->SetTexture(_pActor->GetGame()->GetTexture("Assets/Jumpman_Jumping_0.png"));
		_status = JUMPING;
	}
	SetVelocity(velocity);
}
