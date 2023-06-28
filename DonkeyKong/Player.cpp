#include "Player.h"
#include "Game.h"

Player::Player(Game* pGame) : Actor(pGame)
{
	_facingRight = true;
	_playerStatus = IDLE;

	_pInputComponent = new InputComponent(this);
	_pInputComponent->SetMaxSpeed(_moveSpeed);
	_pInputComponent->SetRightKey(SDL_SCANCODE_RIGHT);
	_pInputComponent->SetLeftKey(SDL_SCANCODE_LEFT);
	_pInputComponent->SetJumpKey(SDL_SCANCODE_SPACE);

	_pRectangleColliderComponent = new RectangleColliderComponent(this);
	_pRectangleColliderComponent->SetSize(Vector2(12, 16));

	_pSpriteComponent = new SpriteComponent(this);
	_pSpriteComponent->SetTexture(pGame->GetTexture("Assets/Jumpman_Idle.png"));

	SetPosition(Vector2(16, GetGame()->GetWindowSize().y - _pRectangleColliderComponent->GetSize().y - 8));

}

void Player::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	if (_playerStatus == IDLE) {
		_pSpriteComponent->SetTexture(GetGame()->GetTexture("Assets/Jumpman_Idle.png"));
	}
	else if (_playerStatus == RUNNING) {
		_pSpriteComponent->SetTexture(GetGame()->GetTexture("Assets/Jumpman_Running_0.png"));
	}
	else if (_playerStatus == JUMPING) {
		_pSpriteComponent->SetTexture(GetGame()->GetTexture("Assets/Jumpman_Jumping_0.png"));
	}

	// Apply gravity
	_velocity = Vector2(_velocity.x, _velocity.y + _accelerationRate * deltaTime);
	SetPosition(Vector2(GetPosition().x + _velocity.x * deltaTime, GetPosition().y + _velocity.y * deltaTime));

	// Check for collisions
	for (Actor* actor : GetGame()->GetActors()) {
		if (actor == this) {
			continue;
		}

		RectangleColliderComponent* collider = actor->GetComponent<RectangleColliderComponent>();

		if (collider == nullptr) {
			continue;
		}

		if (_pRectangleColliderComponent->Intersect(*collider)) {
			// Appear on top of the box
			_velocity = Vector2(0.0, 0.0);
			SetPosition(Vector2(GetPosition().x, collider->GetActor()->GetPosition().y - _pRectangleColliderComponent->GetSize().y));
		}
	}

}
