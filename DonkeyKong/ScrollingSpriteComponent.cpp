#include "ScrollingSpriteComponent.h"


ScrollingSpriteComponent::ScrollingSpriteComponent(Actor* pActor, int drawOrder)
: SpriteComponent(pActor, drawOrder) {
	_scrollSpeed = 0.0f;
}


ScrollingSpriteComponent::~ScrollingSpriteComponent() {
}

void ScrollingSpriteComponent::SetScrollingTextures(const vector<SDL_Texture*>& textures) {
	int count = 0;
	
	for (SDL_Texture* tex : textures) {
		ScrollingTexture stex;
		stex.pTexture = tex;
		stex.offset.x = count * _screenSize.x;
		stex.offset.y = 0;
		stex.texWidth = _screenSize.x;
		stex.texHeight = _screenSize.y;
		_vecTextures.push_back(stex);
		count++;
		SDL_QueryTexture(tex, nullptr, nullptr, &stex.texWidth, &stex.texHeight);
	}
}

void ScrollingSpriteComponent::Update(float deltaTime) {
	// Update the offset of each sprite to get a scrolling effect.
	for (ScrollingTexture& t : _vecTextures) {
		t.offset.x += _scrollSpeed * deltaTime;

		// TODO: Once a texture goes off the screen, reset its
		// offset to the right of the last texture.
		if (t.offset.x < -t.texWidth) {
			t.offset.x = _screenSize.x * (_vecTextures.size() - 1);
		}
	}
}

void ScrollingSpriteComponent::Draw(SDL_Renderer* pRenderer) {
	// TODO: This is going to look just like SpriteComponent::Draw
	// except we need to draw every SDL_Texture in _vecTextures.

	for (ScrollingTexture scrollingTexture : _vecTextures) {
		if (scrollingTexture.pTexture) {
			SDL_Rect r;
			// Scale the width/height by owner's scale
			r.w = static_cast<int>(scrollingTexture.texWidth * _pActor->GetScale());
			r.h = static_cast<int>(scrollingTexture.texHeight * _pActor->GetScale());

			// Center the rectangle around the position of the owner
			r.x = static_cast<int>((_pActor->GetPosition().x - r.w / 2) + scrollingTexture.offset.x);
			r.y = static_cast<int>(_pActor->GetPosition().y - r.h / 2);

			// Draw (have to convert angle from radians to degrees, and clockwise to counter)
			SDL_RenderCopyEx(pRenderer,
				scrollingTexture.pTexture,
				nullptr,
				&r,
				-Math::ToDegrees(_pActor->GetRotation()),
				nullptr,
				SDL_FLIP_NONE);
		}
	}

}
