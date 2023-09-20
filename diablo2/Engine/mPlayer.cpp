#include "mPlayer.h"
#include "mInput.h"
#include "mTransform.h"
#include "mMeshRenderer.h"
#include "mTime.h"
#include "mCamera.h"
#include "mApplication.h"
#include "mFontWrapper.h"
#include "mMonsterManager.h"
#include "mMouseManager.h"
#include "mTrappingColor.h"

extern m::Application application;
namespace m
{
	Player::Player(Vector3 iniPos)
		: MoveAbleObject(iniPos, 500.f)
		, mHp(nullptr)
		, mMp(nullptr)
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
		playerMove();
		updateColliderPos();
		MoveAbleObject::Update();
	}
	void Player::LateUpdate()
	{
		MoveAbleObject::LateUpdate();
	}
	void Player::Render()
	{
		MoveAbleObject::Render();

		wchar_t szFloat[100] = {};
		swprintf_s(szFloat, 100, L"Player Coord(x) : %f\n Player Coord(y) : %f"
			, TileManager::GetPlayerPositionCoord().x, TileManager::GetPlayerPositionCoord().y);

		FontWrapper::DrawFont(szFloat, 10, 10, 10.f, FONT_RGBA(255, 0, 255, 255));

		swprintf_s(szFloat, 100, L"Player Position(x) : %f\n Player Position(y) : %f"
			, TileManager::GetPlayerPosition().x, TileManager::GetPlayerPosition().y);

		FontWrapper::DrawFont(szFloat, 10, 40, 10.f, FONT_RGBA(255, 0, 255, 255));
	}

	//void Player::timeWaitAttack()
	//{
		//if (!bCanDamaged)
		//	fCanDamagedDelay += Time::fDeltaTime();

		//if (fCanDamagedDelay >= 1.f)
		//{
		//	bCanDamaged = true;
		//	fCanDamagedDelay = 0.f;
		//}
	//}

    void Player::AttackedAddition()
    {
		MoveAbleObject::AttackedAddition();
		if(bAddiction)
		{
			if (fAccDamage >= iAddictionDamage)
			{
				mHp->SetOrigin();
			}
		}
    }

    void Player::playerMove()
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

		if (bStun)
		{
			fAccStun += Time::fDeltaTime();
			if (fAccStun >= fStunSecond)
			{
				bStun = false;
				fAccStun = 0.f;
				fStunSecond = 0.f;
			}
		}
		if (bAddiction) mHp->SetAddiction();

		if (bCallSetNumericalAdjustmentSpeed)
		{
			fNASAcc -= Time::fDeltaTime();
			if (fNASAcc <= 0.f)
			{
				fNumericalAdjustmentSpeed = 0.f;
				bCallSetNumericalAdjustmentSpeed = false;
			}
		}


		TimeWaitAttack();
		AttackedAddition();

		if (mPathFinder->PlayerMove(this))
		{

		}

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
			&& !bStun
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
					AdDegree();
					SetAdjustmentDegree();
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


		if (fRemainDistance < fStartDistance && !bStun)
		{
			float fXFinalSpeed = fXAdjustSpeed + fNumericalAdjustmentSpeed;
			float fYFinalSpeed = fYAdjustSpeed + (fNumericalAdjustmentSpeed / 2.f);
			float fMoveX = curPosition.x + (vDirection.x * fXFinalSpeed * Time::fDeltaTime());
			float fMoveY = curPosition.y + (vDirection.y * fYFinalSpeed * Time::fDeltaTime());
			SET_POS_XYZ(this, fMoveX, fMoveY, curPosition.z);
		}
    }

    void Player::updateColliderPos()
    {
		Vector3 scale =GET_SCALE(this);
		Vector2 scaleOffset = Vector2(0.f, scale.y / 3.f);
		rangeCollider->SetCenter(scaleOffset);
		tilePositionCollider->SetCenter(scaleOffset);
		bodyBoxCollider->SetCenter(scaleOffset);
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
}
