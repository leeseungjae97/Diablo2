#pragma once
#include "_Engine.h"
#include "mTileManager.h"
//#include "mPathFinderSystem.h"
#include "mTileDrawSystem.h"

namespace m
{
	class MoveAbleObject;
	class Tile;
	class PathFinder
	{
	public:

		PathFinder();
		~PathFinder();

		void Release();

		void AstarPathFinding(Vector2 startCoord, Vector2 targetCoord, float searchSize = -1, bool forceRebuild = false);

		void InSightPathFinding(Vector2 startCoord, Vector2 targetCoord);

		bool PathChange(bool moveAdjacent = false);

		void ClearPath();

		bool MonsterMove(Monster* mOwner);
		bool PlayerMove(MoveAbleObject* mOwner);

		void SetXLength(int xLen) { xLength = xLen; }
		void SetYLength(int yLen) { yLength = yLen; }
		std::vector<Tile*>& GetPath() { return finalPathVector; }

		void SetMonsterOwner(Monster* mon) { mMonsterOwner = mon; }
		Vector2 GetTargetCoord() { return mTargetCoord; }
		Vector2 GetDestCoord() { return mDestCoord; }

	private:
		void openVectorAdd(int y, int x);

		Vector2 mStartCoord;    // start coord
		Vector2 mTargetCoord;    // target coord
		Vector2 mDestCoord;

		int xLength;
		int yLength;

		std::vector<Tile*> pathVector;    // searched path
		std::vector<Tile*> finalPathVector;

		Tile* startTile;    // start tile
		Tile* targetTile;    // target tile
		Tile* curTile;        // current tile

		std::vector<Tile*> openVector;    // open list
		std::vector<Tile*> closedVector;    // closed list
		std::vector<int> bfsPathFinderExcept;

		bool allowDiagonal;                // allow diagonal move
		bool dontCrossCorner;            // block corner cutting

		float direct1[4][2];
		float direct2[4][2];
		float direct[8][2];

		int dy;
		int dx;
		int dy2;
		int dx2;

		float searchTileSize;

		Monster* mMonsterOwner;

		//PathFinderSystem* mPFSS;
		TileDrawSystem* mTDS;
		GameObject* mDrawPathTileObject;
	};
}
