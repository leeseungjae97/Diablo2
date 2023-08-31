#include "mStashManager.h"
#include "mMouseManager.h"

#include "../Engine/mItem.h"

namespace m
{
	std::vector<StashManager::Stash> StashManager::stashPositions;
	Camera* StashManager::mCurCamera = nullptr;
	StashManager::eStashType StashManager::GetHoverStashType()
	{
		Vector3 mousePosV3 = MouseManager::UnprojectionMousePos(-1.f, mCurCamera);
		Vector2 mousePosV2 = Vector2(mousePosV3.x, mousePosV3.y);

		for (Stash stash : stashPositions)
		{
			Vector2 sPos = stash.pos;
			Vector2 sSize = stash.size;
			if (Vector2::PointIntersectRect(sPos, sSize, mousePosV2))
			{
				return stash.type;
			}
		}
		return eStashType::End;
	}

	void StashManager::AddStash(Vector2 pos, Vector2 size, eStashType type)
	{
		stashPositions.push_back({ pos, size, type });
	}

	bool StashManager::StashItem(Item* item)
	{
		eStashType prevStashType = item->GetStashType();


		eStashType type = GetHoverStashType();
		if (type == eStashType::End) return false;
		eItemType type2 = item->GetItemType();

		switch (type)
		{
		case eStashType::Invetory:
		{
		}
		break;
		case eStashType::PocketInven:
		{
			if (type2 != eItemType::Posion) return false;



			int a = 0;
		}
		break;
		case eStashType::Shop:
		{

		}
		break;
		default:
		{

		}
		break;
		}

		return true;
	}
}
