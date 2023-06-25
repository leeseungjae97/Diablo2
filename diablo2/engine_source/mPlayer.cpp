#include "mPlayer.h"
#include "mInput.h"
#include "mTransform.h"
namespace m
{
	Player::Player()
	{}
	Player::~Player()
	{}
	void Player::Initialize()
	{}
	void Player::Update()
	{
		Transform* tr = GetComponent<Transform>();

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			Vector2 mousePos = Input::GetMousePos();
			tr->SetPosition(Vector3(mousePos.x, 900.f - mousePos.y - 81.f, 0.f));
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