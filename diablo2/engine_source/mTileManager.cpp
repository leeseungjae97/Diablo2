#include "mTileManager.h"
#include "mSceneManager.h"
#include "mMeshRenderer.h"
namespace m
{
	TILES TileManager::tiles;
	Tile* TileManager::hoverTile = nullptr;
	Tile* TileManager::playerStandTile = nullptr;

	void TileManager::MakeTile(int _x, int _y, Camera* camera)
	{
		for (std::vector<Tile*> tiles_ : tiles)
			tiles_.clear();
		tiles.clear();

		tiles.resize(_x, std::vector<Tile*>(_y));

		Scene* curScene = SceneManager::GetActiveScene();
		float TILE_SIZE_X = 160.f;
		float TILE_SIZE_Y = 80.f;
		for (int y = 0; y < _x; ++y)
		{
			for (int x = 0; x < _y; ++x)
			{
				float fX = (float)(TILE_SIZE_X * (x - y)) / 2.f;
				float fY = (float)(TILE_SIZE_Y * (x + y)) / 2.f;
				Tile* tile = new Tile();
				tile->SetCoord(Vector2(x, y));
				
				curScene->AddGameObject(eLayerType::Tile, tile);
				tile->SetCamera(camera);
				SET_MESH(tile, L"RectMesh");
				if ((y == 2 && x == 2) 
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
					SET_MATERIAL(tile, L"tile");
					tile->SetSaveMaterial(RESOURCE_FIND(Material, L"tile"));
				}
				SET_SCALE_XYZ(tile, TILE_SIZE_X, TILE_SIZE_Y, 1.f);
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