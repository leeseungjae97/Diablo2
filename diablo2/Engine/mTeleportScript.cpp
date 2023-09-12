#include "mTeleportScript.h"

#include "../engine_source/mTileManager.h"

#include "mMoveAbleObject.h"
namespace m
{
	TeleportScript::TeleportScript()
	{
		TileManager::playerStandTile;

	}

	TeleportScript::~TeleportScript()
	{
	}

	void TeleportScript::Initialize()
	{
		Script::Initialize();
	}

	void TeleportScript::Update()
	{
		Script::Update();
		if (Input::GetKeyDownOne(eKeyCode::RBUTTON))
		{
			GET_POS(mOwner);

			checkWallIfWallGetNearByCoord();
		}
	}

	void TeleportScript::LateUpdate()
	{
		Script::LateUpdate();
	}

	void TeleportScript::Render()
	{
		Script::Render();
	}

	void TeleportScript::checkWallIfWallGetNearByCoord()
	{
		Vector2 coord = TileManager::GetHoverTileCoord();
		Tile* hoverTile = TileManager::pathFindingTiles[coord.y][coord.x];

		std::vector<Tile*> tileVector;
		if (hoverTile->GetIsWall())
		{
			tileVector.push_back(hoverTile);

			bool find = false;
			//while (!tileVector.empty())
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
			//while (curTile != startTile)
			//{
			//	pathVector.push_back(curTile);
			//	curTile = curTile->GetParentTile();
			//}
			//for (Tile* tile : openVector)
			//	tile->SetParentTile(nullptr);
			//openVector.clear();
		}
	}
}
