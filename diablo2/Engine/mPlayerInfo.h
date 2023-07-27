#pragma once
namespace m
{
	class InvenItem;
	class PlayerInfo
	{
	public:
		static int skillPoint;

		static int learnedSkill[3][10];

		static std::vector<InvenItem*> inventoryItems;
		static std::vector<InvenItem*> pocketPosions;

		static void PocketToInventory(InvenItem* item);
		static void InventoryToPocket(InvenItem* item);
		static void Initialize();
	private:
		
	};
}

