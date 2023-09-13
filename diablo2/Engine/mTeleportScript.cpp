#include "mTeleportScript.h"

#include "../engine_source/mTileManager.h"

#include "mMoveAbleObject.h"
namespace m
{
	TeleportScript::TeleportScript()
	{
		TileManager::playerStandTile;

	}

	TeleportScript::~TeleportScript()
	{
	}

	void TeleportScript::Initialize()
	{
		Script::Initialize();
	}

	void TeleportScript::Update()
	{
		Script::Update();
		
		checkWallIfWallGetNearByCoord();
	}

	void TeleportScript::LateUpdate()
	{
		Script::LateUpdate();
	}

	void TeleportScript::Render()
	{
		Script::Render();
	}

	void TeleportScript::checkWallIfWallGetNearByCoord()
	{
		Vector2 coord = TileManager::GetHoverTileCoord();

		Tile* hoverTile = TileManager::pathFindingTiles[coord.y][coord.x];
		
		if (hoverTile->GetIsWall())
		{
			getNearByCoord(hoverTile);
		}else{
			Vector3 hoverTilePosition =GET_POS(hoverTile);
			TileManager::playerStandTile = hoverTile;
			SET_POS_VEC(mOwner, hoverTilePosition);
			GetOwner()->SetState(GameObject::eState::Delete);
		}
	}
	void TeleportScript::getNearByCoord(Tile* targetTile)
	{
		int direct1[8][2] = {
	{-1, -1}, {0, -1}, {1, -1},
	{-1, 0},	/*     curPosition    */{1, 0},
	{-1, 1}, {0, 1}, {1, 1}
		};

		std::vector<Tile*> tileVector;
		//Vector2 playerCoord = TileManager::GetPlayerPositionCoord();
		;
		tileVector.push_back(targetTile);

		for (int i = 0; i < 8; ++i)
		{
			int dx = direct1[i][0];
			int dy = direct1[i][1];
		}
	}
}
