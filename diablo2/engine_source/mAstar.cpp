#include "mAstar.h"

#include "mMeshRenderer.h"
#include "mTileManager.h"
#include "../Engine/mTile.h"
namespace m
{
	Vector2 Astar::mStartCoord = Vector2(-1.f, -1.f);
	Vector2 Astar::mTargetCoord = Vector2(-1.f, -1.f);

	int Astar::xLength = 0;
	int Astar::yLength = 0;

	std::vector<Tile*> Astar::finalTileVector;

	Tile* Astar::startTile = nullptr;
	Tile* Astar::targetTile = nullptr;
	Tile* Astar::curTile = nullptr;
	std::vector<Tile*> Astar::openVector;
	std::vector<Tile*> Astar::closedVector;
	std::vector<Tile*> Astar::tmpOpenVector;
	bool Astar::allowDiagonal = false;
	bool Astar::dontCrossCorner = false;
	int Astar::tempCount = 0;
	void Astar::Initialize()
	{
		allowDiagonal = false;
		dontCrossCorner = false;
		mStartCoord = Vector2(-1.f, -1.f);
		mTargetCoord = Vector2(-1.f, -1.f);
	}
	void Astar::PathFinding(Vector2 startCoord, Vector2 targetCoord)
	{
		
		
		TILES tileVec = TileManager::tiles;

		Astar::Initialize();
		Astar::SetYLength(tileVec.size());
		Astar::SetXLength(tileVec[0].size());
		for (int i = 0; i < finalTileVector.size(); ++i)
		{
			Tile* path = finalTileVector[i];
			SET_MATERIAL(path, L"testTile");
		}
		finalTileVector.clear();
		float direct1[4][2] = { {1, 1},{1, -1},{-1, -1},{-1, 1} };
		float direct2[4][2] = { {1, 0},{0, 1},{-1, 0},{0, -1} };

		mStartCoord = startCoord;
		mTargetCoord = targetCoord;

		startTile = tileVec[startCoord.y][startCoord.x];
		targetTile = tileVec[targetCoord.y][targetCoord.x];

		openVector.push_back(startTile);

		int dy = 0;
		int dx = 0;
		auto start_time = std::chrono::high_resolution_clock::now();
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
					finalTileVector.push_back(targetCurTile);
					targetCurTile = targetCurTile->GetParentTile();
				}
				finalTileVector.push_back(startTile);
				std::reverse(finalTileVector.begin(), finalTileVector.end());

			}
			tempCount++;
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
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
		

		for (int i = 0; i < finalTileVector.size(); ++i)
			SET_MATERIAL(finalTileVector[i], L"testTile2");

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
		TILES tileVec = TileManager::tiles;		
		if (x >= (mTargetCoord.x - 10 < 0 ? 0 : mTargetCoord.x - 10) && x < mTargetCoord.x + 10
			&& y >= (mTargetCoord.y - 10 < 0 ? 0 : mTargetCoord.y - 10) && y < mTargetCoord.y + 10
			&& !tileVec[y][x]->GetIsWall()
			&& !tileVec[y][x]->GetInClosed())
		{
			if (allowDiagonal)
			{
				if (tileVec[curTile->GetCoord().y][x]->GetIsWall()
					&& tileVec[y][curTile->GetCoord().x]->GetIsWall()) return;
			}
			if (dontCrossCorner)
			{
				if (tileVec[y][curTile->GetCoord().x]->GetIsWall()
					|| tileVec[curTile->GetCoord().y][x]->GetIsWall()) return;
			}
			Tile* neighborTile = tileVec[y][x];
			int moveCost = curTile->GetG() + (curTile->GetCoord().x - x == 0
											  || curTile->GetCoord().y - y == 0 ? 10 : 14);


			if (moveCost < neighborTile->GetG()
				|| /*std::find(openVector.begin(), openVector.end(), neighborTile) == openVector.end()*/
				!neighborTile->GetInOpen())
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
}