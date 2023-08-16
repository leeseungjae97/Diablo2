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
		, hp(100.f)
		, hpCapacity(100.f)
		, hpPercent(100.f)
	{
		monsterId = MonsterManager::DispendMonsterId();
		MonsterManager::AddMonster(this);

		sightCollider = ADD_COMP(this, Collider2D);
		sightCollider->SetType(eColliderType::Circle);
		sightCollider->SetSize(Vector3(5.f, 5.f, 1.f));
		sightCollider->AddExceptType(eLayerType::Skill);
		sightCollider->SetColliderFunctionType(eColliderFunctionType::Sight);

		rangeCollider->SetSize(Vector3(1.0f, 1.0f, 1.5f));

		hitAreaCollider->SetSize(Vector3(0.5f, 0.5f, 1.f));

		tilePositionCollider->AddExceptType(eLayerType::MonsterSkill);
		hitAreaCollider->AddExceptType(eLayerType::MonsterSkill);
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
		if (hp == 0)
		{
			std::erase(MonsterManager::monsters, this);
			SetState(eState::Delete);
			return;
		}

		Vector3 curPosition = GET_POS(this);

		Vector2 curCoord = GetCoord();
		Vector2 targetCoord = TileManager::GetPlayerPositionCoord();

		mAstar->PathFinding(curCoord, targetCoord, 20);
		mAstar->MonsterMove(this);

		if (sightCollider->GetOnEnter()
			|| sightCollider->GetOnStay())
		{
			if (sightCollider->SearchObjectGameObjectId(PlayerInfo::player->GetGameObjectId()))
			{
				mAstar->PathChange();
			}
		}

		float maxX = max(curPosition.x, prevPosition.x);
		float maxY = max(curPosition.y, prevPosition.y);

		float minX = min(curPosition.x, prevPosition.x);
		float minY = min(curPosition.y, prevPosition.y);

		fRemainDistance = (Vector2(maxX, maxY) - Vector2(minX, minY)).Length();

		if (GetBattleState() == eBattleState::Dead
			|| GetBattleState() == eBattleState::Attack
			//|| GetBattleState() == eBattleState::Hit
			|| GetBattleState() == eBattleState::Cast
			)
		{
			fStartDistance = fRemainDistance;
			destPosition = GET_POS(TileManager::playerStandTile);
		}
		if (rangeCollider->GetOnEnter()
			|| rangeCollider->GetOnStay())
		{
			fStartDistance = fRemainDistance;
		}
		if (fRemainDistance < fStartDistance)
		{
			float fMoveX = curPosition.x + (vDirection.x * fSpeed * Time::fDeltaTime());
			float fMoveY = curPosition.y + (vDirection.y * fSpeed * Time::fDeltaTime());
			SET_POS_XYZ(this, fMoveX, fMoveY, curPosition.z);
		}
		//MoveAbleObject::Update();
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