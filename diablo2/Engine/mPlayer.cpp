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
		: MoveAbleObject(iniPos, 300.f)
		, mHp(nullptr)
		, mMp(nullptr)
	{
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
			float fMoveX = curPosition.x + (vDirection.x * fSpeed * Time::fDeltaTime());
			float fMoveY = curPosition.y + (vDirection.y * fSpeed * Time::fDeltaTime());
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

    void Player::Hit(int damage)
	{
		if (PlayerInfo::hp - damage < 0) PlayerInfo::hp = 0;
		else PlayerInfo::hp -= damage;

		PlayerInfo::CalHpPercent();
		mHp->SetUVCoord(PlayerInfo::hpPercent);

		SetHit(true);
	}

    void Player::UseMana(int mana)
    {
		if (PlayerInfo::mp - mana < 0) PlayerInfo::mp = 0;
		else PlayerInfo::mp -= mana;

		PlayerInfo::CalMpPercent();
		mMp->SetUVCoord(PlayerInfo::mpPercent);
    }

    void Player::RestoreHp(int hp)
    {
		if(PlayerInfo::hp + hp < PlayerInfo::hpCapacity)
		{
			PlayerInfo::hp += hp;
		}else
		{
			PlayerInfo::hp = PlayerInfo::hpCapacity;
		}
		PlayerInfo::CalHpPercent();
		mHp->SetUVCoord(PlayerInfo::hpPercent);
    }

    void Player::RestoreMp(int mp)
    {
		if (PlayerInfo::mp + mp < PlayerInfo::mpCapacity)
		{
			PlayerInfo::mp += mp;
		}
		else
		{
			PlayerInfo::mp = PlayerInfo::mpCapacity;
		}
		PlayerInfo::CalMpPercent();
		mMp->SetUVCoord(PlayerInfo::mpPercent);
    }
}
