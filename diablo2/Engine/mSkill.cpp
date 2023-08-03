#include "mSkill.h"

#include "../engine_source/mTileManager.h"
#include "../engine_source/mMonsterManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mGameObject.h"
#include "../engine_source/mTime.h"

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
		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"");
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

		// 벽충돌

		// 유닛 충돌 Player 제외
		if (hitAreaCollider->GetOnEnter()
			|| hitAreaCollider->GetOnStay())
		{

		}

		if (Stop())
		{
			SetState(NoRenderNoUpdate);
		}
	}
	void Skill::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Skill::Render()
	{
		GameObject::Render();
	}
}