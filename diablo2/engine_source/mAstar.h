#pragma once
#include "_Engine.h"
#include "mTileManager.h"

namespace m
{
	class MoveAbleObject;
	class Tile;
	class Astar
	{
	public:
		Astar();
		~Astar();

		void Initialize();
		void PathFinding(Vector2 startCoord, Vector2 targetCoord);
		void OpenVectorAdd(int y, int x);

		bool PathChange();

		bool Move(MoveAbleObject* mOwner);

		void SetXLength(int xLen) { xLength = xLen; }
		void SetYLength(int yLen) { yLength = yLen; }

		std::vector<Tile*>& GetPath() { return finalPathVector; }
		
	private:
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
		std::vector<Tile*> tmpOpenVector;

		bool allowDiagonal;				// �밢�� �̵� ���
		bool dontCrossCorner;			// �ڳ� �ǳʰ���.

	};
}

