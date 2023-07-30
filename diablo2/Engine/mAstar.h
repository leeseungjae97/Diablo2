#pragma once
#include "_Engine.h"

namespace m
{
	class Tile;
	class Astar
	{
	public:
		Astar();
		~Astar();

		void Initialize();
		void PathFinding(Vector2 startCoord, Vector2 targetCoord);
		
		void SetXLength(int xLen) { xLength = xLen; }
		void SetYLength(int yLen) { yLength = yLen; }
		void SetTiles(std::vector<Tile*> tiles) { tileVector = tiles; }
		void OpenVectorAdd(int x, int y);
	private:
		//Vector2 bottomLeft;	// 전체 타일의 왼쪽 하단
		//Vector2 topRight;	// 전체 타일의 오른쪽 상단
		Vector2 startCoord;	// 시작하는 위치
		Vector2 targetCoord;	// 타겟 위치

		int xLength;
		int yLength;

		std::vector<Tile*> finalTileVector;	// 최종 길

		std::vector<Tile*> tileVector;	// 처음 타일들 불러와 저장하는 곳

		Tile* startTile;	// 처음 시작하는 위치 타일
		Tile* targetTile;	// 타겟 위치 타일
		Tile* curTile;		// 현재 위치 타일
		std::vector<Tile*> openVector;	// 열린리스트 : 값을 비교할 타일들
		std::vector<Tile*> closedVector;	// 닫힌리스트 : 값 비교가 끝난 타일들
		bool allowDiagonal;				// 대각선 이동 허용
		bool dontCrossCorner;			// 코너 건너가기.

	};
}

