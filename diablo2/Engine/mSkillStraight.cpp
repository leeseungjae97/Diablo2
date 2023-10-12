#include "mSkillStraight.h"

#include "../engine_source/mAudioSource.h"
#include "../engine_source/mLight.h"
#include "../engine_source/mMouseManager.h"
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
	    , fRandomRange(0.f)
	    , fRandomMoveAcc(0.f)
	    , fRandomMoveTime(0.f)
	    , randSign(1)
		, mHead(nullptr)
		, bHead(false)
		, bUseHead(false)
	    , bMute(false)
	{
		bMadePath = true;
		if(type == eSkillType::inferno)
		{
			limitDistance = 500.f;
		}
		SetSpeed(speed);

		ADD_COMP(this, AudioSource);

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
		if(type != eSkillType::fireWall)
		{
			Light* lightComp = AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 0.2f));
			lightComp->SetRadiusX(100.0f);
			lightComp->SetRadiusY(50.0f);
		}
	}
	SkillStraight::~SkillStraight()
	{
	}
	void SkillStraight::Initialize()
	{
		Skill::Initialize();
		if (bUseHead)
		{
			if (!bHead) ss->SetNoHit(true);
		}
	}
	void SkillStraight::Update()
	{
		Skill::Update();
		if (bSkillFire)
		{
			if (ss)
			{
				ss->Mute(bMute);
				ss->SkillFire();
			}

			bSkillFire = false;
			bMove = true;
			if (destPosition == initPosition)
			{
				Vector3 destVector = Vector3::One;
				if (GetLayerType() == eLayerType::PlayerSkill)
				{
					destVector = MouseManager::UnprojectionMousePos(destPosition.z, GetCamera());
				}
				else
					destVector = TileManager::GetPlayerPosition();
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
		
		Vector3 curPosition = GET_POS(this);

		if (bMove)
		{
			if(fRandomRange > 0.f)
			{
				randomY();
			}
			SetAdjustmentDegree();
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

    void SkillStraight::SetRandomStraight(float randomY, float fRandomTime)
    {
		fRandomRange = randomY;
		fRandomMoveTime = fRandomTime;
    }

	void SkillStraight::randomY()
	{
		fRandomMoveAcc -= Time::fDeltaTime();
		if(fRandomMoveAcc <= 0.f)
		{
			int m = 0;
			m = rand() % 2;

			float xRand = fRandomRange / 2.f;
			float yRand = fRandomRange;

			if (vDirection.x <= 0.f) xRand *= -1.f;

			if (m > 0)
			{
				yRand *= -1.f;
				xRand *= -1.f;
			}
			//randSign *= -1;
			//yRand *= randSign;

			vDirection.x += xRand;
			vDirection.y += yRand;
			vDirection.Normalize();

			fRandomMoveAcc = fRandomMoveTime;
		}
	
	}
	void SkillStraight::Hit(int damage, bool attackStun)
	{

	}
}