#include "mMoveAbleObject.h"
#include "mInput.h"
#include "mTransform.h"
#include "mMeshRenderer.h"
#include "mTime.h"
#include "mCamera.h"
#include "mApplication.h"
#include "mMouseManager.h"
#include "mTrappingColor.h"
#include "SkillAnimLookUpTables.h"

namespace m
{
	MoveAbleObject::MoveAbleObject(Vector3 iniPos
		, float speed
		, bool useHitArea
		, bool useRange
		, bool useTilePos
		, bool useAstar
	)
		: GameObject()
		, prevPosition(iniPos)
		, destPosition(iniPos)
		, initPosition(iniPos)
		, vS(iniPos)

		, fSpeed(speed)
		, fXAdjustSpeed(speed)
		, fYAdjustSpeed(speed)
		, fStartDistance(0.f)
		, fRemainDistance(0.f)
		, vDirection(Vector2::Zero)

		, bGetHit(false)

		, bMove(false)

	    , bMadePath(false)

	    , bCanDamaged(false)
	    , fCanDamagedDelay(0.f)

		, bSixteenDirection(false)

	    , fNumericalAdjustmentSpeed(0.f)
	    , bCallSetNumericalAdjustmentSpeed(false)

		, bAddiction(false)
		, fAddictionTime(0.f)
		, fAddictionTickCount(0)
		, iAddictionDamage(0)
		, fAccAddiction(0.f)
		, fAccDamage(0)

		, bStun(false)
		, fAccStun(0.f)
		, fStunSecond(0.f)

		, mCoord(Vector2(0.f, 0.f))
	{
		SET_POS_VEC(this, iniPos);

		if (useHitArea)
		{
			bodyBoxCollider = ADD_COMP(this, Collider2D);
			bodyBoxCollider->SetColliderFunctionType(eColliderFunctionType::HitArea);
		}

		if (useRange)
		{
			rangeCollider = ADD_COMP(this, Collider2D);
			rangeCollider->SetType(eColliderType::Circle);
			rangeCollider->SetColliderFunctionType(eColliderFunctionType::Range);
			rangeCollider->AddExceptType(eLayerType::Skill);
		}

		if (useTilePos)
		{
			//Vector3 scale = GET_SCALE(this);
			tilePositionCollider = ADD_COMP(this, Collider2D);
			tilePositionCollider->SetType(eColliderType::Dot);
			tilePositionCollider->SetColliderFunctionType(eColliderFunctionType::TilePos);
		}

		if (useAstar)
			mPathFinder = new PathFinder();
		MeshRenderer* mr = ADD_COMP(this, MeshRenderer);
		mr->AddTrappingColorBuffer();
	}
	MoveAbleObject::~MoveAbleObject()
	{
		if (mPathFinder)
			delete mPathFinder;
	}
	void MoveAbleObject::Initialize()
	{
	}
	void MoveAbleObject::Update()
	{
		GameObject::Update();

		addZWeight();
		adjustmentMovementSpeedAccordingAngle();
		damagedDelay();
	}
	void MoveAbleObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void MoveAbleObject::Render()
	{
		GameObject::Render();
		MeshRenderer* mr = GET_COMP(this, MeshRenderer);
		if(fNASAcc > 0)
		{
			mr->SetTrappingColor(Vector4(0.f, 0.f, 10.f, 1.f));
		}else
		{
			mr->SetTrappingColor(Vector4(0.f, 0.f, 0.f, 1.f));
		}
	}

    void MoveAbleObject::SetNumericalAdjustmentSpeed(float speed, float time)
    {
		fNASAcc = time;
		fNumericalAdjustmentSpeed = speed;
		bCallSetNumericalAdjustmentSpeed = true;
    }
	void MoveAbleObject::Stun(float second)
	{
		fStunSecond = second;
		bStun = true;
	}
	void MoveAbleObject::Addiction(int damage, float addictionTime, int tickCount)
	{
		if (bAddiction)
		{
			fAddictionTickCount += (float)tickCount;
			fAddictionTime += addictionTime;
			iAddictionDamage += damage;
		}
		else
		{
			fAddictionTickCount = (float)tickCount;
			fAddictionTime = addictionTime;

			iAddictionDamage = damage;

			bAddiction = true;
		}

	}

    void MoveAbleObject::TimeWaitAttack()
    {
		if (!bCanDamaged)
			fCanDamagedDelay += Time::fDeltaTime();

		if (fCanDamagedDelay >= 1.f)
		{
			bCanDamaged = true;
			fCanDamagedDelay = 0.f;
		}
    }

    void MoveAbleObject::AttackedAddition()
    {
		if (bAddiction)
		{
			fAccAddiction += Time::fDeltaTime();

			if (fAccAddiction >= fAddictionTime / (float)fAddictionTickCount)
			{
				fAccDamage += iAddictionDamage / fAddictionTickCount;
				Hit(iAddictionDamage / fAddictionTickCount, false);
				fAccAddiction = 0.f;
			}
			if (fAccDamage >= iAddictionDamage)
			{
				bAddiction = false;
				fAccAddiction = 0.f;
				fAccDamage = 0.f;
			}
		}
    }

	void MoveAbleObject::damagedDelay()
	{
		if (!bCanDamaged) fCanDamagedDelay += Time::fDeltaTime();
		if (fCanDamagedDelay >= 1.f)
		{
			bCanDamaged = true;
			fCanDamagedDelay = 0.f;
		}
	}
	void MoveAbleObject::addZWeight()
	{
		Vector3 pos = GET_POS(this);
		if (GetLayerType() == eLayerType::Player)
		{
			//pos.z = 1.f + ((TileManager::playerStandTile->GetCoord().x * 0.0001f) + (TileManager::playerStandTile->GetCoord().y * 0.0001f));
			pos.z = 1.f + ((TileManager::GetPlayerPosition().x * 0.0001f) + (TileManager::GetPlayerPosition().y * 0.0001f));
		}
		else
		{
			//pos.z = 1.f + ((mCoord.x * 0.0001f) + (mCoord.y * 0.0001f));
			pos.z = 1.f + ((pos.x * 0.0001f) + (pos.y * 0.0001f));
		}
		SET_POS_VEC(this, pos);
	}
	void MoveAbleObject::adjustmentMovementSpeedAccordingAngle()
	{
		//float degree = RadianToDegree(atan2(vDirection.y, vDirection.x));
		//
		//float degreeWeightIndex = 0.f;
		//float devideNum = 0.f;

		//if (bSixteenDirection)
		//{
		//	devideNum = 18.f;
		//	degreeWeightIndex = degree / (180.f / devideNum);
		//}
		//else
		//{
		//	devideNum = 5.f;
		//	degreeWeightIndex = degree / (180.f / devideNum);
		//}
		//if (degreeWeightIndex > devideNum - 1.f) degreeWeightIndex = devideNum - 1.f;
		//float reductionSpeed = fSpeed / 2.f;
		//float middleDegreeIndex = (devideNum) / 2.f;
		//float weight = fabs(middleDegreeIndex - fabs(degreeWeightIndex));

		//float adjustmentedSpeed = reductionSpeed / middleDegreeIndex;

		//float minorAxisSpeed = adjustmentedSpeed * weight;

		fXAdjustSpeed = fSpeed;
		fYAdjustSpeed = fSpeed / 2.f;
	}
	void MoveAbleObject::SetInitializePosition(Vector3 initPos)
	{
		prevPosition = initPos;
		destPosition = initPos;
		initPosition = initPos;
		vS = initPos;
	}
}
