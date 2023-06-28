#include "WalkingBlock.h"

WalkingBlock::WalkingBlock(Game* pGame) : Actor(pGame)
{
	_pSpriteComponent = new SpriteComponent(this);
	_pSpriteComponent->SetTexture(pGame->GetTexture("Assets/Block.png"));
	_pRectangleColliderComponent = new RectangleColliderComponent(this);
	_pRectangleColliderComponent->SetSize(Vector2(16, 8));
}
