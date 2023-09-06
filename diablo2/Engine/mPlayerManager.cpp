#include "mPlayerManager.h"

#include "../engine_source/mTileManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mAnimator.h"

#include "mInvenItem.h"
#include "mPlayer.h"
#include "mOverlayEffectSkillScript.h"
namespace m
{
	int PlayerManager::learnedSkill[3][10]= {};
	int PlayerManager::skillPoint = 0;
	float PlayerManager::hp = 100.f;
	float PlayerManager::hpCapacity = 100.f;
	float PlayerManager::hpPercent = 1.f;
	float PlayerManager::mp = 100.f;
	float PlayerManager::mpCapacity = 100.f;
	float PlayerManager::mpPercent = 1.f;

	Player* PlayerManager::player = nullptr;
	eSkillType PlayerManager::skillTypes[2] = {};

	void PlayerManager::Initialize()
	{
		skillPoint = 100;
		Tile* tile2 = TileManager::pathFindingTiles[60][10];
		//Vector3 pos2 = GET_POS(tile2);
		Vector3 pos2 = Vector3(10.f, 10.f, 1.f);

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
		learnedSkill[0][(int)eColdSkillType::frozenOrb] = 1;
		learnedSkill[0][(int)eColdSkillType::iceBolt] = 1;

		SetSkill(0, eSkillType::normalAttack);
		SetSkill(1, eSkillType::frozenOrb);
	}

	void PlayerManager::CalHpPercent()
	{
		hpPercent = (hpCapacity - hp) / hpCapacity;
	}
	void PlayerManager::CalMpPercent()
	{
		mpPercent = (mpCapacity - mp) / mpCapacity;
	}
	eSkillType PlayerManager::GetSkill(int num)
	{
		if (num > 2 || num < 0) return eSkillType::END;

		return skillTypes[num];
	}

	void PlayerManager::SetSkill(int num, eSkillType type)
	{
		if (num > 2) return;

		skillTypes[num] = type;
	}

	eSkillType PlayerManager::SetColdSkillType(eColdSkillType type)
	{
		return (eSkillType)type;
	}

	eSkillType PlayerManager::SetFireSkillType(eFireSkillType type)
	{
		return (eSkillType)((UINT)type + (UINT)eSkillType::coldMastery);
	}

	eSkillType PlayerManager::SetLightningSkillType(eLightningSkillType type)
	{
		return (eSkillType)((UINT)type + (UINT)eSkillType::lightningMastery);
	}
}