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
	enum Status {
		IDLE,
		RUNNING,
		JUMPING,
		CLIMBING
	};

	// Lower update order to update first
	InputComponent(class Actor* owner);

	virtual void ProcessInput(const uint8_t* keyState) override;
	
	// Getters/setters for private variables
	float GetMaxSpeed() const { return _maxSpeed; }
	int GetRightKey() const { return _rightKey; }
	int GetLeftKey() const { return _leftKey; }
	int GetUpKey() const { return _upKey; }
	int GetDownKey() const { return _downKey; }
	int GetJumpKey() const { return _jumpKey; }
	Status GetStatus() const { return _status; }

	void SetMaxSpeed(float speed) { _maxSpeed = speed; }
	void SetRightKey(int key) { _rightKey = key; }
	void SetLeftKey(int key) { _leftKey = key; }
	void SetUpKey(int key) { _upKey = key; }
	void SetDownKey(int key) { _downKey = key; }
	void SetJumpKey(int key) { _jumpKey = key; }
	void SetIsGrounded(bool isGrounded) { _isGrounded = isGrounded; }
	void SetIsTouchingLadder(bool isTouchingLadder) { _isTouchingLadder = isTouchingLadder; }

private:
	// The maximum forward/angular speeds
	float _maxSpeed;
    
	// Keys for forward/back movement
	int _rightKey;
	int _leftKey;
	int _upKey;
	int _downKey;

	// Key for jumping
	int _jumpKey;

	bool _isGrounded;
	bool _isTouchingLadder;

	const float JUMP_SPEED = 75;
	const float CLIMB_SPEED = 50;

	Status _status;

};
