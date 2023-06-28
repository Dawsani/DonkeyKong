// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Component.h"
#include <vector>
#include "Math.h"

class MoveComponent : public Component {
public:
	// Lower update order to update first
	MoveComponent(class Actor* pActor, int updateOrder = 10);

	virtual void Update(float deltaTime) override;
	
	Vector2 GetVelocity() const { return _velocity; }
	void SetVelocity(Vector2 velocity) { _velocity = velocity; }
    
private:    
	// Controls forward movement (units/second)
	Vector2 _velocity;
};
