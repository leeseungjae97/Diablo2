#pragma once
#include "../Engine/mTile.h"

#include "mTileSystem.h"
namespace m
{
#define TILES std::vector<std::vector<Tile*>>
	class TileManager
	{
	public:
		static void MakeTile(int x, int y, Camera* camera);
		static void TilesUpdate();
		static void Release();
        static void TileIsWallChange();
        static void TileIsWallReset();
		static Vector2 GetHoverTileCoord();
		static Vector2 GetPlayerPositionCoord();
		static Vector3 GetPlayerPosition();

		static TILES pathFindingTiles;
		static Tile* hoverTile;
		static Tile* playerStandTile;

		static int tileXLen;
		static int tileYLen;
		static float tileXSize;
		static float tileYSize;

		static TileSystem* curTileSystem;
	private:
	};
}

