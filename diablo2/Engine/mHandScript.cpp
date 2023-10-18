#include "mHandScript.h"

#include "MonsterHandLookUpTables.h"
#include "MoveAbleObjectAnimLookUpTables.h"
#include "SkillAnimLookUpTables.h"

namespace m
{
	HandScript::HandScript(Vector2* sizes, Vector2* offset, int* lens, int maxLen, std::wstring* names)
		: mHandDirection(0)
		, mHandnames(names)
		, mAnimationSize(sizes)
		, mAnimationOffset(offset)
		, mAnimationLength(lens)
		, mAnimationMaxLength(maxLen)
	{
		mMats.resize(maxLen);
	}

	HandScript::~HandScript()
	{
	}
	void HandScript::Initialize()
	{
		Script::Initialize();
		mAnimator = GET_COMP(GetOwner(), Animator);
		for (int i = 0; i < mAnimationMaxLength; ++i)
		{
			if (mHandnames[i] == L"") continue;
			mMats[i] = RESOURCE_FIND(Material, mHandnames[i]);
		}
		int m = 0;
		for (int i = 0; i < mAnimationMaxLength; ++i)
		{
			if (mHandnames[i] == L"") continue;

			for (int j = 0; j < 8; ++j)
			{
				m = pathEightDirections[j];
				mAnimator->Create(
					mHandnames[i] + L"@" + sixteenDirectionString[m]
					, mMats[i]->GetTexture()
					, Vector2(0.0f, mAnimationSize[i].y * j)
					, mAnimationSize[i]
					, mAnimationLength[i]
					, mAnimationOffset[i]
					, 0.05f
				);
			}
		}
	}

    void HandScript::SetHandDirection(int direction)
    {
		if(mAnimator->GetActiveAnimation())
		{
			if(mAnimator->GetActiveAnimation()->GetAltasLength() - 1 < direction)
			{
				direction = mAnimator->GetActiveAnimation()->GetAltasLength() - 1;
			}
		}

		mHandDirection = direction;
    }

    void HandScript::Update()
	{
		Script::Update();

		std::wstring curAnimationName = mHandnames[mHandAnimationType] + L"@" + sixteenDirectionString[mHandDirection];
		if (nullptr == mAnimator->GetActiveAnimation())
		{
			if(mHandnames[mHandAnimationType] != L"")
			{
				SET_SCALE_XYZ(GetOwner(), mAnimationSize[mHandAnimationType].x, mAnimationSize[mHandAnimationType].y, 0.f);
				mAnimator->PlayAnimation(curAnimationName, true);
			}

		}else
		{
			if (mAnimator->GetActiveAnimation()->GetKey() != curAnimationName
				&& mHandnames[mHandAnimationType] != L"")
			{
				SET_SCALE_XYZ(GetOwner(), mAnimationSize[mHandAnimationType].x, mAnimationSize[mHandAnimationType].y, 0.f);

				WSTRING_SUBSTR(mAnimator->GetActiveAnimation()->GetKey(), L'@', subStr1);

				int prevIndex = 0;
				if (subStr1 == mHandnames[3])
				{
					prevIndex = mAnimator->GetAnimationIndex();
				}
				mAnimator->PlayAnimation(curAnimationName, true);
				if (mHandAnimationType == 3)
				{
					//mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)mAnimationType]);
					mAnimator->SetAnimationIndex(prevIndex);
				}
			}
		}
	}

	void HandScript::LateUpdate()
	{
		Script::LateUpdate();
	}

	void HandScript::Render()
	{
		Script::Render();
	}
}
