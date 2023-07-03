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
		: prevPosition(Vector3::Zero)
		, destPosition(iniPos)
		, vS(iniPos)
		, fSpeed(300.f)
		, fStartDistance(0.f)
		, fRemainDistance(0.f)
	{
		GetComponent<Transform>()->SetPosition(iniPos);
	}
	Player::~Player()
	{}
	void Player::Initialize()
	{}
	void Player::Update()
	{
		Transform* tr = GetComponent<Transform>();

		Vector3 curPosition = tr->GetPosition();

		Viewport viewport = application.GetViewport();

		Vector3 unprojMousePos = Input::GetUnprojectionMousePos(destPosition.z
			, viewport, GetCamera()->GetPrivateProjectionMatrix(), GetCamera()->GetPrivateViewMatrix());

		if (Input::GetKeyDown(eKeyCode::LBUTTON)
			&& !MouseManager::GetMouseOnUI())
		{
			prevPosition = tr->GetPosition();

			destPosition = Vector3(unprojMousePos.x, unprojMousePos.y, destPosition.z);

			fStartDistance = abs((destPosition - prevPosition).Length());

			vDirection = destPosition - curPosition;
			vDirection.Normalize();
		}

		fRemainDistance = abs((curPosition - prevPosition).Length());

		if (fRemainDistance <= fStartDistance)
		{
			float fMoveX = curPosition.x + (vDirection.x * fSpeed * Time::fDeltaTime());
			float fMoveY = curPosition.y + (vDirection.y * fSpeed * Time::fDeltaTime());
			tr->SetPosition(Vector3(fMoveX, fMoveY, curPosition.z));
		}

		GameObject::Update();
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