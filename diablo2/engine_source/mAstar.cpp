#include "mAstar.h"

#include "mMeshRenderer.h"
#include "mTileManager.h"

#include "../Engine/mTile.h"
#include "../Engine/mMoveAbleObject.h"

namespace m
{
	Astar::Astar()
	{

	}
	Astar::~Astar()
	{

	}
	void Astar::Initialize()
	{
		allowDiagonal = true;
		dontCrossCorner = false;
		mStartCoord = Vector2(-1.f, -1.f);
		mTargetCoord = Vector2(-1.f, -1.f);
		xLength = 0;
		yLength = 0;
		startTile = nullptr;
		targetTile = nullptr;
		curTile = nullptr;
	}

	void Astar::PathFinding(Vector2 startCoord, Vector2 targetCoord)
	{
		Astar::Initialize();
		Astar::SetYLength(TileManager::tiles.size());
		Astar::SetXLength(TileManager::tiles[0].size());
		for (int i = 0; i < pathVector.size(); ++i)
		{
			Tile* path = pathVector[i];
			SET_MATERIAL(path, L"testTile");
		}
		pathVector.clear();
		float direct1[4][2] = { {1, 1},{1, -1},{-1, -1},{-1, 1} };
		float direct2[4][2] = { {1, 0},{0, 1},{-1, 0},{0, -1} };

		mStartCoord = startCoord;
		mTargetCoord = targetCoord;

		startTile = TileManager::tiles[startCoord.y][startCoord.x];
		targetTile = TileManager::tiles[targetCoord.y][targetCoord.x];

		openVector.push_back(startTile);

		int dy = 0;
		int dx = 0;
		while (!openVector.empty())
		{
			
			curTile = openVector.front();
			for (int i = 1; i < openVector.size(); ++i)
			{
				if (openVector[i]->GetF() <= curTile->GetF()
					&& openVector[i]->GetH() < curTile->GetH())
				{
					//openVector[i]->SetParentTile(curTile);
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
			curTile->SetInOpen(false);

			closedVector.push_back(curTile);
			curTile->SetInClosed(true);
			
			if (curTile == targetTile)
			{
				Tile* targetCurTile = targetTile;
				while (targetCurTile != startTile)
				{
					pathVector.push_back(targetCurTile);
					targetCurTile = targetCurTile->GetParentTile();
				}
				pathVector.push_back(startTile);
				std::reverse(pathVector.begin(), pathVector.end());

			}
			if (allowDiagonal)
			{
				for (int i = 0; i < 4; ++i)
				{
					dy = curTile->GetCoord().y + direct1[i][0];
					dx = curTile->GetCoord().x + direct1[i][1];
					if (dy < 0 || dx < 0 || dy >= yLength || dx >= xLength) continue;
					OpenVectorAdd(dy, dx);
				}
			}

			for (int i = 0; i < 4; ++i)
			{
				dy = curTile->GetCoord().y + direct2[i][0];
				dx = curTile->GetCoord().x + direct2[i][1];
				if (dy < 0 || dx < 0 || dy >= yLength || dx >= xLength) continue;
				OpenVectorAdd(dy, dx);
			}
		}

		for (int i = 0; i < pathVector.size(); ++i)
			SET_MATERIAL(pathVector[i], L"testTile2");

		for (int i = 0; i < closedVector.size(); ++i)
			closedVector[i]->SetInClosed(false);

		for (int i = 0; i < tmpOpenVector.size(); ++i)
			tmpOpenVector[i]->SetInOpen(false);
		openVector.clear();
		closedVector.clear();
		tmpOpenVector.clear();
	}

	void Astar::OpenVectorAdd(int y, int x)
	{
		if (x >= (mTargetCoord.x - 5 < 0 ? 0 : mTargetCoord.x - 5) && x < mTargetCoord.x + 5
			&& y >= (mTargetCoord.y - 5 < 0 ? 0 : mTargetCoord.y - 5) && y < mTargetCoord.y + 5
			&& !TileManager::tiles[y][x]->GetIsWall()
			&& !TileManager::tiles[y][x]->GetInClosed())
		{
			if (allowDiagonal)
			{
				if (TileManager::tiles[curTile->GetCoord().y][x]->GetIsWall()
					&& TileManager::tiles[y][curTile->GetCoord().x]->GetIsWall()) return;
			}
			if (dontCrossCorner)
			{
				if (TileManager::tiles[y][curTile->GetCoord().x]->GetIsWall()
					|| TileManager::tiles[curTile->GetCoord().y][x]->GetIsWall()) return;
			}
			Tile* neighborTile = TileManager::tiles[y][x];
			int moveCost = curTile->GetG() + (curTile->GetCoord().x - x == 0
											  || curTile->GetCoord().y - y == 0 ? 10 : 14);

			if (moveCost < neighborTile->GetG()
				|| !neighborTile->GetInOpen())
			{
				neighborTile->SetG(moveCost);
				neighborTile->SetH((abs(neighborTile->GetCoord().x - targetTile->GetCoord().x)
									+ abs(neighborTile->GetCoord().y - targetTile->GetCoord().y)) * 10);
				neighborTile->SetParentTile(curTile);

				neighborTile->SetInOpen(true);
				openVector.push_back(neighborTile);
				tmpOpenVector.push_back(neighborTile);
			}
		}
	}

	void Astar::PathChange()
	{
		finalPathVector = pathVector;
		if (!finalPathVector.empty())
		{
			Tile* eraseFrontTile = finalPathVector.front();
			std::vector<Tile*>::iterator iter = finalPathVector.begin();
			while (iter != finalPathVector.end())
			{
				if ((*iter) == eraseFrontTile)
				{
					iter = finalPathVector.erase(iter);
					break;
				}
				else iter++;
			}
		}
		
	}

	void Astar::Move(MoveAbleObject* mOwner)
	{
		if (finalPathVector.empty()) return;

		for (Tile* tile : finalPathVector) SET_MATERIAL(tile, L"testTile2");

		Tile* subTargetTile = finalPathVector.front();
		if (subTargetTile->GetCoord() != TileManager::GetPlayerPositionCoord())
		{
			Vector3 subPos = GET_POS(subTargetTile);

			Vector3 prevPosition = GET_POS(mOwner);
			Vector3 destPosition = subPos;
			mOwner->SetPrevPosition(prevPosition);
			mOwner->SetDestPosition(subPos);

			float maxX = max(destPosition.x, prevPosition.x);
			float maxY = max(destPosition.y, prevPosition.y);

			float minX = min(destPosition.x, prevPosition.x);
			float minY = min(destPosition.y, prevPosition.y);

			mOwner->SetStartDistance((Vector2(maxX, maxY) - Vector2(minX, minY)).Length());

			Vector3 vDirection = destPosition - prevPosition;
			vDirection.Normalize();
			mOwner->SetDirection(vDirection);
			
		}
		if (mOwner->Stop())
		{
			std::vector<Tile*>::iterator iter = finalPathVector.begin();
			while (iter != finalPathVector.end())
			{
				if ((*iter) == subTargetTile)
				{
					iter = finalPathVector.erase(iter);
					break;
				}
				else iter++;
			}
		}

		

	}

	
}