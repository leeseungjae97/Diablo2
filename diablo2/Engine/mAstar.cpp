#include "mAstar.h"

#include "mTile.h"
namespace m
{
	Astar::Astar()
		: allowDiagonal(true)
		, dontCrossCorner(false)
		//, bottomLeft(Vector2(-1.f, -1.f))
		//, topRight(Vector2(-1.f, -1.f))
		, startCoord(Vector2(-1.f, -1.f))
		, targetCoord(Vector2(-1.f, -1.f))
	{

	}
	Astar::~Astar()
	{
	}
	void Astar::Initialize()
	{

	}
	void Astar::PathFinding(Vector2 startCoord, Vector2 targetCoord)
	{
		startTile = tileVector[startCoord.y * 10 + startCoord.x];
		targetTile = tileVector[targetCoord.y * 10 + targetCoord.x];

		openVector.push_back(startTile);

		while (!openVector.empty())
		{
			curTile = openVector.front();
			for (int i = 1; i < openVector.size(); ++i)
			{
				if (openVector[i]->GetF() <= curTile->GetF()
					&& openVector[i]->GetH() < curTile->GetH())
				{
					openVector[i]->SetParentTile(curTile);
					curTile = openVector[i];
				}
			}

			std::vector<Tile*>::iterator iter = openVector.begin();
			while (iter != openVector.end())
			{
				if ((*iter) == curTile)
				{
					iter = openVector.erase(iter);
					break;
				}
				else iter++;
			}
			closedVector.push_back(curTile);

			if (curTile == targetTile)
			{
				Tile* targetCurTile = targetTile;
				while (targetCurTile != startTile)
				{
					finalTileVector.push_back(targetCurTile);
					targetCurTile = targetCurTile->GetParentTile();
				}
				finalTileVector.push_back(startTile);
				
			}
		}
	}
	void Astar::OpenVectorAdd(int x, int y)
	{
		if (x >= 0 && x < xLength
			&& y >= 0 && y < yLength
			&& !tileVector[y * 10 + x]->GetIsWall())
		{
			
		}
	}
}