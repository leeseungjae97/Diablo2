#include "mSkillStraight.h"

#include "mMouseManager.h"
#include "../engine_source/SkillLookUpTables.h"
#include "../engine_source/mAnimator.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTileManager.h"

namespace m
{
	SkillStraight::SkillStraight(eSkillType type, Vector3 iniPos, float speed)
		:Skill(type, iniPos, false, true)
		, limitDistance(1000.f)
	{
		SetSpeed(speed);
		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");
		SET_SCALE_XYZ(this, skillSizes[(int)type].x, skillSizes[(int)type].y, 1.f);
		ADD_COMP(this, Animator);

		if(type >= eSkillType::DiabloLightning)
		{
			ss = AddComponent<StraightScript>(8);
			rangeCollider->SetSize(Vector3(0.5f, 0.5f, 1.f));
		}
		else 
			ss = AddComponent<StraightScript>();
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
		//if (mbStopMove)
		//{
		//	fSpeed = 0.f;
		//}
		Vector3 curPosition = GET_POS(this);
		if(bSkillFire)
		{
			//ss->
			bSkillFire = false;
			bMove = true;
			Vector3 destVector = Vector3::One;
			if (GetLayerType() == eLayerType::PlayerSkill)
			{
				destVector = MouseManager::UnprojectionMousePos(destPosition.z, GetCamera());
			}
			else destVector = GET_POS(TileManager::playerStandTile);
			prevPosition = GET_POS(this);
			destPosition = Vector3(destVector.x, destVector.y, destPosition.z);

			float maxX = max(destPosition.x, prevPosition.x);
			float maxY = max(destPosition.y, prevPosition.y);

			float minX = min(destPosition.x, prevPosition.x);
			float minY = min(destPosition.y, prevPosition.y);

			SetStartDistance((Vector2(maxX, maxY) - Vector2(minX, minY)).Length());

			vDirection = destPosition - prevPosition;
			vDirection.Normalize();
		}
		if (bMove)
		{
			float fMoveX = curPosition.x + (vDirection.x * fSpeed * Time::fDeltaTime());
			float fMoveY = curPosition.y + (vDirection.y * fSpeed * Time::fDeltaTime());

			SET_POS_XYZ(this, fMoveX, fMoveY, curPosition.z);
		}
		
		Vector2 diff = (Vector2(prevPosition.x, prevPosition.y) - Vector2(curPosition.x, curPosition.y));
		if (limitDistance <= diff.Length())
		{
			bMove = false;
			SetState(eState::Delete);
		}
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