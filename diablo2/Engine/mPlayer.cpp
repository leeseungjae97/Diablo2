#include "mPlayer.h"
#include "mInput.h"
#include "mTransform.h"
#include "mMeshRenderer.h"
#include "mTime.h"
#include "mCamera.h"
#include "mApplication.h"
#include "mMouseManager.h"

extern m::Application application;
namespace m
{
	Player::Player(Vector3 iniPos)
		: MoveAbleObject(iniPos, 300.f)
		, mHp(nullptr)
		, mMp(nullptr)
	{
		rangeCollider->SetSize(Vector3(1.f, 1.f, 1.f));
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
		MoveAbleObject::Update();
		Vector3 curPosition = GET_POS(this);

		Vector3 unprojMousePos = Input::GetUnprojectionMousePos(destPosition.z
																, GetCamera()->GetPrivateProjectionMatrix(), GetCamera()->GetPrivateViewMatrix());

		Vector2 curCoord = TileManager::GetPlayerPositionCoord();
		Vector2 mouseCoord = TileManager::GetHoverTileCoord();

		mAstar->PathFinding(curCoord, mouseCoord);
		mAstar->Move(this);

		if (Input::GetKeyDownOne(eKeyCode::LBUTTON)
			&& !MouseManager::GetMouseOnUI())
		{
			mAstar->PathChange();
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
	void Player::LateUpdate()
	{
		MoveAbleObject::LateUpdate();
	}
	void Player::Render()
	{
		MoveAbleObject::Render();
	}
}