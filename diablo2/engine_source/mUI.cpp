#include "mUI.h"

#include "..\engine_source\mTransform.h"
#include "..\engine_source\mCamera.h"
#include "..\engine_source\mInput.h"
#include "..\engine_source\mMouseManager.h"
#include "..\engine_source\mApplication.h"

extern m::Application application;
namespace m
{
	UI::UI()
		//: bHover(false)
	{}
	UI::~UI()
	{}
	void UI::Initialize()
	{}
	void UI::Update()
	{
		GameObject::Update();
		//Transform* tr = GetComponent<Transform>();
		//Vector3 mScale = tr->GetScale();

		//Viewport viewport = application.GetViewport();

		//Matrix proj = Matrix::Identity;
		//Matrix view = Matrix::Identity;

		//if (nullptr == GetCamera())
		//{
		//	proj = Camera::GetProjectionMatrix();
		//	view = Camera::GetViewMatrix();
		//}
		//else
		//{
		//	proj = GetCamera()->GetPrivateProjectionMatrix();
		//	view = GetCamera()->GetPrivateViewMatrix();
		//}

		//Vector3 unprojMousePos = Input::GetUnprojectionMousePos(mScale.z, viewport, proj, view);

		//if (Vector2::OnMouseVector2Rect(Vector2(tr->GetPosition().x, tr->GetPosition().y)
		//	, Vector2(mScale.x, mScale.y)
		//	, Vector2(unprojMousePos.x, unprojMousePos.y)))
		//{
		//	bHover = true;
		//}
		//else
		//{
		//	bHover = false;
		//}
	}
	void UI::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void UI::Render()
	{
		GameObject::Render();
	}
}