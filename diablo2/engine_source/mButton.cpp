#include "mButton.h"
#include "mTransform.h"
#include "mMeshRenderer.h"
#include "mCamera.h"
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
		MeshRenderer* mr = GetComponent<MeshRenderer>();
		Vector3 mScale = tr->GetScale();
		Vector2 trPos = Vector2(tr->GetPosition().x, tr->GetPosition().y);
		Vector2 mousePos = Input::GetMousePos();

		Vector2 vCen = Camera::GetCameraCenter();

		if (fabs((trPos.x - mousePos.x) < mScale.x)
			&& fabs((trPos.y - mousePos.y) < mScale.y))
		{
			bHover = true;
		}

		if (trPos == (mousePos + vCen))
		{
			
			if (Input::GetKey(eKeyCode::LBUTTON))
			{
				bClick = true;
				mr->SetMaterial(mClickedMaterial);
			}
		}
		else
		{
			bHover = false;
			mr->SetMaterial(mNormalMaterial);
		}

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