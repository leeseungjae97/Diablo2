#pragma once
namespace m
{
	class InvenItem;
	class PlayerInfo
	{
	public:
		static int skillPoint;
		static float hp;
		static float hpCapacity;
		static float hpPercent;
		static float mp;
		static int learnedSkill[3][10];

		static std::vector<InvenItem*> inventoryItems;
		static std::vector<InvenItem*> pocketPosions;

		static void PocketToInventory(InvenItem* item);
		static void InventoryToPocket(InvenItem* item);
		static void CalHpPercent();
		static void Initialize();
	private:
		
	};
}

