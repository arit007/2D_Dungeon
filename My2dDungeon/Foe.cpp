#include "Foe.h"

using namespace DungeonGame;

void Foe::SetFoeIndex(int newIndex)
{
	FoeIndex = newIndex;
}

void Foe::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	const float FOE_MOVEMENT_SPEED = 80.0f;

	FoeData& currFoe = worldState.Foes[FoeIndex];

	if (currFoe.Alive && !playerState.PlayerHasWon())
	{
		Vector2d vecToPlayer = currFoe.Position - playerState.PlayerPosition;
		if (vecToPlayer.GetLength() < 30.0f)
		{
			//currFoe.Alive = false;
			if (playerState.PlayerHP > 0 && playerState.InvincibilitySeconds <= 0.0f)
			{
				playerState.PlayerHP -= 1;
				playerState.InvincibilitySeconds = 1.5f;
			}
			
		}

		vecToPlayer.Normalize();
		vecToPlayer *= -1.0f;
		currFoe.Position += vecToPlayer * FOE_MOVEMENT_SPEED * deltaSeconds;

	}

	Position = currFoe.Position - Vector2d(Size.X * 0.5f, Size.Y * 0.85f);
	Visible = currFoe.Alive;

}