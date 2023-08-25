#include "mMoveAbleObject.h"
#include "mInput.h"
#include "mTransform.h"
#include "mMeshRenderer.h"
#include "mTime.h"
#include "mCamera.h"
#include "mApplication.h"
#include "mMouseManager.h"

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
		, vS(iniPos)
		, fSpeed(speed)
		, fStartDistance(0.f)
		, fRemainDistance(0.f)
		, vDirection(Vector2::Zero)
		, bGetHit(false)
		, bMove(false)
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

		if(useAstar)
			mPathFinder = new PathFinder();
		ADD_COMP(this, MeshRenderer);

		
	}
	MoveAbleObject::~MoveAbleObject()
	{
		if(mPathFinder)
			delete mPathFinder;
	}
	void MoveAbleObject::Initialize()
	{
	}
	void MoveAbleObject::Update()
	{
		GameObject::Update();
		
		Vector3 pos = GET_POS(this);
		if(GetLayerType() == eLayerType::Player)
		{
			pos.z = 1.f + ((TileManager::playerStandTile->GetCoord().x * 0.0001f) + (TileManager::playerStandTile->GetCoord().y * 0.0001f));
		}else
		{
			pos.z = 1.f + ((mCoord.x * 0.0001f) + (mCoord.y * 0.0001f));
		}
		SET_POS_VEC(this, pos);

	}
	void MoveAbleObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void MoveAbleObject::Render()
	{
		GameObject::Render();
	}
}