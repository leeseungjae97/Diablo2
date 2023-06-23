#include "mButton.h"
#include "mTransform.h"

namespace m
{
	Button::Button()
		: bHover(false)
		, bClick(false)
	{}
	Button::~Button()
	{}
	void Button::Initialize()
	{}
	void Button::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();
		Vector2 trPos = Vector2(tr->GetPosition().x, tr->GetPosition().y);
		if (trPos == Input::GetMousePos())
		{
			bHover = true;
			if (Input::GetKey(eKeyCode::LBUTTON))
			{
				bClick = true;
			}
		}
		else bHover = false;

		if (Input::GetKeyUp(eKeyCode::LBUTTON))
		{
			bClick = false;
		}
	}
	void Button::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Button::Render()
	{
		GameObject::Render();
	}
}