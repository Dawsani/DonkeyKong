#include "RectangleColliderComponent.h"
#include "Actor.h"

RectangleColliderComponent::RectangleColliderComponent(Actor* pActor) : Component(pActor)
{
	_size = Vector2(0.0f, 0.0f);
}

void RectangleColliderComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);

}

bool RectangleColliderComponent::Intersect(const RectangleColliderComponent& other)
{
	Vector2 position = _pActor->GetPosition();

	Vector2 otherPosition = other._pActor->GetPosition();

	// Up aand down
	if (position.x < otherPosition.x + other._size.x &&
		position.x + _size.x > otherPosition.x &&
		position.y < otherPosition.y + other._size.y &&
		position.y + _size.y > otherPosition.y) {
		return true;
	}

	return false;
}
