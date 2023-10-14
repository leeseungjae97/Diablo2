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

		Vector2 mStartCoord;	// �����ϴ� ��ġ
		Vector2 mTargetCoord;	// Ÿ�� ��ġ
		Vector2 mDestCoord;

		int xLength;
		int yLength;

		std::vector<Tile*> pathVector;	// ���� ��
		std::vector<Tile*> finalPathVector;

		Tile* startTile;	// ó�� �����ϴ� ��ġ Ÿ��
		Tile* targetTile;	// Ÿ�� ��ġ Ÿ��
		Tile* curTile;		// ���� ��ġ Ÿ��

		std::vector<Tile*> openVector;	// ��������Ʈ : ���� ���� Ÿ�ϵ�
		std::vector<Tile*> closedVector;	// ��������Ʈ : �� �񱳰� ���� Ÿ�ϵ�
		std::vector<int> bfsPathFinderExcept;

		bool allowDiagonal;				// �밢�� �̵� ���
		bool dontCrossCorner;			// �ڳ� �ǳʰ���.

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
