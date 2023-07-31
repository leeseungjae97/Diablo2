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
		//Vector2 bottomLeft;	// ��ü Ÿ���� ���� �ϴ�
		//Vector2 topRight;	// ��ü Ÿ���� ������ ���
		static Vector2 mStartCoord;	// �����ϴ� ��ġ
		static Vector2 mTargetCoord;	// Ÿ�� ��ġ

		static int tempCount;
		static int xLength;
		static int yLength;

		static std::vector<Tile*> finalTileVector;	// ���� ��

		static Tile* startTile;	// ó�� �����ϴ� ��ġ Ÿ��
		static Tile* targetTile;	// Ÿ�� ��ġ Ÿ��
		static Tile* curTile;		// ���� ��ġ Ÿ��
		static std::vector<Tile*> openVector;	// ��������Ʈ : ���� ���� Ÿ�ϵ�
		static std::vector<Tile*> closedVector;	// ��������Ʈ : �� �񱳰� ���� Ÿ�ϵ�
		static std::vector<Tile*> tmpOpenVector;
		static bool allowDiagonal;				// �밢�� �̵� ���
		static bool dontCrossCorner;			// �ڳ� �ǳʰ���.

	};
}

