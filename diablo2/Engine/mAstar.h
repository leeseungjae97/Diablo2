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
		//Vector2 bottomLeft;	// ��ü Ÿ���� ���� �ϴ�
		//Vector2 topRight;	// ��ü Ÿ���� ������ ���
		Vector2 startCoord;	// �����ϴ� ��ġ
		Vector2 targetCoord;	// Ÿ�� ��ġ

		int xLength;
		int yLength;

		std::vector<Tile*> finalTileVector;	// ���� ��

		std::vector<Tile*> tileVector;	// ó�� Ÿ�ϵ� �ҷ��� �����ϴ� ��

		Tile* startTile;	// ó�� �����ϴ� ��ġ Ÿ��
		Tile* targetTile;	// Ÿ�� ��ġ Ÿ��
		Tile* curTile;		// ���� ��ġ Ÿ��
		std::vector<Tile*> openVector;	// ��������Ʈ : ���� ���� Ÿ�ϵ�
		std::vector<Tile*> closedVector;	// ��������Ʈ : �� �񱳰� ���� Ÿ�ϵ�
		bool allowDiagonal;				// �밢�� �̵� ���
		bool dontCrossCorner;			// �ڳ� �ǳʰ���.

	};
}

