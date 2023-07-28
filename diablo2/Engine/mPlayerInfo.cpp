#include "mPlayerInfo.h"
#include "mInvenItem.h"

namespace m
{
	int PlayerInfo::learnedSkill[3][10]= {};
	int PlayerInfo::skillPoint = 0;
	std::vector<InvenItem*> PlayerInfo::inventoryItems;
	std::vector<InvenItem*> PlayerInfo::pocketPosions;

	void PlayerInfo::PocketToInventory(InvenItem* item)
	{
		std::vector<InvenItem*>::iterator iter = pocketPosions.begin();

		while (iter != pocketPosions.end())
		{
			if( (*(iter)) != item)
				iter++;
			else
				iter = pocketPosions.erase(iter);
		}
		inventoryItems.push_back(item);
	}
	void PlayerInfo::InventoryToPocket(InvenItem* item)
	{
		std::vector<InvenItem*>::iterator iter = inventoryItems.begin();

		while (iter != inventoryItems.end())
		{
			if ((*(iter)) != item)
				iter++;
			else
				iter = inventoryItems.erase(iter);
		}
		pocketPosions.push_back(item);
	}
	void PlayerInfo::Initialize()
	{
		skillPoint = 100;
	}
}