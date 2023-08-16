#pragma once
#include "Actor.h"
#include "SpriteComponent.h"

class DonkeyKong : public Actor
{
public:
	DonkeyKong(Game* pGame);
	virtual void Update(float deltaTime) override;
private:
	SpriteComponent* _pSpriteComponent;
	const float ATTACK_TIME = 2.0f;
	float _timer = ATTACK_TIME;
};

