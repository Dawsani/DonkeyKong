#include "Barrel.h"
#include "WalkingBlock.h"
#include "Game.h"

Barrel::Barrel(Game* pGame) : Actor(pGame)
{
	_pMoveComponent = new MoveComponent(this, 10);

	_pRectangleColliderComponent = new RectangleColliderComponent(this);
	_pRectangleColliderComponent->SetSize(Vector2(12, 10));

	_pSpriteComponent = new SpriteComponent(this, 0);
	_pSpriteComponent->SetTexture(pGame->GetTexture("Assets/Barrel_0.png"));
}

void Barrel::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	// Barrel rolsl forward, has a a panic attack if no collision
	_pMoveComponent->SetVelocity(Vector2(_direction * SPEED, DOWNWARD_SPEED));

	// Check for collisions
	_isFalling = true;
	for (Actor* actor : GetGame()->GetActors()) {
		if (actor == this) {
			continue;
		}

		RectangleColliderComponent* collider = actor->GetComponent<RectangleColliderComponent>();

		if (collider == nullptr) {
			continue;
		}

		if (_pRectangleColliderComponent->Intersect(*collider)) {
			// Appear on top of the box, if its a walkingblock
			if (dynamic_cast<WalkingBlock*>(actor) != nullptr) {
				_isFalling = false;
				SetPosition(Vector2(GetPosition().x, collider->GetActor()->GetPosition().y - _pRectangleColliderComponent->GetSize().y));
			}
		}
	}

	if (!_isFalling && _wasFalling) {
		// Swap directions
		if (_direction > 0) {
			_direction = -1;
		}
		else {
			_direction = 1;
		}
	}

	_wasFalling = _isFalling;

}
