#pragma once
#include "Actor.h"
#include "Game.h"

#include "RectangleColliderComponent.h"
#include "SpriteComponent.h"

class Ladder : public Actor
{
public:
	Ladder(Game* pGame);
private:
	RectangleColliderComponent* _pRectangleColliderComponent;
	SpriteComponent* _pSpriteComponent;
};

