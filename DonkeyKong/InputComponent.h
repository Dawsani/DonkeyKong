// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent {
public:
	// Lower update order to update first
	InputComponent(class Actor* owner);

	virtual void ProcessInput(const uint8_t* keyState) override;
	
	// Getters/setters for private variables
	float GetMaxSpeed() const { return _maxSpeed; }
	int GetRightKey() const { return _rightKey; }
	int GetLeftKey() const { return _leftKey; }
	int GetJumpKey() const { return _jumpKey; }

	void SetMaxSpeed(float speed) { _maxSpeed = speed; }
	void SetRightKey(int key) { _rightKey = key; }
	void SetLeftKey(int key) { _leftKey = key; }
	void SetJumpKey(int key) { _jumpKey = key; }

private:
	// The maximum forward/angular speeds
	float _maxSpeed;
    
	// Keys for forward/back movement
	int _rightKey;
	int _leftKey;

	// Key for jumping
	int _jumpKey;
};
