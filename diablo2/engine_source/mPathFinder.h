#pragma once
#include "_Engine.h"
#include "mTileManager.h"

namespace m
{
	class MoveAbleObject;
	class Tile;
	class PathFinder
	{
	public:
		enum class eFinderType
		{
			Astar,
			InSight,
			End,
		};

		PathFinder();
		~PathFinder();

		void AstarPathFinding(Vector2 startCoord, Vector2 targetCoord, float searchSize = -1);
		
		void InSightPathFinding(Vector2 startCoord, Vector2 targetCoord);

		bool PathChange();

		void ClearPath();

		bool MonsterMove(MoveAbleObject* mOwner);
		bool PlayerMove(MoveAbleObject* mOwner);

		void SetXLength(int xLen);
		void SetYLength(int yLen);

		std::vector<Tile*>& GetPath();

		void SetFinderType(eFinderType type) { mFinderType = type; }
	private:
		void openVectorAdd(int y, int x);

		Vector2 mStartCoord;	// 시작하는 위치
		Vector2 mTargetCoord;	// 타겟 위치

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

		int dy;
		int dx;

		float searchTileSize;

		eFinderType mFinderType;
	};
}