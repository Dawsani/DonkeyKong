#pragma once
#include "SpriteComponent.h"
#include <vector>
using namespace std;


class ScrollingSpriteComponent : public SpriteComponent {
public:
	ScrollingSpriteComponent(Actor* pActor, int drawOrder = 100);
	~ScrollingSpriteComponent();

	void SetScrollingTextures(const vector<SDL_Texture*>& textures);

	void SetScreenSize(const Vector2& size) { _screenSize = size; }
	void SetScrollSpeed(float speed) { _scrollSpeed = speed; }

	// This component needs to be updated AND drawn.
	virtual void Update(float deltaTime) override;
	virtual void Draw(SDL_Renderer* pRenderer) override;

private:
	struct ScrollingTexture {
		SDL_Texture* pTexture;
		Vector2 offset;
		int texWidth;
		int texHeight;
	};
	vector<ScrollingTexture> _vecTextures;
	Vector2 _screenSize;
	float _scrollSpeed;
};

