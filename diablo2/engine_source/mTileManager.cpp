#include "mTileManager.h"
#include "mSceneManager.h"
#include "mMeshRenderer.h"
namespace m
{
	TILES TileManager::tiles;
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
		for (std::vector<Tile*> tiles_ : tiles)
			tiles_.clear();
		tiles.clear();

		tiles.resize(_y, std::vector<Tile*>(_x));
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
				
				curScene->AddGameObject(eLayerType::Tile, tile);
				tile->SetCamera(camera);
				if(x == 0 || x == _x - 1 || y == 0 || y == _y - 1)
					tile->SetCulled(false);
				else 
					tile->SetCulled(true);


				SET_MESH(tile, L"RectMesh");
				if ((y == 52 && x == 71) 
					|| (y == 2 && x == 3)
					|| (y == 2 && x == 4)
					|| (y == 2 && x == 5)
					|| (y == 2 && x == 6)
					)
				{
					tile->SetIsWall(true);
					SET_MATERIAL(tile, L"redTile");
					tile->SetSaveMaterial(RESOURCE_FIND(Material, L"redTile"));
				}
				else
				{
					tile->SetIsWall(false);
					SET_MATERIAL(tile, L"greenOutlineTile");
					tile->SetSaveMaterial(RESOURCE_FIND(Material, L"greenOutlineTile"));
				}
				SET_SCALE_XYZ(tile, tileXSize, tileYSize, 1.f);
				SET_POS_XYZ(tile, fX, fY, 1.f);
				tiles[y][x] = tile;
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
	
}