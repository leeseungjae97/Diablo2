#include "mButton.h"
#include "mTransform.h"
#include "mMeshRenderer.h"
#include "mCamera.h"
#include "mInput.h"

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
		Vector3 trPos = Vector3(tr->GetPosition().x, -tr->GetPosition().y, tr->GetPosition().z);

		Vector2 mousePos = Input::GetMousePos();
		Vector3 mousePos3 = Vector3(mousePos.x, mousePos.y, mScale.z);

		//GetDevice()->GetD3D11Viewport();
		//Viewport::Unproject();

		//Viewport viewport;
		//viewport.x = 0.f;
		//viewport.y = 0.f;
		//viewport.height = 900.f;
		//viewport.width = 1600.f;
		//viewport.maxDepth = 1.f;
		//viewport.minDepth = -1.f;

		//Vector3 unpojection = viewport.Unproject(tr->GetPosition(), Camera::GetProjectionMatrix(), Camera::GetViewMatrix(), Matrix::Identity);

		if ((fabs(trPos.x - mousePos.x)) <= mScale.x
			&& (fabs(trPos.y - mousePos.y)) <= mScale.y)
		{
			bHover = true;
		}
		else bHover = false;

		if (bHover)
		{
			if (Input::GetKeyDown(eKeyCode::LBUTTON))
			{
				bClick = true;
				mr->SetMaterial(mClickedMaterial);
			}
		}
		if (Input::GetKeyUp(eKeyCode::LBUTTON))
		{
			bClick = false;
			mr->SetMaterial(mNormalMaterial);
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