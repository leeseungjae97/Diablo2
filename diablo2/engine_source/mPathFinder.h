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

		Vector2 mStartCoord;	// �����ϴ� ��ġ
		Vector2 mTargetCoord;	// Ÿ�� ��ġ

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

		int dy;
		int dx;

		float searchTileSize;

		eFinderType mFinderType;
	};
}