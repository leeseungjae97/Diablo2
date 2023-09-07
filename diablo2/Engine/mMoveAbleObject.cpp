#include "mMoveAbleObject.h"
#include "mInput.h"
#include "mTransform.h"
#include "mMeshRenderer.h"
#include "mTime.h"
#include "mCamera.h"
#include "mApplication.h"
#include "mMouseManager.h"
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
		, fAdjustSpeed(speed)
		, fStartDistance(0.f)
		, fRemainDistance(0.f)
		, vDirection(Vector2::Zero)
		, bGetHit(false)
		, bMove(false)
	    , bMadePath(false)
		, bSixteenDirection(false)
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
			Vector3 scale = GET_SCALE(this);
			tilePositionCollider = ADD_COMP(this, Collider2D);
			tilePositionCollider->SetType(eColliderType::Dot);
			tilePositionCollider->SetColliderFunctionType(eColliderFunctionType::TilePos);
		}

		if (useAstar)
			mPathFinder = new PathFinder();
		ADD_COMP(this, MeshRenderer);


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
		AddZWeight();
		AdjustmentMovementSpeedAccordingAngle();
	}
	void MoveAbleObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void MoveAbleObject::Render()
	{
		GameObject::Render();
	}
	void MoveAbleObject::AddZWeight()
	{
		Vector3 pos = GET_POS(this);
		if (GetLayerType() == eLayerType::Player)
		{
			pos.z = 1.f + ((TileManager::playerStandTile->GetCoord().x * 0.0001f) + (TileManager::playerStandTile->GetCoord().y * 0.0001f));
		}
		else
		{
			pos.z = 1.f + ((mCoord.x * 0.0001f) + (mCoord.y * 0.0001f));
		}
		SET_POS_VEC(this, pos);
	}
	void MoveAbleObject::AdjustmentMovementSpeedAccordingAngle()
	{
		float degree = RadianToDegree(atan2(vDirection.x, vDirection.y));
		
		//int direction;
		float degreeWeight = 0.f;
		float devideNum = 0.f;
		//int* plusDirection = nullptr;
		//int* minusDirection = nullptr;
		if(bMadePath)
		{
			if (bSixteenDirection)
			{
				devideNum = 18.f;
				degreeWeight = degree / (180.f / devideNum);
				//if (degreeIndex > 0)
				//	plusDirection = pathPlusSixteenDirections;
				//else
				//	minusDirection = pathMinusSixteenDirections;
			}else
			{
				devideNum = 5.f;
				degreeWeight = degree / (180.f / devideNum);
				//if (degreeIndex > 0)
				//	plusDirection = pathPlusEightDirections;
				//else
				//	minusDirection = pathMinusEightDirections;
			}
		}else
		{
			if (bSixteenDirection)
			{
				devideNum = 9.f;
				degreeWeight = degree / (180.f / devideNum);
				//if (degreeIndex > 0)
				//	plusDirection = plusSixteenDirections;
				//else
				//	minusDirection = minusSixteenDirections;
			}
			else
			{
				devideNum = 5.f;
				degreeWeight = degree / (180.f / devideNum);
				//if (degreeIndex > 0)
				//	plusDirection = plusEightDirections;
				//else
				//	minusDirection = minusEightDirections;
			}
		}

		// 0 ~ 9
		
		//
		//float c = m / (devideNum / 2.f);
		if(GetName() == L"orb")
		{
		    if(math::areAlmostEqual(18.f, degreeWeight)
				&& math::areAlmostEqual(0.f, degreeWeight))
		    {
				int a = 0;
		    }
		}

		float reductionSpeed = fSpeed / 2.f;
		float middleDegreeIndex = (devideNum) / 2.f;

		float weight = fabs(fabs(degreeWeight) - middleDegreeIndex);
		float adjustmentedSpeed = reductionSpeed / (devideNum + 1.f);

		fAdjustSpeed = fSpeed - (adjustmentedSpeed * weight);

		//float middleIndex = (devideNum / 2.f);
		//float weight = fabs(fabs(degreeIndex) - middleIndex);
		//float adjustmentSpeed = fSpeed / middleIndex;

		//fAdjustSpeed = fSpeed - (adjustmentSpeed * weight);

		//fAdjustSpeed = fSpeed - (m - (fabs(n) * c));
		//fAdjustSpeed = fSpeed - (fabs(n) * 20.f);
		//fAdjustSpeed = fSpeed - (fSpeed / (abs(n) == 0 ? 1 : abs(n) * 10.f));
		//fAdjustSpeed = fSpeed - (n * 10.f);
	/*	if (n > 0)
			direction = (int)plusDirection[n];
		else
			direction = (int)minusDirection[abs(n)];
		if (bMadePath)
		{
			switch (direction)
			{
			case (int)ePathSixteenDirection::Right:
			case (int)ePathSixteenDirection::Left:
			{
				fAdjustSpeed = fSpeed;
			}
			break;
			case (int)ePathSixteenDirection::Down:
			case (int)ePathSixteenDirection::Up:
			{
				fAdjustSpeed = fSpeed - 100.f;
			}
			break;
			case (int)ePathSixteenDirection::LeftDown1:
			case (int)ePathSixteenDirection::LeftUp3:
			case (int)ePathSixteenDirection::RightUp1:
			case (int)ePathSixteenDirection::RightDown3:
			{
				fAdjustSpeed = fSpeed - 90.f;
			}
			break;
			case (int)ePathSixteenDirection::RightUp2:
			case (int)ePathSixteenDirection::LeftDown2:
			case (int)ePathSixteenDirection::RightDown2:
			case (int)ePathSixteenDirection::LeftUp2:
			{
				fAdjustSpeed = fSpeed - 50.f;
			}
			break;
			case (int)ePathSixteenDirection::RightDown1:
			case (int)ePathSixteenDirection::RightUp3:
			case (int)ePathSixteenDirection::LeftDown3:
			case (int)ePathSixteenDirection::LeftUp1:
			{
				fAdjustSpeed = fSpeed - 20.f;
			}
			break;
			default:
			{
				fAdjustSpeed = fSpeed;
			}
			break;
			}
		}else
		{
			switch (direction)
			{
			case (int)eSixteenDirection::Down:
			case (int)eSixteenDirection::Up:
			{
				fAdjustSpeed = fSpeed / 2.f;
			}
			break;
			case (int)eSixteenDirection::RightUp1:
			case (int)eSixteenDirection::LeftDown1:
			case (int)eSixteenDirection::RightDown1:
			case (int)eSixteenDirection::LeftUp1:
			{
				fAdjustSpeed = fSpeed / 1.4f;
			}
			break;

			case (int)eSixteenDirection::RightUp2:
			case (int)eSixteenDirection::LeftDown2:
			case (int)eSixteenDirection::RightDown2:
			case (int)eSixteenDirection::LeftUp2:
			{
				fAdjustSpeed = fSpeed / 1.3f;
			}
			break;

			case (int)eSixteenDirection::RightUp3:
			case (int)eSixteenDirection::LeftDown3:
			case (int)eSixteenDirection::RightDown3:
			case (int)eSixteenDirection::LeftUp3:
			{
				fAdjustSpeed = fSpeed / 1.2f;
			}
			break;
			default:
			{
				fAdjustSpeed = fSpeed;
			}
			break;
			}
		}*/
	}
	void MoveAbleObject::SetInitializePosition(Vector3 initPos)
	{
		prevPosition = initPos;
		destPosition = initPos;
		initPosition = initPos;
		vS = initPos;
	}
}
