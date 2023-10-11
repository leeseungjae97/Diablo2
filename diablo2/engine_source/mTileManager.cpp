#include "mTileManager.h"
#include "mSceneManager.h"
#include "mMeshRenderer.h"
#include "mMouseManager.h"
#include "mMonsterManager.h"

#include "../Engine/mPlayerManager.h"
#include "../Engine/mPlayer.h"
#include "../Engine/mMonster.h"
#include "../Engine/mFloor.h"

#include "MapLookUpTables.h"
#include "mWallObjectManager.h"

namespace m
{
	TILES TileManager::pathFindingTiles;
	Tile* TileManager::hoverTile = nullptr;
	Tile* TileManager::playerStandTile = nullptr;
	float TileManager::tileXSize = 80.f;
	float TileManager::tileYSize = 40.f;
	int TileManager::tileXLen = 0.f;
	int TileManager::tileYLen = 0.f;
	TileSystem* TileManager::curTileSystem = nullptr;
	
	void TileManager::MakeTile(int _x, int _y, Camera* camera)
	{
		Scene* curScene = SceneManager::GetActiveScene();
		pathFindingTiles.resize(_y, std::vector<Tile*>(_x));
		tileXLen = _x;
		tileYLen = _y;

		for (int y = 0; y < _y; ++y)
		{
			for (int x = 0; x < _x; ++x)
			{
				float fX = (float)(tileXSize * (x - y)) / 2.f;
				float fY = (float)(tileYSize * (x + y)) / 2.f;

				Tile* tile = new Tile();
				tile->SetCoord(Vector2(x, y));

                tile->SetIsWall(false);
				tile->SetScale(Vector3(tileXSize, tileYSize, 1.f));
				tile->SetPos(Vector3(fX, fY, 1.f));
				pathFindingTiles[y][x] = tile;

			}
		}
		
		GameObject* tileDrawObject = new GameObject();
		tileDrawObject->SetCamera(camera);
		curScene->AddGameObject(eLayerType::Tile, tileDrawObject);
		SET_POS_XYZ(tileDrawObject, 0.f, 0.f, 1.f);
		curTileSystem = ADD_COMP(tileDrawObject, TileSystem);
	}

	void TileManager::TilesUpdate()
	{
		
	}
	void TileManager::Release()
	{
		for(int y = 0 ; y < tileYLen; ++y)
		{
			for (int x = 0; x < tileXLen; ++x)
			{
				if(pathFindingTiles[y][x])
					delete pathFindingTiles[y][x];
			}
		}

		hoverTile = nullptr;
		playerStandTile = nullptr;
	}
	void TileManager::TileIsWallChange()
	{
		if (curTileSystem)
			curTileSystem->WallChange();
	}
	void TileManager::MakeStageFloor(int stage)
	{
	    
	}
	void TileManager::MakeStageWall(int stage)
	{
		Vector2* wall = nullptr;
		Vector2* throughWall = nullptr;

		if(stage == 3)
			wall = stage4Walls;

		if (stage == 2)
			wall = stage3Walls;

		if (stage == 1)
			wall = stage2Walls;

		if (stage == 0)
			wall = stage1Walls;

		for(int i = 0 ; i < 1000; ++i)
		{
			Vector2 wallCoord = wall[i];
			int y = static_cast<int>(wallCoord.y);
			int x = static_cast<int>(wallCoord.x);

			if(stage == 1)
				pathFindingTiles[y][x]->SetThroughWall(false);
			if (stage == 0 || stage == 2 || stage == 3)
				pathFindingTiles[y][x]->SetThroughWall(true);
			
			pathFindingTiles[y][x]->SetIsWall(true);
		}
	}
    void TileManager::TileIsWallReset()
    {
		WallObjectManager::EraseAll();
		for (int y = 0; y < tileYLen; ++y)
		{
			for (int x = 0; x < tileXLen; ++x)
			{
				if (pathFindingTiles[y][x])
				{
					pathFindingTiles[y][x]->SetIsWall(false);
					pathFindingTiles[y][x]->SetThroughWall(true);
				}
			}
		}
    }

    Vector2 TileManager::GetHoverTileCoord()
	{
		return nullptr == hoverTile ? Vector2::Zero : hoverTile->GetCoord();
	}

	Vector2 TileManager::GetPlayerPositionCoord()
	{
		return nullptr == playerStandTile ? Vector2::Zero : playerStandTile->GetCoord();
	}
	Vector3 TileManager::GetPlayerPosition()
	{
		return nullptr == playerStandTile ? Vector3::Zero : playerStandTile->GetPos();
	}
}
