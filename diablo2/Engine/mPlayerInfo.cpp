#include "mPlayerInfo.h"

#include "../engine_source/mTileManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mAnimator.h"

#include "mInvenItem.h"
#include "mPlayer.h"
#include "mOverlayEffectSkillScript.h"
namespace m
{
	int PlayerInfo::learnedSkill[3][10]= {};
	int PlayerInfo::skillPoint = 0;
	float PlayerInfo::hp = 100.f;
	float PlayerInfo::hpCapacity = 100.f;
	float PlayerInfo::hpPercent = 1.f;
	float PlayerInfo::mp = 100.f;
	float PlayerInfo::mpCapacity = 100.f;
	float PlayerInfo::mpPercent = 1.f;

	Player* PlayerInfo::player = nullptr;
	eSkillType PlayerInfo::skillTypes[2] = {};

	void PlayerInfo::Initialize()
	{
		skillPoint = 100;
		Tile* tile2 = TileManager::pathFindingTiles[60][10];
		Vector3 pos2 = GET_POS(tile2);

		player = new Player(pos2);
		//SET_MAIN_CAMERA(player);
		//AddGameObject(eLayerType::Player, player);
		SET_MESH(player, L"RectMesh");
		SET_MATERIAL(player, L"AnimationMaterial");
		SET_SCALE_XYZ(player, 48.f, 74.f, 1.f);
		ADD_COMP(player, Animator);
		//player->AddComponent<OverlayEffectSkillScript>(1);

		learnedSkill[2][(int)eFireSkillType::fireBolt] = 1;
		learnedSkill[0][(int)eColdSkillType::blizzard] = 1;

		SetSkill(0, eSkillType::normalAttack);
		SetSkill(1, eSkillType::fireBolt);
	}

	void PlayerInfo::CalHpPercent()
	{
		hpPercent = (hpCapacity - hp) / hpCapacity;
	}
	void PlayerInfo::CalMpPercent()
	{
		mpPercent = (mpCapacity - mp) / mpCapacity;
	}
	eSkillType PlayerInfo::GetSkill(int num)
	{
		if (num > 2 || num < 0) return eSkillType::END;

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