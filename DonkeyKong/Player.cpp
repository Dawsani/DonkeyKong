#include "Player.h"
#include "Game.h"
#include "WalkingBlock.h"
#include "Ladder.h"
#include "Barrel.h"
#include <iostream> // DEBUG ONLY!

Player::Player(Game* pGame) : Actor(pGame)
{
	_facingRight = true;

	_pInputComponent = new InputComponent(this);
	_pInputComponent->SetMaxSpeed(_moveSpeed);
	_pInputComponent->SetRightKey(SDL_SCANCODE_RIGHT);
	_pInputComponent->SetLeftKey(SDL_SCANCODE_LEFT);
	_pInputComponent->SetUpKey(SDL_SCANCODE_UP);
	_pInputComponent->SetDownKey(SDL_SCANCODE_DOWN);
	_pInputComponent->SetJumpKey(SDL_SCANCODE_SPACE);

	_pRectangleColliderComponent = new RectangleColliderComponent(this);
	_pRectangleColliderComponent->SetSize(Vector2(12, 16));

	_pSpriteComponent = new SpriteComponent(this);
	_pSpriteComponent->SetTexture(pGame->GetTexture("Assets/Jumpman_Idle.png"));

	// Set position to on ground
	SetPosition(Vector2(16, GetGame()->GetWindowSize().y - _pRectangleColliderComponent->GetSize().y - 8));
}

void Player::Update(float deltaTime)
{
	lastPosition = GetPosition();

	Actor::Update(deltaTime);

	InputComponent::Status status = _pInputComponent->GetStatus();

	if (status == InputComponent::IDLE) {
		_pSpriteComponent->SetTexture(GetGame()->GetTexture("Assets/Jumpman_Idle.png"));
	}
	else if (status == InputComponent::RUNNING) {
		_pSpriteComponent->SetTexture(GetGame()->GetTexture("Assets/Jumpman_Running_0.png"));
	}
	else if (status == InputComponent::JUMPING) {
		_pSpriteComponent->SetTexture(GetGame()->GetTexture("Assets/Jumpman_Jumping_0.png"));
	}

	// Apply gravity ONLY IF not climbing
	if (_pInputComponent->GetStatus() != InputComponent::CLIMBING) {
		Vector2 velocity = _pInputComponent->GetVelocity();
		_pInputComponent->SetVelocity(Vector2(velocity.x, velocity.y + _accelerationRate * deltaTime));
	}
	
	// Check for collisions
	_pInputComponent->SetIsGrounded(false);
	_pInputComponent->SetIsTouchingLadder(false);
	for (Actor* actor : GetGame()->GetActors()) {
		if (actor == this) {
			continue;
		}

		RectangleColliderComponent* collider = actor->GetComponent<RectangleColliderComponent>();

		if (collider == nullptr) {
			continue;
		}

		if (_pRectangleColliderComponent->Intersect(*collider)) {
			// If the collision is a walking block
			if (dynamic_cast<WalkingBlock*>(actor) != nullptr) {
				// Appear on top of the box if you came in from above
				if (GetPosition().y  + _pRectangleColliderComponent->GetSize().y * 0.75f < collider->GetActor()->GetPosition().y) {
					_pInputComponent->SetIsGrounded(true);
					_pInputComponent->SetVelocity(Vector2(0.0, 0.0));
					SetPosition(Vector2(GetPosition().x, collider->GetActor()->GetPosition().y - _pRectangleColliderComponent->GetSize().y));
				}
			}
			// If it's like a ladder or whatever, whole 'nother story
			if (dynamic_cast<Ladder*>(actor) != nullptr) {
				// Maybe just set a bool isTouchingLadder, and let 
				_pInputComponent->SetIsTouchingLadder(true);
			}
			// If it's a barrel, die
			if (dynamic_cast<Barrel*>(actor) != nullptr) {
				// TODO: game over!
				std::cout << "GAME OVER!" << std::endl;
			}
		}
	}

	// Make sure player isn't outside screen boundries
	Vector2 pos = GetPosition();
	if (pos.x < 0) {
		pos.x = 0;
	}
	else if (pos.x + _pRectangleColliderComponent->GetSize().x > GetGame()->GetWindowSize().x) {
		pos.x = GetGame()->GetWindowSize().x - _pRectangleColliderComponent->GetSize().x;
	}
	SetPosition(pos);
}
