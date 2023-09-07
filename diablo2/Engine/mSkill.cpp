#include "mSkill.h"

#include "../engine_source/mMonsterManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mGameObject.h"
#include "../engine_source/SkillLookUpTables.h"

#include "mMonster.h"
namespace m
{
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
	{
	}
	Skill::~Skill()
	{
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
	void Skill::Hit(int damage)
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
}