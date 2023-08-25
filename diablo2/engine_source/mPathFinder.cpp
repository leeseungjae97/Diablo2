#include "mPathFinder.h"

#include "mMeshRenderer.h"
#include "mTileManager.h"
#include "mTileSystem.h"
#include "mMonsterManager.h"
#include "mTileSystem.h"

#include "../Engine/mMoveAbleObject.h"
namespace m
{
	PathFinder::PathFinder()
		: mStartCoord(Vector2::Zero)
		, mTargetCoord(Vector2::Zero)
		, xLength(0)
		, yLength(0)
		, startTile(nullptr)
		, targetTile(nullptr)
		, curTile(nullptr)
		, allowDiagonal(true)
		, dontCrossCorner(true)
		, direct1{ { 1, 1 }, { 1, -1 }, { -1, -1 }, { -1,  1 } }
		, direct2{ { 1, 0 }, { 0,  1 }, { -1,  0 }, {  0, -1 } }
		, direct
			{{ 1, 1 }, { 1, -1 }, { -1, -1 }, { -1,  1 }
			,  { 1, 0 }, { 0,  1 }, { -1,  0 }, {  0, -1 }}
		, dy(0)
		, dx(0)
		, searchTileSize(20)
	{
		bfsPathFinderExcept.reserve(5);
		finalPathVector.reserve(300);
		pathVector.reserve(300);
		int capa = 1000;
		if (!TileManager::pathFindingTiles.empty()) capa = TileManager::pathFindingTiles.size() * TileManager::pathFindingTiles[0].size();
		openVector.reserve(capa);
		closedVector.reserve(capa);

		yLength = TileManager::pathFindingTiles.size();
		xLength = TileManager::pathFindingTiles[0].size();


	}
	PathFinder::~PathFinder()
	{
		pathVector.clear();
		finalPathVector.clear();
		openVector.clear();
		closedVector.clear();
		startTile = nullptr;
		targetTile = nullptr;
		curTile = nullptr;
	}

	void PathFinder::AstarPathFinding(Vector2 startCoord, Vector2 targetCoord, float searchSize)
	{
		if (TileManager::pathFindingTiles[targetCoord.y][targetCoord.x]->GetIsWall()) return;
		if (TileManager::pathFindingTiles[startCoord.y][startCoord.x]->GetIsWall()) return;
		//if (TileManager::pathFindingTiles[targetCoord.y][targetCoord.x]->GetOnMonster()) return;

		if(nullptr == mMonsterOwner)
		{
			if (mStartCoord == startCoord && mTargetCoord == targetCoord) return;
		}
		else
		{
			if (mMonsterOwner->GetPathChange() == false
				&& mStartCoord == startCoord 
				&& mTargetCoord == targetCoord)
			{
				return;
			}
		}
		
		mStartCoord = startCoord;
		mTargetCoord = targetCoord;

		if (searchSize == -1)
			searchTileSize = fabs(mTargetCoord.x - mStartCoord.x) + fabs(mTargetCoord.y - mStartCoord.y);
		else searchTileSize = searchSize;

		pathVector.clear();

		

		startTile = TileManager::pathFindingTiles[mStartCoord.y][mStartCoord.x];
		targetTile = TileManager::pathFindingTiles[mTargetCoord.y][mTargetCoord.x];

		openVector.push_back(startTile);
		int i;
		while (!openVector.empty())
		{
			curTile = openVector.front();
			for (i = 1; i < openVector.size(); ++i)
			{
				if (openVector[i]->GetF() <= curTile->GetF()
					&& openVector[i]->GetH() < curTile->GetH())
				{
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
				std::ranges::reverse(pathVector);

			}
			if (allowDiagonal)
			{
				for (i = 0; i < 4; ++i)
				{
					dy = static_cast<int>(curTile->GetCoord().y + direct1[i][0]);
					dx = static_cast<int>(curTile->GetCoord().x + direct1[i][1]);
					if (dy < 0 || dx < 0 || dy >= yLength || dx >= xLength) continue;
					openVectorAdd(dy, dx);
				}
			}
			for (i = 0; i < 4; ++i)
			{
				dy = curTile->GetCoord().y + direct2[i][0];
				dx = curTile->GetCoord().x + direct2[i][1];
				if (dy < 0 || dx < 0 || dy >= yLength || dx >= xLength) continue;
				openVectorAdd(dy, dx);
			}
		}

		for (Tile* path : pathVector)
		{
			path->SetInOpen(false);
			path->SetParentTile(nullptr);
		}
		
		for (Tile* path : closedVector)
		{
			path->SetInClosed(false);
			path->SetParentTile(nullptr);
		}
		for (Tile* path : openVector)
		{
			path->SetParentTile(nullptr);
		}
		openVector.clear();
		closedVector.clear();
	}

	void PathFinder::openVectorAdd(int y, int x)
	{
		if (mMonsterOwner
			&& mMonsterOwner->GetNextMoveCoord() == Vector2(x, y)
			&& TileManager::pathFindingTiles[y][x]->GetMonsterNext() != 0)
			return;
		if (x >= (mTargetCoord.x - searchTileSize < 0 ? 0 : mTargetCoord.x - searchTileSize)
			&& x < mTargetCoord.x + searchTileSize
			&& y >= (mTargetCoord.y - searchTileSize < 0 ? 0 : mTargetCoord.y - searchTileSize)
			&& y < mTargetCoord.y + searchTileSize
			&& !TileManager::pathFindingTiles[y][x]->GetIsWall()
			&& !TileManager::pathFindingTiles[y][x]->GetOnMonster()
			&& !TileManager::pathFindingTiles[y][x]->GetInClosed())
		{

			if (allowDiagonal)
			{
				if (TileManager::pathFindingTiles[curTile->GetCoord().y][x]->GetIsWall()
					&& TileManager::pathFindingTiles[y][curTile->GetCoord().x]->GetIsWall()) return;
			}
			if (dontCrossCorner)
			{
				if (TileManager::pathFindingTiles[y][curTile->GetCoord().x]->GetIsWall()
					|| TileManager::pathFindingTiles[curTile->GetCoord().y][x]->GetIsWall()) return;
			}
			Tile* neighborTile = TileManager::pathFindingTiles[y][x];
			int moveCost = curTile->GetG()
						 + (curTile->GetCoord().x - x == 0 
						 || curTile->GetCoord().y - y == 0 ? 10 : 14);

			if (moveCost < neighborTile->GetG() || !neighborTile->GetInOpen())
			{
				neighborTile->SetG(moveCost);
				neighborTile->SetH((abs(neighborTile->GetCoord().x - targetTile->GetCoord().x)
									+ abs(neighborTile->GetCoord().y - targetTile->GetCoord().y)) * 10);
				neighborTile->SetParentTile(curTile);

				neighborTile->SetInOpen(true);
				openVector.push_back(neighborTile);
			}
		}
	}
	void PathFinder::InSightPathFinding(Vector2 startCoord, Vector2 targetCoord)
	{
		//if (TileManager::pathFindingTiles[targetCoord.y][targetCoord.x]->GetIsWall()) return;
		//if (TileManager::pathFindingTiles[startCoord.y][startCoord.x]->GetIsWall()) return;

		//if (mStartCoord == startCoord
		//	&&
		//	mTargetCoord == targetCoord)
		//	return;

		//pathVector.clear();

		//mStartCoord = startCoord;
		//mTargetCoord = targetCoord;

		//startTile = TileManager::pathFindingTiles[startCoord.y][startCoord.x];
		//targetTile = TileManager::pathFindingTiles[targetCoord.y][targetCoord.x];

		//openVector.push_back(startTile);

		//bool find = false;
		//while(!openVector.empty())
		//{
		//	curTile = openVector.front();
		//	Vector2 curCoord = curTile->GetCoord();
		//	std::erase(openVector, curTile);

		//	if (abs(mStartCoord.x - curCoord.x) > 10) continue;
		//	if (abs(mStartCoord.y - curCoord.y) > 10) continue;

		//	bfsPathFinderExcept.clear();

		//	if (curCoord.x > targetCoord.x)
		//		bfsPathFinderExcept.push_back(2); // {-1, 0}
		//	else if (curCoord.x < targetCoord.x)
		//		bfsPathFinderExcept.push_back(0); // {1, 0}
		//	if (curCoord.y > targetCoord.y)
		//		bfsPathFinderExcept.push_back(3); // {0, -1}
		//	else if (curCoord.y < targetCoord.y)
		//		bfsPathFinderExcept.push_back(1); // {0, 1}

		//	if (bfsPathFinderExcept.size() == 0)
		//		break;

		//	for (int i = 0; i < bfsPathFinderExcept.size(); ++i)
		//	{
		//		dx = curTile->GetCoord().x + direct2[bfsPathFinderExcept[i]][0];
		//		dy = curTile->GetCoord().y + direct2[bfsPathFinderExcept[i]][1];

		//		if (dy < 0 || dx < 0 || dy >= yLength || dx >= xLength) continue;
		//		Tile* tile = TileManager::pathFindingTiles[dy][dx];
		//		if (tile->GetIsWall()) continue;
		//		if (tile->GetOnMonster()) continue;
		//		if (tile->GetMonsterNext() != 0) continue;
		//		tile->SetParentTile(curTile);
		//		openVector.push_back(tile);
		//		if (tile == targetTile)
		//		{
		//			find = true;
		//			break;
		//		}
		//	}
		//	if (find) break;
		//}
		//while(curTile != startTile)
		//{
		//	pathVector.push_back(curTile);
		//	curTile = curTile->GetParentTile();
		//}
		//for (Tile* tile : openVector)
		//	tile->SetParentTile(nullptr);
		//openVector.clear();
	}

	bool PathFinder::PathChange(bool moveAdjacent)
	{
		finalPathVector = pathVector;
		if (!finalPathVector.empty())
		{
			std::erase(finalPathVector, finalPathVector.front());
			if(moveAdjacent)
			{
				if (!finalPathVector.empty())
					finalPathVector.pop_back();
			}
			if (mMonsterOwner)
			{
				if (!finalPathVector.empty()) mMonsterOwner->PathChange(true);
				else mMonsterOwner->PathChange(false);
			}
			if (finalPathVector.empty()) return false;

			return true;
		}
		return false;

	}
	bool PathFinder::MonsterMove(Monster* mOwner)
	{
		if (finalPathVector.empty()) return false;

		Tile* subTargetTile = finalPathVector.front();
		mOwner->SetNextMoveCoord(subTargetTile->GetCoord());
		subTargetTile->SetMonsterNext();

		if (subTargetTile->GetCoord() != mOwner->GetCoord())
		{
			if (subTargetTile->GetOnMonster())
			{
				subTargetTile->UnSetMonsterNext();
				ClearPath();
				return false;
			}

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
			subTargetTile->UnSetMonsterNext();
			std::erase(finalPathVector, finalPathVector.front());
		}
		return true;
	}
	void PathFinder::ClearPath()
	{
		for(int i = 0 ; i < finalPathVector.size() ;++i)
		{
			finalPathVector[i]->SetOnMonster(false);
			//finalPathVector[i]->SetMonsterNext(false);
		}
		for(int i = 0 ; i < pathVector.size(); ++i)
		{
			pathVector[i]->SetOnMonster(false);
			//pathVector[i]->SetMonsterNext(false);
		}
		finalPathVector.clear();
		pathVector.clear();
	}
	bool PathFinder::PlayerMove(MoveAbleObject* mOwner)
	{
		if (finalPathVector.empty()) return false;

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
			std::erase(finalPathVector, finalPathVector.front());
		}
		return true;
	}
}
