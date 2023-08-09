#include "Barrel.h"
#include "Game.h"

Barrel::Barrel(Game* pGame) : Actor(pGame)
{
	_pMoveComponent = new MoveComponent(this, 10);

	_pRectangleColliderComponent = new RectangleColliderComponent(this);
	_pRectangleColliderComponent->SetSize(Vector2(12, 10));

	_pSpriteComponent = new SpriteComponent(this);
	_pSpriteComponent->SetTexture(pGame->GetTexture("Assets/Barrel_0.png"));
}

void Barrel::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	// Barrel rolsl forward, has a a panic attack if no collision
	_pMoveComponent->SetVelocity(Vector2(_forwardSpeed, _downwardSpeed));

	// Check for collisions
	for (Actor* actor : GetGame()->GetActors()) {
		if (actor == this) {
			continue;
		}

		RectangleColliderComponent* collider = actor->GetComponent<RectangleColliderComponent>();

		if (collider == nullptr) {
			continue;
		}

		if (_pRectangleColliderComponent->Intersect(*collider)) {
			// Appear on top of the box
			_pMoveComponent->SetVelocity(Vector2(0.0, 0.0));
			SetPosition(Vector2(GetPosition().x, collider->GetActor()->GetPosition().y - _pRectangleColliderComponent->GetSize().y));
		}
	}
}
