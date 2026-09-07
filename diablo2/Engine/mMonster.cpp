#include "mMonster.h"

#include "../engine_source/ItemLookUpTables.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTime.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/mStashManager.h"
#include "../engine_source/mTileManager.h"

#include "mPlayerManager.h"
#include "mPlayer.h"
#include "mPlayerStatus.h"
#include "mShadowObject.h"
#include "mSkillOverlay.h"

namespace m
{
	Monster::Monster(Vector3 iniPos, float speed)
		: MoveAbleObject(iniPos, speed)
		, mMonsterClass(eMonsterClass::Normal)
		, hp(100.f)
		, hpCapacity(100.f)
	    , fCenterPosY(0.f)
		, hpPercent((hpCapacity - hp) / hpCapacity)
		, mNextMoveCoord(Vector2(-1.f, -1.f))
		, mReservedNextMoveCoord(Vector2(-1.f, -1.f))
		, bHasNextMoveReservation(false)
		, bNeedPathRebuild(true)
		, fPathRebuildAcc(0.f)
		, fStuckAcc(0.f)
	{
		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");
		ADD_COMP(this, Animator);
		ADD_COMP(this, AudioSource);

		MonsterManager::AddMonster(this);
		MeshRenderer* mr = GET_COMP(this, MeshRenderer);
		mr->AddTrappingColorBuffer();

		sightCollider = ADD_COMP(this, Collider2D);
		sightCollider->SetType(eColliderType::Circle);
		//sightCollider->SetSize(Vector3(5.f, 5.f, 1.f));
		sightCollider->SetScale(Vector3(1000.f, 1000.f, 1.f));
		sightCollider->AddExceptType(eLayerType::Skill);
		sightCollider->AddExceptType(eLayerType::MonsterSkill);
		sightCollider->AddExceptType(eLayerType::PlayerSkill);

		sightCollider->SetColliderFunctionType(eColliderFunctionType::Sight);

		rangeCollider->SetSize(Vector3(1.0f, 1.0f, 1.5f));

		bodyBoxCollider->SetSize(Vector3(0.3f, 0.5f, 1.f));

		tilePositionCollider->AddExceptType(eLayerType::MonsterSkill);
		bodyBoxCollider->AddExceptType(eLayerType::MonsterSkill);

		mPathFinder->SetMonsterOwner(this);
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

		if (mShadow)
			mShadow->SetState(Delete);
	}
	bool Monster::Arrival()
	{
		return CanMeleeAttackPlayerByTile();
	}

	bool Monster::CanMeleeAttackPlayerByTile()
	{
		Vector2 curCoord = GetCoord();
		Vector2 playerCoord = TileManager::GetPlayerPositionCoord();

		int dx = abs(static_cast<int>(curCoord.x) - static_cast<int>(playerCoord.x));
		int dy = abs(static_cast<int>(curCoord.y) - static_cast<int>(playerCoord.y));

		return dx <= 1 && dy <= 1 && (dx != 0 || dy != 0);
	}
	void Monster::ReserveNextMoveCoord(Vector2 coord)
	{
		if (bHasNextMoveReservation && mReservedNextMoveCoord == coord)
			return;

		ClearNextMoveReservation();
		if (!MonsterManager::ReserveMoveTile(this, coord))
		{
			RequestPathRebuild();
			return;
		}

		mReservedNextMoveCoord = coord;
		mNextMoveCoord = coord;
		bHasNextMoveReservation = true;
	}

	void Monster::ClearNextMoveReservation()
	{
		if (!bHasNextMoveReservation && !MonsterManager::HasMoveTileReservation(this))
			return;

		MonsterManager::ReleaseMoveTile(this);
		mReservedNextMoveCoord = Vector2(-1.f, -1.f);
		bHasNextMoveReservation = false;
	}

	Vector2 Monster::selectApproachCoord(Vector2 playerCoord, Vector2 curCoord)
	{
		static const int offsets[][2] = {
			{ 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 },
			{ 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 }
		};

		const int count = sizeof(offsets) / sizeof(offsets[0]);
		int startIndex = monsterId < 0 ? 0 : monsterId % count;
		Vector2 bestCoord = CanMeleeAttackPlayerByTile() ? curCoord : playerCoord;
		int bestScore = INT_MAX;

		for (int n = 0; n < count; ++n)
		{
			int index = (startIndex + n) % count;
			int x = static_cast<int>(playerCoord.x) + offsets[index][0];
			int y = static_cast<int>(playerCoord.y) + offsets[index][1];

			if (y < 0 || x < 0
				|| y >= TileManager::pathFindingTiles.size()
				|| x >= TileManager::pathFindingTiles[y].size())
				continue;

			Tile* tile = TileManager::pathFindingTiles[y][x];
			Vector2 candidate = Vector2(x, y);
			bool ownCurrent = candidate == curCoord;

			if (tile->GetIsWall())
				continue;
			if (tile->GetOnMonster() && !ownCurrent)
				continue;
			if (MonsterManager::IsMoveTileReservedByOther(this, candidate))
				continue;

			int dist = static_cast<int>(abs(candidate.x - curCoord.x) + abs(candidate.y - curCoord.y));
			int score = dist * 10 + n;

			if (score < bestScore)
			{
				bestScore = score;
				bestCoord = candidate;
			}
		}

		return bestCoord;
	}

	bool Monster::shouldRebuildPath(Vector2 curCoord, Vector2 targetCoord)
	{
		if (bNeedPathRebuild)
			return true;
		if (curCoord != prevCurCoord)
			return true;
		if (targetCoord != prevTargetCoord)
			return true;
		if (mPathFinder && mPathFinder->GetPath().empty())
			return true;
		if (fStuckAcc > 0.25f)
			return true;
		if (fPathRebuildAcc > 0.5f)
			return true;

		return false;
	}

	void Monster::Initialize()
	{
		MoveAbleObject::Initialize();
	}

	void Monster::Update()
	{
		
		MoveAbleObject::Update();
		if (GetBattleState() == eBattleState::ToDead)
		{
			MonsterManager::AddDeadMonster(this);
			//SetState(eState::RenderNoUpdate);
			if (mHSO)
			{
				mHSO->SetState(eState::Delete);
			}
			if (mShadow)
			{
				mShadow->SetState(eState::Delete);
			}
			Release();
			

			if (mPathFinder)
			{
				ClearNextMoveReservation();
				mPathFinder->Release();

				getReward();

				delete mPathFinder;
				mPathFinder = nullptr;
			}
			return;
		}
		if (GetBattleState() == eBattleState::Dead)
		{
			if (mHSO)
			{
				mHSO->SetState(eState::Delete);
			}
			if (mShadow)
			{
				mShadow->SetState(eState::Delete);
			}

			return;
		}

		if (mShadow && nullptr == mShadow->GetCamera()) mShadow->SetCamera(GetCamera());

		if(mHSO && nullptr == mHSO->GetCamera())
		{
			mHSO->SetActiveOwner(this);
		}

		Vector3 curPosition = GET_POS(this);

		Vector2 curCoord = GetCoord();
		Vector2 playerCoord = TileManager::GetPlayerPositionCoord();
		Vector2 targetCoord = selectApproachCoord(playerCoord, curCoord);
		bool canMeleeAttack = CanMeleeAttackPlayerByTile();
		fPathRebuildAcc += Time::fDeltaTime();

		if (canMeleeAttack)
		{
			ClearNextMoveReservation();
			mPathFinder->ClearPath();
		}

		if (!canMeleeAttack && shouldRebuildPath(curCoord, targetCoord))
		{
			if (sightCollider->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
			{
				ClearNextMoveReservation();
				mPathFinder->ClearPath();

				if (mMonsterClass == eMonsterClass::Boss)
				{
					mPathFinder->AstarPathFinding(curCoord, targetCoord, 20, true);
				}
				else
				{
					mPathFinder->AstarPathFinding(curCoord, targetCoord, 10, true);
				}

				prevCurCoord = curCoord;
				prevTargetCoord = targetCoord;

				bool moveAdjacent = targetCoord == playerCoord;
				if (mPathFinder->PathChange(moveAdjacent))
				{
					destCoord = mPathFinder->GetTargetCoord();
					ClearPathRebuildRequest();
					fPathRebuildAcc = 0.f;
				}
				else
				{
					RequestPathRebuild();
				}
			}
		}
		bMove = !canMeleeAttack;
		if (bMove)
		{
			mPathFinder->MonsterMove(this);
		}
		
		if (mMonsterClass != eMonsterClass::Boss
			&& GetBattleState() == eBattleState::Hit)
		{
			fStartDistance = fRemainDistance;
			destPosition = TileManager::GetPlayerPosition();
			bMove = false;
		}
		if (GetBattleState() == eBattleState::Attack
			&& !CanMeleeAttackPlayerByTile())
		{
			SetBattleState(eBattleState::Idle);
			RequestPathRebuild();
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
		if (bMove && fStartDistance > 0.f && fRemainDistance >= fStartDistance)
		{
			fStuckAcc += Time::fDeltaTime();
		}
		else
		{
			fStuckAcc = 0.f;
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
		if (hp <= 0) return;

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
	void Monster::getReward()
	{
		PlayerStatus::experiance += 250;
		Vector3 pos = GET_POS(this);
		int iRandCount = rand() % 3;

		int randTable[3] = {
			(int)eItem::hpPotion1,
			(int)eItem::mpPotion1,
			(int)eItem::gold,
		};
		for(int i = 0 ; i < iRandCount; ++i )
		{
			int randDropItem = rand() % 3;
			int index = randTable[randDropItem];
			StashManager::DropFieldItem(index, pos);

			int randXSign = rand() % 2;
			int randYSign = rand() % 2;

			if (randXSign) randXSign *= -1;
			if (randYSign) randYSign *= -1;

			pos.x += i + 10 * randXSign;
			pos.y += i + 10 * randYSign;
		}
	}
}





