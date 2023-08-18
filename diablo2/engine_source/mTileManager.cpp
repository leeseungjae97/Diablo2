#include "mTileManager.h"
#include "mSceneManager.h"
#include "mMeshRenderer.h"
#include "mMouseManager.h"
#include "mMonsterManager.h"
#include "mTileSystem.h"

#include "../Engine/mPlayerInfo.h"
#include "../Engine/mPlayer.h"
#include "../Engine/mMonster.h"


namespace m
{
	TILES TileManager::pathFindingTiles;
	std::vector<Tile*> TileManager::notCulledTiles;
	Tile* TileManager::hoverTile = nullptr;
	Tile* TileManager::playerStandTile = nullptr;
	float TileManager::tileXSize = 80.f;
	float TileManager::tileYSize = 40.f;
	//float TileManager::iniX = 0.f;
	//float TileManager::iniY = 0.f;
	int TileManager::tileXLen = 0.f;
	int TileManager::tileYLen = 0.f;
	
	void TileManager::MakeTile(int _x, int _y, Camera* camera)
	{
		for (std::vector<Tile*> tiles_ : pathFindingTiles)
			tiles_.clear();
		pathFindingTiles.clear();

		pathFindingTiles.resize(_y, std::vector<Tile*>(_x));
		tileXLen = _x;
		tileYLen = _y;

		Scene* curScene = SceneManager::GetActiveScene();

		for (int y = 0; y < _y; ++y)
		{
			for (int x = 0; x < _x; ++x)
			{
				float fX = (float)(tileXSize * (x - y)) / 2.f;
				float fY = (float)(tileYSize * (x + y)) / 2.f;
				//fX += iniX;
				//fY += iniY;

				Tile* tile = new Tile();
				tile->SetCoord(Vector2(x, y));
				
				//curScene->AddGameObject(eLayerType::Tile, tile);
				//tile->SetCamera(camera);
				//if(x == 0 || x == _x - 1 || y == 0 || y == _y - 1)
				//	tile->SetCulled(false);
				//else
				//tile->SetCulled(true);

				//SET_MESH(tile, L"RectMesh");
				if (   (y == 55 && x == 70)
					|| (y == 54 && x == 70)
					|| (y == 53 && x == 70)
					|| (y == 52 && x == 70)
					|| (y == 56 && x == 70)
					|| (y == 51 && x == 71) 
					|| (y == 52 && x == 71)
					|| (y == 53 && x == 71)
					|| (y == 54 && x == 71)
					|| (y == 55 && x == 71)
					|| (y == 56 && x == 71)
					|| (y == 57 && x == 71)
					|| (y == 58 && x == 71)
					|| (y == 52 && x == 72)
					|| (y == 53 && x == 72)
					|| (y == 54 && x == 72)
					|| (y == 55 && x == 72)
					|| (y == 56 && x == 72)
					|| (y == 57 && x == 72)
					|| (y == 53 && x == 73)
					|| (y == 54 && x == 73)
					|| (y == 55 && x == 73)
					|| (y == 56 && x == 73)
					|| (y == 55 && x == 74)
					|| (y == 54 && x == 74)
					|| (y == 50 && x == 75)
					|| (y == 50 && x == 76)
					|| (y == 50 && x == 77)
					|| (y == 49 && x == 74)
					|| (y == 49 && x == 75)
					|| (y == 49 && x == 76)
					|| (y == 49 && x == 77)
					|| (y == 49 && x == 78)
					|| (y == 48 && x == 73)
					|| (y == 48 && x == 74)
					|| (y == 48 && x == 75)
					|| (y == 48 && x == 76)
					|| (y == 48 && x == 77)
					|| (y == 48 && x == 78)
					|| (y == 48 && x == 79)
					|| (y == 47 && x == 73)
					|| (y == 47 && x == 74)
					|| (y == 47 && x == 75)
					|| (y == 47 && x == 76)
					|| (y == 47 && x == 77)
					|| (y == 47 && x == 78)
					|| (y == 47 && x == 79)
					|| (y == 46 && x == 75)
					|| (y == 46 && x == 76)
					|| (y == 46 && x == 77)
					|| (y == 46 && x == 78)
					|| (y == 46 && x == 79)
					|| (y == 47 && x == 82)
					|| (y == 48 && x == 82)
					|| (y == 49 && x == 82)
					|| (y == 50 && x == 82)
					|| (y == 51 && x == 82)
					|| (y == 52 && x == 82)
					|| (y == 57 && x == 82)
					|| (y == 58 && x == 82)
					|| (y == 59 && x == 82)
					|| (y == 60 && x == 82)
					|| (y == 61 && x == 82)
					|| (y == 47 && x == 83)
					|| (y == 48 && x == 83)
					|| (y == 49 && x == 83)
					|| (y == 50 && x == 83)
					|| (y == 51 && x == 83)
					|| (y == 52 && x == 83)
					|| (y == 56 && x == 83)
					|| (y == 57 && x == 83)
					|| (y == 58 && x == 83)
					|| (y == 59 && x == 83)
					|| (y == 60 && x == 83)
					|| (y == 61 && x == 83)
					|| (y == 48 && x == 84)
					|| (y == 49 && x == 84)
					|| (y == 50 && x == 84)
					|| (y == 51 && x == 84)
					|| (y == 52 && x == 84)
					|| (y == 56 && x == 84)
					|| (y == 57 && x == 84)
					|| (y == 58 && x == 84)
					|| (y == 59 && x == 84)
					|| (y == 60 && x == 84)
					|| (y == 49 && x == 85)
					|| (y == 50 && x == 85)
					|| (y == 51 && x == 85)
					|| (y == 52 && x == 85)
					|| (y == 55 && x == 85)
					|| (y == 56 && x == 85)
					|| (y == 57 && x == 85)
					|| (y == 58 && x == 85)
					|| (y == 59 && x == 85)
					|| (y == 51 && x == 86)
					|| (y == 52 && x == 86)
					|| (y == 53 && x == 86)
					|| (y == 55 && x == 86)
					|| (y == 56 && x == 86)
					|| (y == 57 && x == 86)
					|| (y == 58 && x == 86)
					|| (y == 62 && x == 79)
					|| (y == 62 && x == 78)
					|| (y == 62 && x == 77)
					|| (y == 62 && x == 76)
					|| (y == 62 && x == 75)
					|| (y == 61 && x == 79)
					|| (y == 61 && x == 78)
					|| (y == 61 && x == 77)
					|| (y == 61 && x == 76)
					|| (y == 61 && x == 75)
					|| (y == 61 && x == 74)
					|| (y == 60 && x == 78)
					|| (y == 60 && x == 77)
					|| (y == 60 && x == 76)
					|| (y == 60 && x == 75)
					|| (y == 60 && x == 74)
					|| (y == 60 && x == 73)
					|| (y == 59 && x == 77)
					|| (y == 59 && x == 76)
					|| (y == 59 && x == 75)
					|| (y == 59 && x == 74)
					)
				{
					tile->SetIsWall(true);
					//SET_MATERIAL(tile, L"redTile");
					tile->SetSaveMaterial(RESOURCE_FIND(Material, L"redTile"));
				}
				else
				{
					tile->SetIsWall(false);
					//SET_MATERIAL(tile, L"greenOutlineTile");
					tile->SetSaveMaterial(RESOURCE_FIND(Material, L"greenOutlineTile"));
				}
				SET_SCALE_XYZ(tile, tileXSize, tileYSize, 1.f);
				SET_POS_XYZ(tile, fX, fY, 1.f);
				pathFindingTiles[y][x] = tile;
			}
		}
		GameObject* tiles = new GameObject();
		tiles->SetCamera(camera);
		tiles->SetName(L"pathFindingTiles");
		curScene->AddGameObject(eLayerType::Tile, tiles);
		SET_POS_XYZ(tiles, 0.f, 0.f, 1.f);
		SET_SCALE_XYZ(tiles, TileManager::tileXSize, TileManager::tileYSize, 1.f);
		ADD_COMP(tiles, TileSystem);
	}

	void TileManager::TilesUpdate()
	{
		Scene* curScene = SceneManager::GetActiveScene();
		
		Vector2 tileScale = Vector2(TileManager::tileXSize, TileManager::tileYSize);

		Camera* mainCam = curScene->GetSceneMainCamera();
		Vector3 mousePos = MouseManager::UnprojectionMousePos(1.f, mainCam);

		Vector3 ppos = Vector3::One;
		Vector3 pscale = Vector3::One;

		TilesCulling();

		if (nullptr != PlayerInfo::player)
		{
			ppos = GET_POS(PlayerInfo::player);
			pscale = GET_SCALE(PlayerInfo::player);
		}
		
		MAKE_VEC2_F_VEC3(mousePosV2, mousePos);
		for (Tile* tile : notCulledTiles)
		{
			Vector3 posV3 = GET_POS(tile);
			Vector2 coord = tile->GetCoord();
			MAKE_VEC2_F_VEC3(pos, posV3);
			int y = coord.y;
			int x = coord.y;
			if (Vector2::PointIntersectRhombus(pos, tileScale, mousePosV2))
			{
				hoverTile = tile;
				SET_MATERIAL(hoverTile, L"greenTile");
			}
			else
			{
				SET_MATERIAL_D(tile, tile->GetSaveMaterial());
			}
			Vector2 playerPosV2Left = Vector2(ppos.x - pscale.x / 2.f, ppos.y - pscale.y / 2.f);
			Vector2 playerPosV2Right = Vector2(ppos.x + pscale.x / 2.f, ppos.y - pscale.y / 2.f);
			if (Vector2::PointIntersectRhombus(pos, tileScale, GET_VEC2_F_VEC3_D(ppos)))
			{
				TileManager::playerStandTile = tile;
			}
			for (Monster* monster : MonsterManager::monsters)
			{
				if (nullptr == monster) continue;
				if (monster->GetState() == GameObject::eState::Delete) continue;

				MAKE_VEC2_F_VEC3(mPosV2, GET_POS(monster));
				if (Vector2::PointIntersectRhombus(pos, tileScale, mPosV2))
				{
					monster->SetCoord(tile->GetCoord());
				}
			}
		}
		notCulledTiles.clear();
	}

	void TileManager::TilesCulling()
	{
		//Scene* curScene = SceneManager::GetActiveScene();
		//Camera* mainCam = curScene->GetSceneMainCamera();
		//float width = mainCam->GetWidth();
		//float height = mainCam->GetHeight();
		////mainCam->GetOwner()->Get
		//for(int y = 0 ; y < pathFindingTiles.size(); ++y)
		//{
		//	for(int x = 0 ; x < pathFindingTiles[0].size(); ++x)
		//	{
		//		Tile* tile = pathFindingTiles[y][x];

		//		if (Vector2::PointIntersectRect(GET_VEC2_F_VEC3_D(GET_POS(mainCam->GetOwner())), Vector2(width, height), GET_VEC2_F_VEC3_D(GET_POS(tile))))
		//		{
		//			notCulledTiles.push_back(tile);
		//			//tile->SetCulled(false);
		//		}

		//	}
		//}
	}

	Vector2 TileManager::GetHoverTileCoord()
	{
		return nullptr == hoverTile ? Vector2::Zero : hoverTile->GetCoord();
	}

	Vector2 TileManager::GetPlayerPositionCoord()
	{
		return nullptr == playerStandTile ? Vector2::Zero : playerStandTile->GetCoord();
	}
}