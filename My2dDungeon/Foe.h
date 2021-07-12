#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Foe : public Sprite
	{
	public:
		void SetFoeIndex(int newIndex);

		virtual void Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState);

	private:
		int FoeIndex;
	};
}
