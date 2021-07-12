#include "HUD.h"

using namespace DungeonGame;

void HUD::InitializeHUDSprites(SDL_Renderer* pRenderer, const std::string& appleFilepath, const std::string& pumpkinFilepath, const std::string& healthFilepath, const std::string& gameOverFilepath, const std::string& victoryFilepath)
{
	AppleTexture = LoadTexture(pRenderer, appleFilepath);
	PumpkinTexture = LoadTexture(pRenderer, pumpkinFilepath);
	HealthTexture = LoadTexture(pRenderer, healthFilepath);
	GameOverTexture = LoadTexture(pRenderer, gameOverFilepath);
	VictoryTexture = LoadTexture(pRenderer, victoryFilepath);
}

void HUD::Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation)
{

	//Health Display
	for (unsigned int i = 0; i < playerState.PlayerHP; ++i)
	{
		MyTexture = HealthTexture;

		if (MyTexture != nullptr)
		{
			SDL_Rect destRect = {

				(int)16.0f + 48.0f * i,
				(int)16.0f,
				(int)Size.X,
				(int)Size.Y };
			SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
		}
	}

	//Inventory Display
	for (unsigned int i = 0; i < playerState.ItemInventory.size(); ++i)
	{
		ItemType currItem = playerState.ItemInventory[i];
		switch (currItem)
		{
		case Item_APPLE:
			MyTexture = AppleTexture;
			break;
		case Item_PUMPKIN:
			MyTexture = PumpkinTexture;
			break;
		default:
			MyTexture = nullptr;
			break;
		}

		if (MyTexture != nullptr)
		{
			SDL_Rect destRect = {
				
				(int)16.0f + 48.0f * i,
				(int)96.0f,
				(int)Size.X,
				(int)Size.Y };
			SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
		}
	}

	if (playerState.PlayerHP <= 0)
	{
		SDL_Rect destRect = {

				250,
				10,
				800,
				444 };
		SDL_RenderCopy(pRenderer, GameOverTexture, nullptr, &destRect);

		
	}
	
	if (playerState.PlayerHasWon())
	{
		SDL_Rect destRect = {

				250,
				100,
				867,
				292 };
		SDL_RenderCopy(pRenderer, VictoryTexture, nullptr, &destRect);

	}
}