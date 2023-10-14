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

		void AstarPathFinding(Vector2 startCoord, Vector2 targetCoord, float searchSize = -1);

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

		Vector2 mStartCoord;	// 시작하는 위치
		Vector2 mTargetCoord;	// 타겟 위치
		Vector2 mDestCoord;

		int xLength;
		int yLength;

		std::vector<Tile*> pathVector;	// 최종 길
		std::vector<Tile*> finalPathVector;

		Tile* startTile;	// 처음 시작하는 위치 타일
		Tile* targetTile;	// 타겟 위치 타일
		Tile* curTile;		// 현재 위치 타일

		std::vector<Tile*> openVector;	// 열린리스트 : 값을 비교할 타일들
		std::vector<Tile*> closedVector;	// 닫힌리스트 : 값 비교가 끝난 타일들
		std::vector<int> bfsPathFinderExcept;

		bool allowDiagonal;				// 대각선 이동 허용
		bool dontCrossCorner;			// 코너 건너가기.

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
