#include "mPlayerInfo.h"

#include "../engine_source/mTileManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mAnimator.h"

#include "mInvenItem.h"
#include "mPlayer.h"

namespace m
{
	int PlayerInfo::learnedSkill[3][10]= {};
	int PlayerInfo::skillPoint = 0;
	float PlayerInfo::hp = 100.f;
	float PlayerInfo::hpCapacity = 100.f;
	float PlayerInfo::hpPercent = 1.f;
	float PlayerInfo::mp = 100.f;

	Player* PlayerInfo::player = nullptr;
	eSkillType PlayerInfo::skillTypes[2] = {};

	std::vector<InvenItem*> PlayerInfo::inventoryItems;
	std::vector<InvenItem*> PlayerInfo::pocketPosions;
	void PlayerInfo::Initialize()
	{
		skillPoint = 100;
		player = new Player(GET_POS(TileManager::tiles[0][0]));
		//SET_MAIN_CAMERA(player);
		//AddGameObject(eLayerType::Player, player);
		SET_MESH(player, L"RectMesh");
		SET_MATERIAL(player, L"AnimationMaterial");
		SET_SCALE_XYZ(player, 48.f, 74.f, 1.f);
		ADD_COMP(player, Animator);
		SetSkill(0, eSkillType::normalAttack);
		SetSkill(1, eSkillType::lightning);
	}

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

	void PlayerInfo::CalHpPercent()
	{
		hpPercent = (hpCapacity - hp) / hpCapacity;
	}

	eSkillType PlayerInfo::GetSkill(int num)
	{
		if (num > 2) return eSkillType::END;

		return skillTypes[num];
	}

	void PlayerInfo::SetSkill(int num, eSkillType type)
	{
		if (num > 2) return;

		skillTypes[num] = type;
	}

	eSkillType PlayerInfo::SetColdSkillType(eColdSkillType type)
	{
		return (eSkillType)type;
	}

	eSkillType PlayerInfo::SetFireSkillType(eFireSkillType type)
	{
		return (eSkillType)((UINT)type + (UINT)eSkillType::coldMastery);
	}

	eSkillType PlayerInfo::SetLightningSkillType(eLightningSkillType type)
	{
		return (eSkillType)((UINT)type + (UINT)eSkillType::lightningMastery);
	}
}