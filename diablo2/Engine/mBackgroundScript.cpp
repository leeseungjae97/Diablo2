#include "mBackgroundScript.h"

#include "mMaterial.h"

namespace m
{
	BackgroundScript::BackgroundScript()
		: mAnimator(nullptr)
		, mAnimString(L"")
	{
	}

	BackgroundScript::~BackgroundScript()
	{
	}

	void BackgroundScript::Initialize()
	{
		Script::Initialize();
		mAnimator = GET_COMP(GetOwner(), Animator);

		SHARED_MAT noneMat = RESOURCE_FIND(Material, L"noneRect");
		mAnimator->Create(
			L"noneRectAnim"
			, noneMat->GetTexture()
			, Vector2::Zero
			, Vector2(20.f, 20.f)
			, 1
			, Vector2::Zero
			, 0.03f
			, 0.3f
		);

		mAnimator->PlayAnimation(L"noneRectAnim", false);
	}

	void BackgroundScript::Update()
	{
		Script::Update();
		if(mAnimString != L"")
		{
			if(mAnimator->GetActiveAnimation()->GetKey() != mAnimString + +L"anim")
			{
				SHARED_MAT mat = RESOURCE_FIND(Material, mAnimString);
				mAnimator->Create(
					mAnimString + L"anim"
					, mat->GetTexture()
					, Vector2::Zero
					, Vector2(362.f, 183.f)
					, 30
					, Vector2::Zero
					, 0.03f
				);

				mAnimator->PlayAnimation(mAnimString + L"anim", true);
			}
		}
	}

	void BackgroundScript::LateUpdate()
	{
		Script::LateUpdate();
	}

	void BackgroundScript::Render()
	{
		Script::Render();
	}

	void BackgroundScript::SetAnimString(const std::wstring& str)
	{
		mAnimString = str;
	}
}
