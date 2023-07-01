#include "mButton.h"

#include "..\engine_source\mTransform.h"
#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mCamera.h"
#include "..\engine_source\mInput.h"

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
		Vector3 trPos = Vector3(tr->GetPosition().x, tr->GetPosition().y, tr->GetPosition().z);

		Vector2 mousePos = Input::GetMousePos();
		Vector3 mousePos3 = Vector3(mousePos.x, mousePos.y, mScale.z);

		Viewport viewport;
		viewport.x = 0.f;
		viewport.y = 0.f;
		viewport.height = 900.f;
		viewport.width = 1600.f;
		viewport.maxDepth = 1000.f;
		viewport.minDepth = -1.f;

		Vector3 unprojMousePos = viewport.Unproject(mousePos3, GetCamera()->GetProjectionMatrix(), GetCamera()->GetViewMatrix(), Matrix::Identity);

		Vector2 sp = Vector2(trPos.x, fabs(trPos.y));
		Vector2 lp = Vector2(trPos.x + mScale.x, fabs(trPos.y) + mScale.y);
		if (sp <= Vector2(unprojMousePos.x , fabs(unprojMousePos.y))
			&& lp >= Vector2(unprojMousePos.x, fabs(unprojMousePos.y)))
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