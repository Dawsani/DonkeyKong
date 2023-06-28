#pragma once
#include "Component.h"
#include "Math.h"

class RectangleColliderComponent : public Component
{
public:
	RectangleColliderComponent(class Actor* pActor);

	void SetSize(Vector2 _size) { this->_size = _size; };
	const Vector2 GetSize() { return _size; };

	bool Intersect(const RectangleColliderComponent& other);
private:
	Vector2 _size;
};

