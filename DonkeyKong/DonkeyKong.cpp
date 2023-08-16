#include "DonkeyKong.h"
#include "Game.h"
#include "Barrel.h"

DonkeyKong::DonkeyKong(Game* pGame) : Actor(pGame)
{
	_pSpriteComponent = new SpriteComponent(this);
	_pSpriteComponent->SetTexture(pGame->GetTexture("Assets/DonkeyKong_Idle.png"));
}

void DonkeyKong::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	_timer -= deltaTime;
	if (_timer <= 0.0f) {
		// Attack! aka spawn a barrel
		Barrel* newBarrel = new Barrel(GetGame());
		_timer = ATTACK_TIME;
	}
}
