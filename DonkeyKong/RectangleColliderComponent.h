#pragma once
#include "Component.h"
#include "Math.h"

class RectangleColliderComponent : public Component
{
public:
	RectangleColliderComponent(class Actor* pActor);

	virtual void Update(float deltaTime);

	void SetSize(Vector2 _size) { this->_size = _size; };
	const Vector2 GetSize() { return _size; };

	bool Intersect(const RectangleColliderComponent& other);
	void OnCollision(const RectangleColliderComponent& collision);
private:
	Vector2 _size;
};

