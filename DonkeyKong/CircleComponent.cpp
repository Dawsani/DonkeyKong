// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(class Actor* pActor) : Component(pActor), _radius(0.0f) {
	
}

const Vector2& CircleComponent::GetCenter() const {
	return _pActor->GetPosition();
}

float CircleComponent::GetRadius() const {
	return _pActor->GetScale() * _radius;
}

// TODO: Implement this method
bool CircleComponent::Intersect(const CircleComponent& other) {
	// Calculate distance squared between this CircleComponet
    // and other.
	Vector2 position = _pActor->GetPosition();
	Vector2 otherPosition = other._pActor->GetPosition();
	float xDiff = position.x - otherPosition.x;
	float yDiff = position.y - otherPosition.y;
	float distance = Math::Sqrt( (xDiff * xDiff) + (yDiff * yDiff) );

	// Calculate the sum of the radii squared.
	float radiiSum = _radius + other._radius;
	
    // Return whether or not the distance squared is less
    // than the radii squared - if it is, Intersect of these
    // two CircleComponets is true.
	return distance <= radiiSum;

	// Why would we use ditance squared vs radii sum squared instead of distance vs radii sum?
}
