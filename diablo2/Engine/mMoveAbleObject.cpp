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

		: prevPosition(iniPos)
		, destPosition(iniPos)
		, vS(iniPos)
		, fSpeed(speed)
		, fStartDistance(0.f)
		, fRemainDistance(0.f)
		, bGetHit(false)
	{
		SET_POS_VEC(this, iniPos);

		if(useHitArea)
			hitAreaCollider = ADD_COMP(this, Collider2D);

		if (useRange)
		{
			rangeCollider = ADD_COMP(this, Collider2D);
			rangeCollider->SetType(eColliderType::Circle);
		}

		if (useTilePos)
		{
			tilePositionCollider = ADD_COMP(this, Collider2D);
			tilePositionCollider->SetType(eColliderType::Dot);
		}

		if(useAstar)
			mAstar = new Astar();
		ADD_COMP(this, MeshRenderer);
	}
	MoveAbleObject::~MoveAbleObject()
	{
		if(mAstar)
			delete mAstar;
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