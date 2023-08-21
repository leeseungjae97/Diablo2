#include "mHandScript.h"

#include "MonsterHandLookUpTables.h"

namespace m
{
	HandScript::HandScript(Vector2* sizes, int* lens, int maxLen, std::wstring* names)
		: mHandDirection(0)
		, mAnimationSize(sizes)
		, mAnimationLength(lens)
		, mAnimationMaxLength(maxLen)
		, mHandnames(names)
	{
		mMats.resize(maxLen);
		mAnimator = GET_COMP(GetOwner(), Animator);
		for(int i = 0; i < maxLen; ++i)
		{
			if (mHandnames[i] == L"") continue;
			mMats[i] = RESOURCE_FIND(Material, mHandnames[i]);
		}
		for(int i = 0 ; i < mAnimationMaxLength; ++i)
		{
			if (mHandnames[i] == L"") continue;
			mAnimator->Create(
				mHandnames[i] + L"anim"
				, mMats[i]->GetTexture()
				, Vector2::Zero
				, mAnimationSize[i]
				, mAnimationLength[i]
				, Vector2::Zero
				, 0.03f
			);
		}
	}

	HandScript::~HandScript()
	{
	}

	void HandScript::Update()
	{
		Script::Update();
	/*	if (mAnimator->GetActiveAnimation()->GetKey() != mHandnames[(UINT)mAnimationType] + sixteenDirectionString[mHandDirection]
			&& curMonsterData.textureString[(UINT)mAnimationType] != L"")
		{

			SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);

			WSTRING_SUBSTR(mAnimator->GetActiveAnimation()->GetKey(), L'@', subStr1);

			int prevIndex = 0;
			if (subStr1 == curMonsterData.animationString[(UINT)T::eAnimationType::Run])
			{
				prevIndex = mAnimator->GetAnimationIndex();
			}

			mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + sixteenDirectionString[mDirection], true);
			if (mAnimationType == T::eAnimationType::Run)
			{
				mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)mAnimationType]);
				mAnimator->SetAnimationIndex(prevIndex);
			}
		}*/
	}

	void HandScript::LateUpdate()
	{
		Script::LateUpdate();
	}

	void HandScript::Render()
	{
		Script::Render();
	}

	void HandScript::Initialize()
	{
		Script::Initialize();
	}
}
