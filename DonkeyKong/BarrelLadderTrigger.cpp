#include "BarrelLadderTrigger.h"

BarrelLadderTrigger::BarrelLadderTrigger(Game* pGame) : Actor(pGame)
{
	_pRectangleColliderComponent = new RectangleColliderComponent(this);
	_pRectangleColliderComponent->SetSize(Vector2(8, 8)); // 8 wide, as wide as a ladder
}
