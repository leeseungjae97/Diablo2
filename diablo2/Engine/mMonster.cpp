#include "mMonster.h"

#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTime.h"

#include "mPlayerManager.h"
#include "mPlayer.h"
#include "mSceneManager.h"
#include "mShadowObject.h"
#include "mSkillOverlay.h"

namespace m
{
	Monster::Monster(Vector3 iniPos, float speed)
		: MoveAbleObject(iniPos, speed)
		, mMonsterClass(eMonsterClass::Normal)
		, hp(100.f)
		, hpCapacity(100.f)
	{
		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");
		ADD_COMP(this, Animator);

		hpPercent = (hpCapacity - hp) / hpCapacity;

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
		ADD_COMP(this, Animator);
		mHSO = new SkillOverlay();
		mHSO->SetActiveOwner(this);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Overlay, mHSO);

		mShadow = new ShadowObject(this);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Shadow, mShadow);
	}
	Monster::~Monster()
	{
		if (mHSO)
			mHSO->SetState(Delete);
	}
	void Monster::Initialize()
	{
		MoveAbleObject::Initialize();
	}

	void Monster::Update()
	{
		MoveAbleObject::Update();
		if (nullptr == mShadow->GetCamera()) mShadow->SetCamera(GetCamera());

		if(nullptr == mHSO->GetCamera())
		{
			mHSO->SetActiveOwner(this);
		}

		//if (hp == 0)
		if (GetBattleState() == eBattleState::Dead)
		{
			//Dead end -> Delete
			MonsterManager::EraseMonster(this);
			SetState(eState::RenderNoUpdate);
			mHSO->SetState(eState::Delete);
			mShadow->SetState(eState::Delete);

			if(mPathFinder)
			    delete mPathFinder;
			return;
		}
		if (GetBattleState() == eBattleState::ToDead)
			return;

		Vector3 curPosition = GET_POS(this);

		Vector2 curCoord = GetCoord();
		Vector2 targetCoord = TileManager::GetPlayerPositionCoord();
		
		
		if (targetCoord != prevTargetCoord
			|| destCoord != mPathFinder->GetTargetCoord())
		if (sightCollider->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
		{
			//bool move = mPathFinder->MonsterMove(this);

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
			destCoord = mPathFinder->GetTargetCoord();
		}
		bMove = true;
		mPathFinder->MonsterMove(this);
		
		
		
		if (mMonsterClass != eMonsterClass::Boss
			&& GetBattleState() == eBattleState::Hit)
		{
			fStartDistance = fRemainDistance;
			destPosition = TileManager::GetPlayerPosition();
			bMove = false;
		}
		if (GetBattleState() == eBattleState::Dead
			|| GetBattleState() == eBattleState::Attack
			|| GetBattleState() == eBattleState::Cast)
		{
			fStartDistance = fRemainDistance;
			destPosition = TileManager::GetPlayerPosition();
			bMove = false;
		}

		float maxX = max(curPosition.x, prevPosition.x);
		float maxY = max(curPosition.y, prevPosition.y);

		float minX = min(curPosition.x, prevPosition.x);
		float minY = min(curPosition.y, prevPosition.y);

		fRemainDistance = (Vector2(maxX, maxY) - Vector2(minX, minY)).Length();

		if(!bMove)
		{
			destPosition = TileManager::GetPlayerPosition();
		}
		if (fRemainDistance < fStartDistance && bMove)
		{
			SetAdjustmentDegree();

			if (fNASAcc <= 0.f)
			{
				fNumericalAdjustmentSpeed = 0.f;
			}

			float fXFinalSpeed = fXAdjustSpeed + fNumericalAdjustmentSpeed;
			float fYFinalSpeed = fYAdjustSpeed + fNumericalAdjustmentSpeed;
			float fMoveX = curPosition.x + (vDirection.x * fXFinalSpeed * Time::fDeltaTime());
			float fMoveY = curPosition.y + (vDirection.y * fYFinalSpeed * Time::fDeltaTime());
			SET_POS_XYZ(this, fMoveX, fMoveY, curPosition.z);
		}

		if(bMove)
		{
			
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

			hpPercent = (hpCapacity - hp) / hpCapacity;
			if(attackStun)
			    SetHit(true);
		}
	}
}
