#include "mSkill.h"

#include "../engine_source/mTileManager.h"
#include "../engine_source/mMonsterManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mGameObject.h"

#include "mMonster.h"
namespace m
{
	Skill::Skill(eSkillType type, Vector3 iniPos)
		: MoveAbleObject(iniPos
			, 300.f
			, true
			, false
			, false
			, false 
		)
		, mSkillType(type)
		, bSkillFire(false)
	{
		//SET_MESH(this, L"RectMesh");
		//SET_MATERIAL(this, L"");
	}
	Skill::~Skill()
	{
	}
	void Skill::Initialize()
	{
		GameObject::Initialize();
	}
	void Skill::Update()
	{
		GameObject::Update();
		// 벽충돌

		// 유닛 충돌 Player 제외
		//if (hitAreaCollider->GetOnEnter()
		//	|| hitAreaCollider->GetOnStay())
		//{

		//}
	}
	void Skill::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Skill::Render()
	{
		GameObject::Render();
	}
	void Skill::Hit(int damage)
	{
	}
}