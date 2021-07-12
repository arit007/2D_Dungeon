#include "GameCore.h"
#include "Sprite.h"
#include "Hero.h"
#include "RoomRenderer.h"
#include "Item.h"
#include "HUD.h"
#include "BG.h"
#include "Foe.h"
#include "Door.h"

namespace DungeonGame
{
	//SDL_Texture* pTestTexture = nullptr;

	std::vector<Sprite*> SpriteList;
	
	bool PlayerState::PlayerHasWon() const
	{
		int numberOfPumpkins = 0;

		for (int i = 0; i < ItemInventory.size(); ++i)
		{
			if (ItemInventory[i] == Item_PUMPKIN)
			{
				numberOfPumpkins++;
			}
		}

		return numberOfPumpkins >= 5;
	}

	bool WorldState::IsWalkableTile(const Vector2d& inPosition)
	{
		
		for (int i = 0; i < Doors.size(); ++i)
		{
			if (Doors[i].Alive)
			{
				Vector2d vecToDoor = Doors[i].Position - inPosition;
				if (vecToDoor.GetLength() < 40.0f)
				{
					return false;
				}
			}
			
		}
		


		int column = (int)inPosition.X / TileSizeInPixels.X;
		int row = (int)inPosition.Y / TileSizeInPixels.Y;

		char currentTile = ' ';

		int index = row * TilesPerRow + column;
		if (index >= 0 && index < (int)Tiles.size())
		{
			currentTile = Tiles[index];
		}
		
		return currentTile == '.';
	}


	void InitializeGame(SDL_Renderer* pRenderer, PlayerState& playerState, WorldState& worldState)
	{
		playerState.HasFinishedGame = false;
		playerState.PlayerHP = 5;
		playerState.InvincibilitySeconds = 0.0f;

		playerState.WantsToGoUP = false;
		playerState.WantsToGoDown = false;
		playerState.WantsToGoLeft = false;
		playerState.WantsToGoRight = false;

		worldState.SecondsSincePlayerDefeat = 0.0f;



		worldState.TilesPerRow = 34; 
		worldState.TileSizeInPixels = Vector2d(72.0f, 72.0f);
		worldState.Tiles =
		   
			
			"     #########  #########  ##  ## "
			"    #.........##.........##..##..#"
			"    #............................#"
			" ###..........##.........##......#"
			"#............#  #.......#  #....# "
			" ###.........#   #######    #..#  "
			"    ######.###               ##   "
			"       #....#                     "
			"       #....#                     "
			"       #....#                     "
			"       ######                     "
			
			;

		worldState.Items.push_back({ true, Item_APPLE, Vector2d(7.0f * worldState.TileSizeInPixels.X, 5.0f * worldState.TileSizeInPixels.Y) });

		worldState.Items.push_back({ true, Item_PUMPKIN, Vector2d(9.0f * worldState.TileSizeInPixels.X, 9.0f * worldState.TileSizeInPixels.Y) });
		worldState.Items.push_back({ true, Item_PUMPKIN, Vector2d(20.0f * worldState.TileSizeInPixels.X, 2.0f * worldState.TileSizeInPixels.Y) });
		worldState.Items.push_back({ true, Item_PUMPKIN, Vector2d(18.0f * worldState.TileSizeInPixels.X, 5.0f * worldState.TileSizeInPixels.Y) });
		worldState.Items.push_back({ true, Item_PUMPKIN, Vector2d(28.0f * worldState.TileSizeInPixels.X, 2.0f * worldState.TileSizeInPixels.Y) });
		worldState.Items.push_back({ true, Item_PUMPKIN, Vector2d(30.0f * worldState.TileSizeInPixels.X, 6.0f * worldState.TileSizeInPixels.Y) });
		
		worldState.Foes.push_back({ true, Vector2d(13.0f * worldState.TileSizeInPixels.X, 3.0f * worldState.TileSizeInPixels.Y) });
		worldState.Foes.push_back({ true, Vector2d(23.0f * worldState.TileSizeInPixels.X, 3.0f * worldState.TileSizeInPixels.Y) });
		worldState.Foes.push_back({ true, Vector2d(28.0f * worldState.TileSizeInPixels.X, 3.0f * worldState.TileSizeInPixels.Y) });

		worldState.Doors.push_back({ true, Vector2d(14.0f * worldState.TileSizeInPixels.X, 3.0f * worldState.TileSizeInPixels.Y) });
		worldState.Doors.push_back({ true, Vector2d(25.0f * worldState.TileSizeInPixels.X, 3.0f * worldState.TileSizeInPixels.Y) });

		BG* bg = new BG;
		bg->Initialize(pRenderer, "Assets/city.bmp");
		bg->Size = Vector2d(WINDOW_WIDTH, WINDOW_HEIGHT);
		SpriteList.push_back(bg);

		RoomRenderer* roomRenderer = new RoomRenderer;
		roomRenderer->InitializeRoomTiles(pRenderer, "Assets/floor.bmp", "Assets/border.bmp");
		SpriteList.push_back(roomRenderer);

		for (unsigned int i = 0; i < worldState.Items.size(); ++i)
		{
			std::string itemFilepath = "Assets/apple.bmp";
			switch (worldState.Items[i].Type)
			{
			case Item_APPLE:
				itemFilepath = "Assets/apple.bmp";
				break;
			case Item_PUMPKIN:
				itemFilepath = "Assets/pumpkin.bmp";
				break;
			
			}

			Item* newItem = new Item;
			newItem->Initialize(pRenderer, itemFilepath);
			newItem->SetItemIndex(i);
			SpriteList.push_back(newItem);
		}


		for (unsigned int i = 0; i < worldState.Foes.size(); ++i)
		{
			std::string foeFilepath = "Assets/blob.bmp";
			

			Foe* newFoe = new Foe;
			newFoe->Initialize(pRenderer, foeFilepath);
			newFoe->SetFoeIndex(i);
			SpriteList.push_back(newFoe);
		}

		for (unsigned int i = 0; i < worldState.Doors.size(); ++i)
		{
			
			Door* newDoor = new Door;
			newDoor->Initialize(pRenderer, "Assets/egg.bmp");//egg sprite acts as door blocking path
			newDoor->SetDoorIndex(i);
			SpriteList.push_back(newDoor);
		}


		Hero* newHero = new Hero;
		newHero->Initialize(pRenderer, "Assets/heroSprite.bmp");
		playerState.PlayerPosition = Vector2d(2.0f * worldState.TileSizeInPixels.X, 5.0f * worldState.TileSizeInPixels.Y);
		//newHero->Position = Vector2d(3.0f * worldState.TileSizeInPixels.X, 3.0f * worldState.TileSizeInPixels.Y);
		SpriteList.push_back(newHero);

		HUD* newHUD = new HUD;
		newHUD->InitializeHUDSprites(pRenderer, "Assets/apple.bmp", "Assets/pumpkin.bmp", "Assets/heart.bmp", "Assets/GameOver.bmp", "Assets/victory.bmp");
		SpriteList.push_back(newHUD);

		

	}

	void GetInput(PlayerState& playerState, const WorldState& worldState)
	{
		SDL_Event e = {};
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				playerState.HasFinishedGame = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
					case SDLK_ESCAPE:
						playerState.HasFinishedGame = true;
						break;
					
					case SDLK_w:
					case SDLK_UP:
						playerState.WantsToGoUP = true;
						break;

					case SDLK_s:
					case SDLK_DOWN:
						playerState.WantsToGoDown = true;
						break;

					case SDLK_a:
					case SDLK_LEFT:
						playerState.WantsToGoLeft = true;
						break;

					case SDLK_d:
					case SDLK_RIGHT:
						playerState.WantsToGoRight = true;
						break;
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
				case SDLK_w:
				case SDLK_UP:
					playerState.WantsToGoUP = false;
					break;

				case SDLK_s:
				case SDLK_DOWN:
					playerState.WantsToGoDown = false;
					break;

				case SDLK_a:
				case SDLK_LEFT:
					playerState.WantsToGoLeft = false;
					break;

				case SDLK_d:
				case SDLK_RIGHT:
					playerState.WantsToGoRight = false;
					break;
				}
				
			}
		}
	}

	void UpdateGame(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
	{
		//testDirection.Normalize();
		//testSprite.Position += testDirection * 50.0f * deltaSeconds;

		for (unsigned int i = 0; i < SpriteList.size(); ++i)
		{
			SpriteList[i]->Update(deltaSeconds, playerState, worldState);
		}

		if (playerState.PlayerHP <= 0 || playerState.PlayerHasWon())
		{
			
			worldState.SecondsSincePlayerDefeat += deltaSeconds;

			if (worldState.SecondsSincePlayerDefeat > 3.0f)
			{
				playerState.HasFinishedGame = true;
			}
		}
			
	}

	void RenderGame(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState)
	{
		SDL_RenderClear(pRenderer);
		
		for (unsigned int i = 0; i < SpriteList.size(); ++i)
		{
			SpriteList[i]->Render(pRenderer, playerState, worldState, Vector2d(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f) - worldState.CameraPosition );
		}

		SDL_RenderPresent(pRenderer);
	}

	void CleanupGame(PlayerState& playerState, WorldState& worldState)
	{
		for (unsigned int i = 0; i < SpriteList.size(); ++i)
		{
			SpriteList[i]->Cleanup();
			delete SpriteList[i];
		}
		SpriteList.clear();
		Sprite::CleanupTextures();
	}
}

