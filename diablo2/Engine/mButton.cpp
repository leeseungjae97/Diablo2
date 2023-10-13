#include "mButton.h"

#include "../engine_source/mAudioSource.h"
#include "../engine_source/mSoundManager.h"
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
		ADD_COMP(this, AudioSource);
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
				AudioSource* as = GET_COMP(this, AudioSource);
				if(!IsSoundPlayed())
				{
					as->Play(eButtonSoundType::ButtonClick, false, false);
					SoundPlay(true);
				}

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
		else
		{
			SoundPlay(false);
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