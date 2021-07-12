#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Door : public Sprite
	{
	public:
		void SetDoorIndex(int newIndex);

		virtual void Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState);

	private:
		int DoorIndex;
	};
}