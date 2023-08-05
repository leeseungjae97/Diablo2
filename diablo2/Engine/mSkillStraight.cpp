#include "mSkillStraight.h"

#include "../engine_source/SkillAnimLookUpTables.h"
#include "../engine_source/mAnimator.h"

namespace m
{
	SkillStraight::SkillStraight(eSkillType type, Vector3 iniPos)
		:Skill(type, iniPos)
	{
	}
	SkillStraight::~SkillStraight()
	{
	}
	void SkillStraight::Initialize()
	{
	}
	void SkillStraight::Update()
	{
		if (Stop())
		{
			SetState(NoRenderNoUpdate);
		}
		Vector3 curPosition = GET_POS(this);

		Vector3 unprojMousePos = Input::GetUnprojectionMousePos(destPosition.z
			, GetCamera()->GetPrivateProjectionMatrix(), GetCamera()->GetPrivateViewMatrix());
		if(bSkillFire)
		{
			bSkillFire = false;
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

		float maxX = max(curPosition.x, prevPosition.x);
		float maxY = max(curPosition.y, prevPosition.y);

		float minX = min(curPosition.x, prevPosition.x);
		float minY = min(curPosition.y, prevPosition.y);

		fRemainDistance = (Vector2(maxX, maxY) - Vector2(minX, minY)).Length();

		if (fRemainDistance < fStartDistance)
		{
			float fMoveX = curPosition.x + (vDirection.x * fSpeed * Time::fDeltaTime());
			float fMoveY = curPosition.y + (vDirection.y * fSpeed * Time::fDeltaTime());
			SET_POS_XYZ(this, fMoveX, fMoveY, curPosition.z);
		}
	}
	void SkillStraight::LateUpdate()
	{
	}
	void SkillStraight::Render()
	{
	}
	void SkillStraight::Hit(int damage)
	{

	}
}