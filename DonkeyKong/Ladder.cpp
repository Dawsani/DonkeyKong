#include "Ladder.h"

Ladder::Ladder(Game* pGame) : Actor(pGame)
{
	_pSpriteComponent = new SpriteComponent(this);
	_pSpriteComponent->SetTexture(pGame->GetTexture("Assets/Ladder.png"));
	_pRectangleColliderComponent = new RectangleColliderComponent(this);
	_pRectangleColliderComponent->SetSize(Vector2(8, 4));
}
