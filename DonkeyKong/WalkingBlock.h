#pragma once
#include "Actor.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "RectangleColliderComponent.h"

class WalkingBlock : public Actor
{
public:
	WalkingBlock(Game* pGame);
	void SetPosition(Vector2 pos) { // TRUE EVIL RIGHT HERE, DON'T KNOW WHY IT'S NOT LETTING BE NORMAL
		Actor::SetPosition(pos);
	}
	Vector2 GetSize() { return _pRectangleColliderComponent->GetSize(); };

private:
	SpriteComponent* _pSpriteComponent;
	RectangleColliderComponent* _pRectangleColliderComponent;
	
};

