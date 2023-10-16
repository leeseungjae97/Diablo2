#include "mMoveAbleObject.h"
#include "mInput.h"
#include "mTransform.h"
#include "mMeshRenderer.h"
#include "mTime.h"
#include "mCamera.h"
#include "mApplication.h"
#include "mMouseManager.h"
#include "mShadowObject.h"
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

		, bAdjustmentDegree(false)
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

		fXAdjustSpeed = fSpeed;
		fYAdjustSpeed = fSpeed / 2.f;
	}
	MoveAbleObject::~MoveAbleObject()
	{
		if (mPathFinder)
			delete mPathFinder;
		//if (mShadow)
		//	mShadow->SetState(Delete);
	}
	void MoveAbleObject::Initialize()
	{
	}
	void MoveAbleObject::Update()
	{
		GameObject::Update();

		addZWeight();
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
		if (fNASAcc > 0)
		{
			mr->SetTrappingColor(Vector4(0.f, 0.f, 10.f, 1.f));
		}
		else
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

		if (fCanDamagedDelay >= 0.5f)
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
	void MoveAbleObject::SetAdjustmentDegree()
	{
		if (!bAdjustmentDegree)
		{
			Vector3 _vD = vDirection;
			
			float fMoveX1 = _vD.x * (fXAdjustSpeed + fNumericalAdjustmentSpeed);
			float fMoveY1 = _vD.y * (fYAdjustSpeed + (fNumericalAdjustmentSpeed == 0.f ? 0.f : fNumericalAdjustmentSpeed / 2.f));

			float fMoveX2 = _vD.x * (fXAdjustSpeed + fNumericalAdjustmentSpeed);
			float fMoveY2 = _vD.y * (fXAdjustSpeed + fNumericalAdjustmentSpeed);

			Vector2 m1 = Vector2(fMoveX1, fMoveY1);
			Vector2 m2 = Vector2(fMoveX2, fMoveY2);

			m1.Normalize();
			m2.Normalize();

			float m1degree = RadianToDegree(atan2(m1.y, m1.x));
			float theta = atan2(m1.y, m1.x) - atan2(m2.y, m2.x);

			if (fabs(m1degree) > 90.f)
			{
				vDirection.y = _vD.y + sinf(theta * 2);
			}
			else
			{
				vDirection.y = _vD.y - sinf(theta * 2);
			}
			vDirection.Normalize();
			bAdjustmentDegree = true;
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
			pos.z = 1.f + ((TileManager::GetPlayerPosition().x * 0.0001f) + (TileManager::GetPlayerPosition().y * 0.0001f));
		}
		else
		{
			pos.z = 1.f + ((pos.x * 0.0001f) + (pos.y * 0.0001f));
		}
		//pos.z = 1.f + ((pos.x * 0.0001f) + (pos.y * 0.0001f));
		SET_POS_VEC(this, pos);
	}
	void MoveAbleObject::SetInitializePosition(Vector3 initPos)
	{
		prevPosition = initPos;
		destPosition = initPos;
		initPosition = initPos;
		vS = initPos;
	}
}
