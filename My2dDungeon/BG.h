#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class BG : public Sprite
	{
	public:
		virtual void Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation);

	
	};
}