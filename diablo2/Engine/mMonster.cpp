#include "mMonster.h"

#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTime.h"

#include "mPlayerManager.h"
#include "mPlayer.h"

namespace m
{
	Monster::Monster(Vector3 iniPos, float speed)
		: MoveAbleObject(iniPos, speed)
		, mMonsterClass(eMonsterClass::Normal)
		, hp(100.f)
		, hpCapacity(100.f)
		, hpPercent(100.f)
	{
		MonsterManager::AddMonster(this);

		sightCollider = ADD_COMP(this, Collider2D);
		sightCollider->SetType(eColliderType::Circle);
		sightCollider->SetSize(Vector3(5.f, 5.f, 1.f));
		sightCollider->AddExceptType(eLayerType::Skill);
		sightCollider->AddExceptType(eLayerType::MonsterSkill);
		sightCollider->AddExceptType(eLayerType::PlayerSkill);

		sightCollider->SetColliderFunctionType(eColliderFunctionType::Sight);

		rangeCollider->SetSize(Vector3(1.0f, 1.0f, 1.5f));

		bodyBoxCollider->SetSize(Vector3(0.3f, 0.5f, 1.f));

		tilePositionCollider->AddExceptType(eLayerType::MonsterSkill);
		bodyBoxCollider->AddExceptType(eLayerType::MonsterSkill);

		mPathFinder->SetMonsterOwner(this);
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
			//Dead end -> Delete
			MonsterManager::EraseMonster(this);
			SetState(eState::Delete);
			return;
		}

		Vector3 curPosition = GET_POS(this);

		Vector2 curCoord = GetCoord();
		Vector2 targetCoord = TileManager::GetPlayerPositionCoord();
		//if (bodyBoxCollider->GetOnEnter()
		//	|| bodyBoxCollider->GetOnStay())
		//{
		//	mPathFinder->ClearPath();
		//}

		//if (sightCollider->GetOnEnter()
		//	|| sightCollider->GetOnStay()
		//	&& sightCollider->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
		if (sightCollider->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
		{
			bool move = mPathFinder->MonsterMove(this);

			if(!move)
			{
				if (mMonsterClass == eMonsterClass::Boss)
				{
					mPathFinder->AstarPathFinding(curCoord, targetCoord, 20);
				}
				else
				{
					mPathFinder->AstarPathFinding(curCoord, targetCoord, 10);
				}

				prevCurCoord = curCoord;
				prevTargetCoord = targetCoord;

				mPathFinder->PathChange(true);
			}
		}
		

		float maxX = max(curPosition.x, prevPosition.x);
		float maxY = max(curPosition.y, prevPosition.y);

		float minX = min(curPosition.x, prevPosition.x);
		float minY = min(curPosition.y, prevPosition.y);

		fRemainDistance = (Vector2(maxX, maxY) - Vector2(minX, minY)).Length();

		if (mMonsterClass != eMonsterClass::Boss
			&& GetBattleState() == eBattleState::Hit)
		{
			fStartDistance = fRemainDistance;
			destPosition = TileManager::GetPlayerPosition();
		}
		if (GetBattleState() == eBattleState::Dead
			|| GetBattleState() == eBattleState::Attack
			|| GetBattleState() == eBattleState::Cast)
		{
			fStartDistance = fRemainDistance;
			destPosition = TileManager::GetPlayerPosition();
		}
		//if (rangeCollider->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
		//{
		//	
		//}
		if(Arrival())
		{
			//fStartDistance = fRemainDistance;
			destPosition = TileManager::GetPlayerPosition();
		}
		if (fRemainDistance < fStartDistance)
		{
			float fMoveX = curPosition.x + (vDirection.x * fAdjustSpeed * Time::fDeltaTime());
			float fMoveY = curPosition.y + (vDirection.y * fAdjustSpeed * Time::fDeltaTime());
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
	void Monster::Hit(int damage, bool attackStun)
	{
		if(bCanDamaged)
		{
			bCanDamaged = false;

			if (hp - damage < 0) hp = 0;
			else hp -= damage;

			hpPercent = hpCapacity - hp / hpCapacity;
			if(attackStun)
			    SetHit(true);
		}
		
	}
}