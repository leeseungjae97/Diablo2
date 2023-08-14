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
				//if(x == 0 || x == _x - 1 || y == 0 || y == _y - 1)
				//	tile->SetCulled(false);
				//else 
				//	tile->SetCulled(true);


				SET_MESH(tile, L"RectMesh");
				if (   (y == 55 && x == 70)
					&& (y == 54 && x == 70)
					&& (y == 53 && x == 70)
					&& (y == 52 && x == 70)
					&& (y == 56 && x == 70)
					&& (y == 51 && x == 71) 
					&& (y == 52 && x == 71)
					&& (y == 53 && x == 71)
					&& (y == 54 && x == 71)
					&& (y == 55 && x == 71)
					&& (y == 56 && x == 71)
					&& (y == 57 && x == 71)
					&& (y == 58 && x == 71)
					&& (y == 52 && x == 72)
					&& (y == 53 && x == 72)
					&& (y == 54 && x == 72)
					&& (y == 55 && x == 72)
					&& (y == 56 && x == 72)
					&& (y == 57 && x == 72)
					&& (y == 53 && x == 73)
					&& (y == 54 && x == 73)
					&& (y == 55 && x == 73)
					&& (y == 56 && x == 73)
					&& (y == 55 && x == 74)
					&& (y == 54 && x == 74)
					&& (y == 50 && x == 75)
					&& (y == 50 && x == 76)
					&& (y == 50 && x == 77)
					&& (y == 49 && x == 74)
					&& (y == 49 && x == 75)
					&& (y == 49 && x == 76)
					&& (y == 49 && x == 77)
					&& (y == 49 && x == 78)
					&& (y == 48 && x == 73)
					&& (y == 48 && x == 74)
					&& (y == 48 && x == 75)
					&& (y == 48 && x == 76)
					&& (y == 48 && x == 77)
					&& (y == 48 && x == 78)
					&& (y == 48 && x == 79)
					&& (y == 47 && x == 73)
					&& (y == 47 && x == 74)
					&& (y == 47 && x == 75)
					&& (y == 47 && x == 76)
					&& (y == 47 && x == 77)
					&& (y == 47 && x == 78)
					&& (y == 47 && x == 79)
					&& (y == 46 && x == 75)
					&& (y == 46 && x == 76)
					&& (y == 46 && x == 77)
					&& (y == 46 && x == 78)
					&& (y == 46 && x == 79)
					&& (y == 47 && x == 82)
					&& (y == 48 && x == 82)
					&& (y == 49 && x == 82)
					&& (y == 50 && x == 82)
					&& (y == 51 && x == 82)
					&& (y == 52 && x == 82)
					&& (y == 57 && x == 82)
					&& (y == 58 && x == 82)
					&& (y == 59 && x == 82)
					&& (y == 60 && x == 82)
					&& (y == 61 && x == 82)
					&& (y == 47 && x == 83)
					&& (y == 48 && x == 83)
					&& (y == 49 && x == 83)
					&& (y == 50 && x == 83)
					&& (y == 51 && x == 83)
					&& (y == 52 && x == 83)
					&& (y == 56 && x == 83)
					&& (y == 57 && x == 83)
					&& (y == 58 && x == 83)
					&& (y == 59 && x == 83)
					&& (y == 60 && x == 83)
					&& (y == 61 && x == 83)
					&& (y == 48 && x == 84)
					&& (y == 49 && x == 84)
					&& (y == 50 && x == 84)
					&& (y == 51 && x == 84)
					&& (y == 52 && x == 84)
					&& (y == 56 && x == 84)
					&& (y == 57 && x == 84)
					&& (y == 58 && x == 84)
					&& (y == 59 && x == 84)
					&& (y == 60 && x == 84)
					&& (y == 49 && x == 85)
					&& (y == 50 && x == 85)
					&& (y == 51 && x == 85)
					&& (y == 52 && x == 85)
					&& (y == 55 && x == 85)
					&& (y == 56 && x == 85)
					&& (y == 57 && x == 85)
					&& (y == 58 && x == 85)
					&& (y == 59 && x == 85)
					&& (y == 51 && x == 86)
					&& (y == 52 && x == 86)
					&& (y == 53 && x == 86)
					&& (y == 55 && x == 86)
					&& (y == 56 && x == 86)
					&& (y == 57 && x == 86)
					&& (y == 58 && x == 86)
					&& (y == 62 && x == 79)
					&& (y == 62 && x == 78)
					&& (y == 62 && x == 77)
					&& (y == 62 && x == 76)
					&& (y == 62 && x == 75)
					&& (y == 61 && x == 79)
					&& (y == 61 && x == 78)
					&& (y == 61 && x == 77)
					&& (y == 61 && x == 76)
					&& (y == 61 && x == 75)
					&& (y == 61 && x == 74)
					&& (y == 60 && x == 78)
					&& (y == 60 && x == 77)
					&& (y == 60 && x == 76)
					&& (y == 60 && x == 75)
					&& (y == 60 && x == 74)
					&& (y == 60 && x == 73)
					&& (y == 59 && x == 77)
					&& (y == 59 && x == 76)
					&& (y == 59 && x == 75)
					&& (y == 59 && x == 74)
					)
				{
					if (y == 53 && x == 81)
					{
						int a = 0;
					}
					tile->SetIsWall(true);
					SET_MATERIAL(tile, L"redTile");
					tile->SetSaveMaterial(RESOURCE_FIND(Material, L"redTile"));
				}
				else
				{
					if (y == 53 && x == 81)
					{
						int a = 0;
					}
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