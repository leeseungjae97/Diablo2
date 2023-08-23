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

		if (GetBattleState() == eBattleState::Dead
			|| GetBattleState() == eBattleState::Attack
			|| GetBattleState() == eBattleState::Hit
			|| GetBattleState() == eBattleState::Cast) return;
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