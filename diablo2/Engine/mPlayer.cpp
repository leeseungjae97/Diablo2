#include "mPlayer.h"
#include "mInput.h"
#include "mTransform.h"
#include "mMeshRenderer.h"
#include "mTime.h"
#include "mCamera.h"
#include "mApplication.h"
#include "mMouseManager.h"

#include "../engine_source/mAstar.h"

extern m::Application application;
namespace m
{
	Player::Player(Vector3 iniPos)
		: prevPosition(iniPos)
		, destPosition(iniPos)
		, vS(iniPos)
		, fSpeed(300.f)
		, fStartDistance(0.f)
		, fRemainDistance(0.f)
		, bGetHit(false)
	{
		SET_POS_VEC(this, iniPos);
		ADD_COMP(this, Collider2D);

		rangeCollider = ADD_COMP(this, Collider2D);
		rangeCollider->SetType(eColliderType::Circle);
		rangeCollider->SetSize(Vector3(1.f, 1.f, 1.f));

		ADD_COMP(this, MeshRenderer);
	}
	Player::~Player()
	{}
	void Player::Initialize()
	{}
	void Player::Update()
	{
		GameObject::Update();

		if (GetBattleState() == eBattleState::Dead
			|| GetBattleState() == eBattleState::Attack
			|| GetBattleState() == eBattleState::Hit
			|| GetBattleState() == eBattleState::Cast) return;

		
		Vector3 curPosition = GET_POS(this);
		
		Vector3 unprojMousePos = Input::GetUnprojectionMousePos(destPosition.z
			, GetCamera()->GetPrivateProjectionMatrix(), GetCamera()->GetPrivateViewMatrix());

		if (Input::GetKeyDownOne(eKeyCode::LBUTTON)
			&& !MouseManager::GetMouseOnUI())
		{
			Vector2 curCoord = TileManager::GetPlayerPositionCoord();
			Vector2 mouseCoord = TileManager::GetHoverTileCoord();

			Astar::PathFinding(curCoord, mouseCoord);

			prevPosition = GET_POS(this);

			destPosition = Vector3(unprojMousePos.x, unprojMousePos.y, destPosition.z);

			float maxX = max(destPosition.x, prevPosition.x);
			float maxY = max(destPosition.y, prevPosition.y);

			float minX = min(destPosition.x, prevPosition.x);
			float minY = min(destPosition.y, prevPosition.y);

			//float dX = destPosition.x < 0 ? fabs(destPosition.x * 2) : destPosition.x;
			//float dY = destPosition.y < 0 ? fabs(destPosition.y * 2) : destPosition.y;

			//float pX = prevPosition.x < 0 ? fabs(prevPosition.x * 2) : prevPosition.x;
			//float pY = prevPosition.y < 0 ? fabs(prevPosition.y * 2) : prevPosition.y;

			//fStartDistance = (Vector2(dX, dY) - Vector2(pX, pY)).Length();

			fStartDistance = (Vector2(maxX, maxY) - Vector2(minX, minY)).Length();

			vDirection = destPosition - curPosition;
			vDirection.Normalize();
		}

		float maxX = max(curPosition.x, prevPosition.x);
		float maxY = max(curPosition.y, prevPosition.y);

		float minX = min(curPosition.x, prevPosition.x);
		float minY = min(curPosition.y, prevPosition.y);

		fRemainDistance = (Vector2(maxX, maxY) - Vector2(minX, minY)).Length();

		//float dX = curPosition.x < 0 ? fabs(curPosition.x * 2) : curPosition.x;
		//float dY = curPosition.y < 0 ? fabs(curPosition.y * 2) : curPosition.y;

		//float pX = prevPosition.x < 0 ? fabs(prevPosition.x * 2) : prevPosition.x;
		//float pY = prevPosition.y < 0 ? fabs(prevPosition.y * 2) : prevPosition.y;

		//fRemainDistance = (Vector2(pX, pY) - Vector2(dX, dY)).Length();

		if (fRemainDistance < fStartDistance)
		{
			float fMoveX = curPosition.x + (vDirection.x * fSpeed * Time::fDeltaTime());
			float fMoveY = curPosition.y + (vDirection.y * fSpeed * Time::fDeltaTime());
			SET_POS_XYZ(this, fMoveX, fMoveY, curPosition.z);
		}
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player::Render()
	{
		GameObject::Render();
	}
}