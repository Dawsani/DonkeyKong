// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Component.h"
#include "Math.h"

class CircleComponent : public Component {
public:
	CircleComponent(class Actor* pActor);
	
	void SetRadius(float radius) { _radius = radius; }
	float GetRadius() const;
	
	const Vector2& GetCenter() const;
    
    bool Intersect(const CircleComponent& other);
    
private:
	float _radius;
};
