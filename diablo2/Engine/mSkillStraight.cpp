#include "mSkillStraight.h"

#include "../engine_source/SkillAnimLookUpTables.h"
#include "../engine_source/mAnimator.h"
#include "../engine_source/mMeshRenderer.h"

namespace m
{
	SkillStraight::SkillStraight(eSkillType type, Vector3 iniPos, float speed)
		:Skill(type, iniPos, false, true)
	{
		SetSpeed(speed);
		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");
		SET_SCALE_XYZ(this, skillSizes[(int)type].x, skillSizes[(int)type].y, 1.f);
		ADD_COMP(this, Animator);
	}
	SkillStraight::~SkillStraight()
	{
	}
	void SkillStraight::Initialize()
	{
		Skill::Initialize();
	}
	void SkillStraight::Update()
	{
		Skill::Update();
		Vector3 curPosition = GET_POS(this);

		Vector3 unprojMousePos = Input::GetUnprojectionMousePos(destPosition.z
			, GetCamera()->GetPrivateProjectionMatrix(), GetCamera()->GetPrivateViewMatrix());
		if(!bSkillFire)
		{
			bSkillFire = true;
			prevPosition = GET_POS(this);
			destPosition = Vector3(unprojMousePos.x, unprojMousePos.y, destPosition.z);

			float maxX = max(destPosition.x, prevPosition.x);
			float maxY = max(destPosition.y, prevPosition.y);

			float minX = min(destPosition.x, prevPosition.x);
			float minY = min(destPosition.y, prevPosition.y);

			SetStartDistance((Vector2(maxX, maxY) - Vector2(minX, minY)).Length());

			vDirection = destPosition - prevPosition;
			vDirection.Normalize();
		}

		float fMoveX = curPosition.x + (vDirection.x * fSpeed * Time::fDeltaTime());
		float fMoveY = curPosition.y + (vDirection.y * fSpeed * Time::fDeltaTime());
		SET_POS_XYZ(this, fMoveX, fMoveY, curPosition.z);

		//float maxX = max(curPosition.x, prevPosition.x);
		//float maxY = max(curPosition.y, prevPosition.y);

		//float minX = min(curPosition.x, prevPosition.x);
		//float minY = min(curPosition.y, prevPosition.y);

		//fRemainDistance = (Vector2(maxX, maxY) - Vector2(minX, minY)).Length();

		//if (fRemainDistance < fStartDistance)
		//{
		//	
		//}
		//if (!bSkillFire && Stop())
		//{
		//	SetState(NoRenderNoUpdate);
		//}
	}
	void SkillStraight::LateUpdate()
	{
		Skill::LateUpdate();
	}
	void SkillStraight::Render()
	{
		Skill::Render();
	}
	void SkillStraight::Hit(int damage)
	{

	}
}