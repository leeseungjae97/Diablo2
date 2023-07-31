#pragma once
#include "_Engine.h"
#include "mTileManager.h"

namespace m
{
	class Tile;
	class Astar
	{
	public:

		static void Initialize();
		static void PathFinding(Vector2 startCoord, Vector2 targetCoord);

		static void SetXLength(int xLen) { xLength = xLen; }
		static void SetYLength(int yLen) { yLength = yLen; }
		static void OpenVectorAdd(int y, int x);
	private:
		//Vector2 bottomLeft;	// 전체 타일의 왼쪽 하단
		//Vector2 topRight;	// 전체 타일의 오른쪽 상단
		static Vector2 mStartCoord;	// 시작하는 위치
		static Vector2 mTargetCoord;	// 타겟 위치

		static int tempCount;
		static int xLength;
		static int yLength;

		static std::vector<Tile*> finalTileVector;	// 최종 길

		static Tile* startTile;	// 처음 시작하는 위치 타일
		static Tile* targetTile;	// 타겟 위치 타일
		static Tile* curTile;		// 현재 위치 타일
		static std::vector<Tile*> openVector;	// 열린리스트 : 값을 비교할 타일들
		static std::vector<Tile*> closedVector;	// 닫힌리스트 : 값 비교가 끝난 타일들
		static std::vector<Tile*> tmpOpenVector;
		static bool allowDiagonal;				// 대각선 이동 허용
		static bool dontCrossCorner;			// 코너 건너가기.

	};
}

