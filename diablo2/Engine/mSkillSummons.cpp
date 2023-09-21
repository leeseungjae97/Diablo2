#include "mSkillSummons.h"

#include "mMonster.h"
#include "../engine_source/mTime.h"

#include "mSummonsScript.h"

namespace m
{
	SkillSummons::SkillSummons(int type, Vector3 initPos, Vector3 vLookDirection, float summonTime)
		: MoveAbleObject(initPos, 300.f, false, true, false, false)
		, fSummonTime(summonTime)
		, mType(type)

	{
		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");

		ADD_COMP(this, Animator);

		if (type == (int)eSummonsType::Hydra)
		{
			vDirection = vLookDirection - initPos;
			vDirection.Normalize();

			AddComponent<SummonsScript<Hydra>>(summonTime);
		}
		
		//rangeCollider
	}

	SkillSummons::~SkillSummons()
	{
	}

	void SkillSummons::Initialize()
	{
		MoveAbleObject::Initialize();
	}

	void SkillSummons::Update()
	{
		MoveAbleObject::Update();
		updateAttackDirection();
	}

	void SkillSummons::LateUpdate()
	{
		MoveAbleObject::LateUpdate();
	}

	void SkillSummons::Render()
	{
		MoveAbleObject::Render();
	}

	void SkillSummons::Hit(int damage, bool attackStun)
	{
	}

	void SkillSummons::updateAttackDirection()
	{
		Monster* monster = rangeCollider->SearchCollideredMonster();
		if (nullptr == monster) return;

		Vector3 otherPos = GET_POS(monster);
		Vector3 pos = GET_POS(this);

		vDirection = otherPos - pos;
		vDirection.Normalize();
	}
}
