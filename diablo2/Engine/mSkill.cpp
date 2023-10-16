#include "mSkill.h"

#include "../engine_source/mMonsterManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mGameObject.h"
#include "../engine_source/SkillLookUpTables.h"

#include "mMonster.h"
#include "mSkillManager.h"

namespace m
{
	int Skill::uSkillIdDispender = 0;
	Skill::Skill(eSkillType type
		, Vector3 iniPos
		, bool useHitArea
		, bool useRange
		, bool useTilePos
		, bool useAstar
	)
		: MoveAbleObject(iniPos
			, skillSpeed[(int)type]
			, useHitArea
			, useRange
			, useTilePos
			, useAstar
		)
		, mSkillType(type)
		, bSkillFire(false)
		, bSkillCrash(false)
	    , mSkillId(++uSkillIdDispender)
	{
		SkillManager::AddSkill(this);
	}
	Skill::~Skill()
	{
		SkillManager::EraseSkill(mSkillId);
	}
	void Skill::Initialize()
	{
		MoveAbleObject::Initialize();
	}
	void Skill::Update()
	{
		MoveAbleObject::Update();
		//mOESS->Update();
	}
	void Skill::LateUpdate()
	{
		MoveAbleObject::LateUpdate();
	}
	void Skill::Render()
	{
		MoveAbleObject::Render();
	}
	void Skill::Hit(int damage, bool attackStun)
	{
	}
	void Skill::SetSkillOwnerLayer(eLayerType ownerType)
	{
		skillOwnerType = ownerType;
		for (Collider2D* col : GetComponents<Collider2D>())
		{
			col->AddExceptType(ownerType);
		}
	}

    void Skill::HitWall()
    {
		SetState(Delete);
    }
}
