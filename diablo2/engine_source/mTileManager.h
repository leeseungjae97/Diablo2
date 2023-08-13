#pragma once
#include "../Engine/mTile.h"
namespace m
{
#define TILES std::vector<std::vector<Tile*>>
	class TileManager
	{
	public:
		static void MakeTile(int x, int y, Camera* camera);
		static Vector2 GetHoverTileCoord();
		static Vector2 GetPlayerPositionCoord();

		static TILES tiles;
		static Tile* hoverTile;
		static Tile* playerStandTile;

		static int tileXLen;
		static int tileYLen;
		static float tileXSize;
		static float tileYSize;
		//static float iniX;
		//static float iniY;
	private:
	};
}

