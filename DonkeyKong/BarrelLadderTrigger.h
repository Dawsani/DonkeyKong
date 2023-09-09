#pragma once
#include "Actor.h"
#include "RectangleColliderComponent.h"
#include "Ladder.h"

class BarrelLadderTrigger : public Actor
{
public:
	BarrelLadderTrigger(Game* pGame);
	void SetAssociatedLadder(Ladder* pLadder) { _pAssociatedLadder = pLadder; }
private:
	RectangleColliderComponent* _pRectangleColliderComponent;
	Ladder* _pAssociatedLadder;
};

