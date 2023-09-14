#include "mPlayer.h"
#include "mInput.h"
#include "mTransform.h"
#include "mMeshRenderer.h"
#include "mTime.h"
#include "mCamera.h"
#include "mApplication.h"
#include "mMonsterManager.h"
#include "mMouseManager.h"

extern m::Application application;
namespace m
{
	Player::Player(Vector3 iniPos)
		: MoveAbleObject(iniPos, 500.f)
		, mHp(nullptr)
		, mMp(nullptr)
		, bCanDamaged(false)
		, fCanDamagedDelay(0.f)
		, bAddiction(false)
		, fAddictionTime(0.f)
	    , fAddictionTickCount(0)
		, iAddictionDamage(0)
		, fAcc(0.f)
	    , fTotalAcc(0.f)
	    , iPastTick(0)
	    , fAccDamage(0)
	{
		bMadePath = false;
		bSixteenDirection = true;
		tilePositionCollider->AddExceptType(eLayerType::PlayerSkill);
		bodyBoxCollider->AddExceptType(eLayerType::PlayerSkill);
		//rangeCollider->SetSize(Vector3(1.f, 1.f, 1.f));
	}
	Player::~Player()
	{

	}
	void Player::Initialize()
	{
		MoveAbleObject::Initialize();
	}
	void Player::Update()
	{
		Vector3 curPosition = GET_POS(this);
		destPosition.z = curPosition.z;
		prevPosition.z = curPosition.z;
		if (nullptr == TileManager::hoverTile) return;
		Vector2 curCoord = TileManager::GetPlayerPositionCoord();
		Vector2 targetCoord = TileManager::GetHoverTileCoord();

		if (GetBattleState() == eBattleState::Cast
			|| GetBattleState() == eBattleState::Dead
			|| GetBattleState() == eBattleState::Attack
			|| GetBattleState() == eBattleState::Hit)
		{
			fStartDistance = fRemainDistance;
			destPosition = curPosition;
			mPathFinder->ClearPath();
		}


		timeWaitAttack();
		attackedAddition();
		
		mPathFinder->PlayerMove(this);

		mPathFinder->AstarPathFinding(curCoord, targetCoord);
		if (!MouseManager::GetMouseOnUI()
			&& Input::GetKeyDown(eKeyCode::RBUTTON))
		{
			Vector3 unprojMousePos = MouseManager::UnprojectionMousePos(destPosition.z, GetCamera());
			Vector3 tempPrev = GET_POS(this);
			Vector3 tempDest = Vector3(unprojMousePos.x, unprojMousePos.y, destPosition.z);

			//float maxX = max(tempDest.x, tempPrev.x);
			//float maxY = max(tempDest.y, tempPrev.y);

			//float minX = min(tempDest.x, tempPrev.x);
			//float minY = min(tempDest.y, tempPrev.y);

			vDirection = tempDest - tempPrev;
			vDirection.Normalize();
		}
		if (!MouseManager::GetMouseOnUI()
			&& nullptr == MouseManager::GetMouseFollow()
			&& Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			if (!mPathFinder->PathChange(false))
			{
				if (!TileManager::hoverTile->GetIsWall())
				{
					Vector3 unprojMousePos = MouseManager::UnprojectionMousePos(destPosition.z, GetCamera());
					prevPosition = GET_POS(this);
					destPosition = Vector3(unprojMousePos.x, unprojMousePos.y, destPosition.z);

					float maxX = max(destPosition.x, prevPosition.x);
					float maxY = max(destPosition.y, prevPosition.y);

					float minX = min(destPosition.x, prevPosition.x);
					float minY = min(destPosition.y, prevPosition.y);

					SetStartDistance((Vector2(maxX, maxY) - Vector2(minX, minY)).Length());

					vDirection = destPosition - prevPosition;
					vDirection.Normalize();
				}
			}
		}
		float maxX = max(curPosition.x, prevPosition.x);
		float maxY = max(curPosition.y, prevPosition.y);

		float minX = min(curPosition.x, prevPosition.x);
		float minY = min(curPosition.y, prevPosition.y);

		fRemainDistance = (Vector2(maxX, maxY) - Vector2(minX, minY)).Length();

		//if (GetBattleState() == eBattleState::Dead
		//	|| GetBattleState() == eBattleState::Attack
		//	|| GetBattleState() == eBattleState::Cast
		//	|| GetBattleState() == eBattleState::Hit)
		//{
		//	fSpeed = 0.0f;
		//}
		if (fRemainDistance < fStartDistance)
		{
			float fMoveX = curPosition.x + (vDirection.x * fAdjustSpeed * Time::fDeltaTime());
			float fMoveY = curPosition.y + (vDirection.y * fAdjustSpeed * Time::fDeltaTime());
			SET_POS_XYZ(this, fMoveX, fMoveY, curPosition.z);
		}
		MoveAbleObject::Update();
	}
	void Player::LateUpdate()
	{
		MoveAbleObject::LateUpdate();
	}
	void Player::Render()
	{
		MoveAbleObject::Render();
	}
	void Player::timeWaitAttack()
	{
		if (!bCanDamaged)
			fCanDamagedDelay += Time::fDeltaTime();

		if (fCanDamagedDelay >= 1.f)
		{
			bCanDamaged = true;
			fCanDamagedDelay = 0.f;
		}
	}

    void Player::attackedAddition()
    {
		if (bAddiction)
		{
			fAcc += Time::fDeltaTime();
			//fTotalAcc += fAcc;

			if(fAcc >= fAddictionTime / (float)fAddictionTickCount)
			{
				//++iPastTick;
				fAccDamage += iAddictionDamage / fAddictionTickCount;
				Hit(iAddictionDamage / fAddictionTickCount, false);
				fAcc = 0.f;
			}
			if (fAccDamage >= iAddictionDamage)
			{
				bAddiction = false;
				fAcc = 0.f;
				fAccDamage = 0.f;
				//fTotalAcc = 0.f;
				//iPastTick = 0;
				mHp->SetOrigin();
			}
		}
    }

    void Player::Hit(int damage, bool attackStun)
	{
		if (bCanDamaged)
		{
			bCanDamaged = false;

			if (PlayerManager::hp - damage < 0) PlayerManager::hp = 0;
			else PlayerManager::hp -= damage;

			PlayerManager::CalHpPercent();
			mHp->SetUVCoord(PlayerManager::hpPercent);

			if(attackStun)
			    SetHit(true);
		}
	}

	void Player::UseMana(int mana)
	{
		if (PlayerManager::mp - mana < 0) PlayerManager::mp = 0;
		else PlayerManager::mp -= mana;

		PlayerManager::CalMpPercent();
		mMp->SetUVCoord(PlayerManager::mpPercent);
	}

	void Player::RestoreHp(int hp)
	{
		if (PlayerManager::hp + hp < PlayerManager::hpCapacity)
		{
			PlayerManager::hp += hp;
		}
		else
		{
			PlayerManager::hp = PlayerManager::hpCapacity;
		}
		PlayerManager::CalHpPercent();
		mHp->SetUVCoord(PlayerManager::hpPercent);
	}

	void Player::RestoreMp(int mp)
	{
		if (PlayerManager::mp + mp < PlayerManager::mpCapacity)
		{
			PlayerManager::mp += mp;
		}
		else
		{
			PlayerManager::mp = PlayerManager::mpCapacity;
		}
		PlayerManager::CalMpPercent();
		mMp->SetUVCoord(PlayerManager::mpPercent);
	}

	void Player::Addiction(int damage, float addictionTime, int tickCount)
	{
		if(bAddiction)
		{
			fAddictionTickCount += (float)tickCount;
			fAddictionTime += addictionTime;
			iAddictionDamage += damage;
		}else
		{
			fAddictionTickCount = (float)tickCount;
			fAddictionTime = addictionTime;

			iAddictionDamage = damage;

			bAddiction = true;
			mHp->SetAddiction();
		}
		
	}
}
