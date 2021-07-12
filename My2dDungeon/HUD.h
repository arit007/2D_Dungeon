#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class HUD : public Sprite
	{
	public:

		void InitializeHUDSprites(SDL_Renderer* pRenderer, const std::string& appleFilepath, const std::string& pumpkinFilepath, const std::string& healthFilepath, const std::string& gameOverFilepath, const std::string& victoryFilepath);

		virtual void Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation);

	private:
		SDL_Texture* AppleTexture;
		SDL_Texture* PumpkinTexture;

		SDL_Texture* HealthTexture;

		SDL_Texture* GameOverTexture;
		SDL_Texture* VictoryTexture;
	};
}