#include "mAstar.h"

#include "mMeshRenderer.h"
#include "mTileManager.h"

#include "../Engine/mMoveAbleObject.h"

namespace m
{
	Astar::Astar()
		: searchTileSize(20)
	{

	}
	Astar::~Astar()
	{

	}
	void Astar::Initialize()
	{
		allowDiagonal = false;
		dontCrossCorner = true;
		mStartCoord = Vector2(-1.f, -1.f);
		mTargetCoord = Vector2(-1.f, -1.f);
		xLength = 0;
		yLength = 0;
		startTile = nullptr;
		targetTile = nullptr;
		curTile = nullptr;
	}

	void Astar::PathFinding(Vector2 startCoord, Vector2 targetCoord, float searchSize)
	{
		Astar::Initialize();
		if (TileManager::tiles[targetCoord.y][targetCoord.x]->GetIsWall()) return;
		for (int i = 0; i < pathVector.size(); ++i)
		{
			Tile* path = pathVector[i];
			SET_MATERIAL(path, L"greenTile");
			path->SetCulled(true);
		}
		if (mStartCoord == startCoord
			&&
			mTargetCoord == targetCoord)
			return;

		if (searchSize == -1)
			searchTileSize = max(fabs(targetCoord.x - startCoord.x), fabs(targetCoord.y - startCoord.y));
		else searchTileSize = searchSize;

		yLength = TileManager::tiles.size();
		xLength = TileManager::tiles[0].size();

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

			std::erase(openVector, curTile);
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
			pathVector[i]->SetCulled(false);

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
		if (x >= (mTargetCoord.x - searchTileSize < 0 ? 0 : mTargetCoord.x - searchTileSize)
			&& x < mTargetCoord.x + searchTileSize
			&& y >= (mTargetCoord.y - searchTileSize < 0 ? 0 : mTargetCoord.y - searchTileSize)
			&& y < mTargetCoord.y + searchTileSize
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

	bool Astar::PathChange()
	{
		finalPathVector = pathVector;
		if (!finalPathVector.empty())
		{
			std::erase(finalPathVector, finalPathVector.front());
			if (finalPathVector.empty()) return false;
			return true;
		}
		return false;

	}
	bool Astar::MonsterMove(MoveAbleObject* mOwner)
	{
		if (finalPathVector.empty()) return false;

		//for (Tile* tile : finalPathVector) SET_MATERIAL(tile, L"greenTile");

		Tile* subTargetTile = finalPathVector.front();
		if (subTargetTile->GetCoord() != mOwner->GetCoord())
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
		else
		{
			//for (Tile* tile : finalPathVector) SET_MATERIAL(tile, L"greenTile");
			std::erase(finalPathVector, finalPathVector.front());
		}
		return true;
	}
	void Astar::ClearPath()
	{
		finalPathVector.clear();
		pathVector.clear();
	}
	bool Astar::PlayerMove(MoveAbleObject* mOwner)
	{
		if (finalPathVector.empty()) return false;

		//for (Tile* tile : finalPathVector) SET_MATERIAL(tile, L"greenTile");

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
		else
		{
			//for (Tile* tile : finalPathVector) SET_MATERIAL(tile, L"greenTile");
			//for (Tile* tile : finalPathVector) tile->SetCulled(false);
			std::erase(finalPathVector, finalPathVector.front());
		}
		return true;
	}


}