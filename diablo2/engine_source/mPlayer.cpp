#include "mPlayer.h"
#include "mInput.h"
#include "mTransform.h"
#include "mMeshRenderer.h"
#include "mTime.h"
#include "mCamera.h"

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
		Vector3 scale = tr->GetScale();
		

		Viewport viewport;
		viewport.x = 0.f;
		viewport.y = 0.f;
		viewport.height = 900.f;
		viewport.width = 1600.f;
		viewport.maxDepth = 1.f;
		viewport.minDepth = -1.f;

		Vector3 unpojection = viewport.Unproject(tr->GetPosition(), Camera::GetProjectionMatrix(), Camera::GetViewMatrix(), Matrix::Identity);

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			prevPosition = tr->GetPosition();

			Vector2 mousePos = Input::GetMousePos();
			destPosition = Vector3(mousePos.x - vS.x, 900.f - mousePos.y - vS.y, 0.f);

			fStartDistance = abs((destPosition - prevPosition).Length());

			vDirection = destPosition - curPosition;
			vDirection.Normalize();
		}

		fRemainDistance = abs((curPosition - prevPosition).Length());
		
		if (fRemainDistance <= fStartDistance)
		{
			float fMoveX = curPosition.x + (vDirection.x * fSpeed * Time::DeltaTime());
			float fMoveY = curPosition.y + (vDirection.y * fSpeed * Time::DeltaTime());
			tr->SetPosition(Vector3(fMoveX, fMoveY, 0.f));
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