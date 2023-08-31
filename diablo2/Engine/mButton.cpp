#include "mButton.h"

#include "../engine_source/mTransform.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mCamera.h"
#include "../engine_source/mInput.h"
#include "../engine_source/mMouseManager.h"
#include "../engine_source/mApplication.h"
#include "../engine_source/mSceneManager.h"

extern m::Application application;
namespace m
{
	Button::Button()
		: bClick(false)
		, bCanClick(true)
	{
	}

	Button::Button(bool useDefaultMeshRenderer)
		: UI(useDefaultMeshRenderer)
	{
	}

	Button::~Button()
	{
	}
	void Button::Initialize()
	{
	}
	void Button::Update()
	{
		UI::Update();

		//if (GetState() != GameObject::RenderUpdate) return;
		if (!bCanClick) return;

		MeshRenderer* mr = GetComponent<MeshRenderer>();
		if (GetHover())
		{
			if (Input::GetKeyUp(eKeyCode::LBUTTON))
			{
				bOneClick = true;
			}
		}
		if (GetHover())
		{
			if (Input::GetKey(eKeyCode::LBUTTON))
			{
				bClick = true;

				if (mClickedMaterial)
					mr->SetMaterial(mClickedMaterial);
			}
			if (Input::GetKeyUp(eKeyCode::LBUTTON))
			{
				if (fClickFunctionPtr)
					fClickFunctionPtr();
			}
		}
		if (!Input::GetKey(eKeyCode::LBUTTON))
		{
			bClick = false;
			if (mNormalMaterial)
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