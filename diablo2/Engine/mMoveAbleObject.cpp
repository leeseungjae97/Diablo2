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
	MoveAbleObject::MoveAbleObject(Vector3 iniPos, float speed)
		: prevPosition(iniPos)
		, destPosition(iniPos)
		, vS(iniPos)
		, fSpeed(speed)
		, fStartDistance(0.f)
		, fRemainDistance(0.f)
		, bGetHit(false)
	{
		SET_POS_VEC(this, iniPos);
		ADD_COMP(this, Collider2D);

		rangeCollider = ADD_COMP(this, Collider2D);
		rangeCollider->SetType(eColliderType::Circle);
		rangeCollider->AddExceptType(eLayerType::Tile);

		ADD_COMP(this, MeshRenderer);
		mAstar = new Astar();
	}
	MoveAbleObject::~MoveAbleObject()
	{
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