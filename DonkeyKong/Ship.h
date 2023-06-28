#pragma once

#include "Actor.h"

class Ship : public Actor
{
public:
	Ship(Game* pGame);

	virtual void ProcessInput(const uint8_t* keyState) override;
	virtual void Update(float deltaTime) override;

private:
	float _laserCooldown = 0.50f;
};

