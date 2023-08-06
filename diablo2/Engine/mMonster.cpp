#include "mMonster.h"

#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTime.h"
#include "../engine_source/mMouseManager.h"

#include "mPlayerInfo.h"
#include "mPlayer.h"

namespace m
{
	Monster::Monster(Vector3 iniPos, float speed)
		: MoveAbleObject(iniPos, speed)
		, hp(0.f)
		, hpCapacity(0.f)
		, hpPercent(0.f)
	{
		monsterId = MonsterManager::DispendMonsterId();
		MonsterManager::AddMonster(this);

		sightCollider = ADD_COMP(this, Collider2D);
		sightCollider->SetType(eColliderType::Circle);
		sightCollider->SetSize(Vector3(5.f, 5.f, 1.f));

		rangeCollider->SetSize(Vector3(1.0f, 1.0f, 1.5f));

		hitAreaCollider->SetSize(Vector3(0.5f, 0.5f, 1.f));
	}
	Monster::~Monster()
	{}
	void Monster::Initialize()
	{
		MoveAbleObject::Initialize();
	}
	void Monster::Update()
	{
		MoveAbleObject::Update();

		if (GetBattleState() == eBattleState::Dead
			|| GetBattleState() == eBattleState::Attack
			|| GetBattleState() == eBattleState::Hit
			|| GetBattleState() == eBattleState::Cast) return;

		Vector3 curPosition = GET_POS(this);
		if (rangeCollider->GetOnStay())
		{
			fRemainDistance += fStartDistance;
			return;
		}

		Vector2 curCoord = GetCoord();
		Vector2 targetCoord = TileManager::GetPlayerPositionCoord();

		mAstar->PathFinding(curCoord, targetCoord);
		mAstar->MonsterMove(this);

		if (sightCollider->GetOnEnter()
			|| sightCollider->GetOnStay())
		{
			if (sightCollider->SearchObjectGameObjectId(PlayerInfo::player->GetGameObjectId()))
				mAstar->PathChange();


			//prevPosition = GET_POS(this);

			//destPosition = sightCollider->GetCollideredObjectPos();

			//float maxX = max(destPosition.x, prevPosition.x);
			//float maxY = max(destPosition.y, prevPosition.y);

			//float minX = min(destPosition.x, prevPosition.x);
			//float minY = min(destPosition.y, prevPosition.y);

			//fStartDistance = (Vector2(maxX, maxY) - Vector2(minX, minY)).Length();

			//vDirection = destPosition - curPosition;
			//vDirection.Normalize();
		}
		float maxX = max(curPosition.x, prevPosition.x);
		float maxY = max(curPosition.y, prevPosition.y);

		float minX = min(curPosition.x, prevPosition.x);
		float minY = min(curPosition.y, prevPosition.y);

		fRemainDistance = (Vector2(maxX, maxY) - Vector2(minX, minY)).Length();

		if (fRemainDistance < fStartDistance)
		{
			float fMoveX = curPosition.x + (vDirection.x * fSpeed * Time::fDeltaTime());
			float fMoveY = curPosition.y + (vDirection.y * fSpeed * Time::fDeltaTime());
			SET_POS_XYZ(this, fMoveX, fMoveY, curPosition.z);
		}
	}
	void Monster::LateUpdate()
	{
		MoveAbleObject::LateUpdate();
	}
	void Monster::Render()
	{
		MoveAbleObject::Render();
	}
	void Monster::Hit(int damage)
	{
		if (hp - damage < 0) hp = 0;
		else hp -= damage;

		hpPercent = hpCapacity - hp / hpCapacity;
		SetHit(true);
	}
}