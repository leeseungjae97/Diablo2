#include "mSkillStraight.h"

#include "mMouseManager.h"
#include "../engine_source/SkillLookUpTables.h"
#include "../engine_source/mAnimator.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTileManager.h"

namespace m
{
	SkillStraight::SkillStraight(eSkillType type
		, Vector3 iniPos
		, float speed
		, bool useLimitDistance
		, bool useAnimator
	)
		:Skill(type, iniPos, false, true)
		, limitDistance(1000.f)
	    , useLimit(useLimitDistance)
	{
		bMadePath = true;
		
		SetSpeed(speed);
		SET_MESH(this, L"RectMesh");
		if(useAnimator)
		{
			SET_MATERIAL(this, L"AnimationMaterial");
			SET_SCALE_XYZ(this, skillSizes[(int)type].x, skillSizes[(int)type].y, 1.f);
			ADD_COMP(this, Animator);

			ss = AddComponent<StraightScript>(skillAnimDirections[(int)type]);
			if (skillAnimDirections[(int)type] == 16)
			{
				rangeCollider->SetSize(Vector3(0.5f, 0.5f, 1.f));
				bSixteenDirection = false;
			}
			else
				bSixteenDirection = true;
		}
	    else
		{
			SET_MATERIAL(this, L"noneRect");
		}
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
		if(bSkillFire)
		{
			if(ss)
			    ss->SkillFire();

			bSkillFire = false;
			bMove = true;
			
			if(destPosition == initPosition)
			{
				Vector3 destVector = Vector3::One;
				if (GetLayerType() == eLayerType::PlayerSkill)
				{
					destVector = MouseManager::UnprojectionMousePos(destPosition.z, GetCamera());
				}
				else destVector = TileManager::GetPlayerPosition();
				destPosition = Vector3(destVector.x, destVector.y, destPosition.z);
			}

			prevPosition = GET_POS(this);
		
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
			float fMoveX = curPosition.x + (vDirection.x * fXAdjustSpeed * Time::fDeltaTime());
			float fMoveY = curPosition.y + (vDirection.y * fYAdjustSpeed * Time::fDeltaTime());

			SET_POS_XYZ(this, fMoveX, fMoveY, curPosition.z);
		}
		moveDistance = (Vector2(prevPosition.x, prevPosition.y) - Vector2(curPosition.x, curPosition.y)).Length();
		if (useLimit && 
			limitDistance <= moveDistance)
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
	void SkillStraight::Hit(int damage, bool attackStun)
	{

	}
}