#include "Ship.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "InputComponent.h"

Ship::Ship(Game* pGame) : Actor(pGame)
{
	// Set starting position
	Vector2 windowSize = pGame->GetWindowSize();
	//SetPosition(Vector2(windowSize.x / 2, windowSize.y / 2));
	SetPosition(Vector2(512.0f, 384.0f));

	// Add SpriteComponent
	SpriteComponent* sprite = new SpriteComponent(this);
	sprite->SetTexture(pGame->GetTexture("Assets/Ship.png"));

	// Add Input Component
	InputComponent* input = new InputComponent(this);
	input->SetRightKey(SDL_SCANCODE_W);
	input->SetLeftKey(SDL_SCANCODE_S);
	input->SetMaxSpeed(200);

}

void Ship::ProcessInput(const uint8_t* keyState)
{
	Actor::ProcessInput(keyState);

	if (keyState[SDL_SCANCODE_SPACE] && _laserCooldown <= 0) {
		_laserCooldown = 0.5f;
	}
}

void Ship::Update(float deltaTime)
{
	Actor::Update(deltaTime);
	_laserCooldown -= deltaTime;
}
