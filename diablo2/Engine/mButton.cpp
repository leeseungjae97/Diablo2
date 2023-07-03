#include "mButton.h"

#include "..\engine_source\mTransform.h"
#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mCamera.h"
#include "..\engine_source\mInput.h"
#include "..\engine_source\mMouseManager.h"
#include "..\engine_source\mApplication.h"

extern m::Application application;
namespace m
{
	Button::Button()
		: bClick(false)
	{}
	Button::~Button()
	{}
	void Button::Initialize()
	{}
	void Button::Update()
	{
		UI::Update();
		MeshRenderer* mr = GetComponent<MeshRenderer>();

		if (GetHover())
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
		UI::LateUpdate();
	}
	void Button::Render()
	{
		UI::Render();
	}
}