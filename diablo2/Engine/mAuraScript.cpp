#include "mAuraScript.h"

#include "mMaterial.h"
#include "mMonster.h"
#include "mMoveAbleObject.h"
#include "mPlayer.h"
#include "mTime.h"

namespace m
{
	AuraScript::AuraScript(eAuraType type, float auraDuration)
		: mAuraType(type)
		, mDuration(auraDuration)
		, fAcc(0.f)
		, fCollideAcc(0.f)
	{
	}

	AuraScript::~AuraScript()
	{
	}

	void AuraScript::Initialize()
	{
		Script::Initialize();
		mAnimator = GET_COMP(GetOwner(), Animator);
		SHARED_MAT mat = RESOURCE_FIND(Material, auraNames[(int)mAuraType]);

		if (nullptr == mat) return;

		mAnimator->Create(
			auraNames[(int)mAuraType] + L"anim"
			, mat->GetTexture()
			, Vector2::Zero
			, auraSizes[(int)mAuraType]
			, auraLength[(int)mAuraType]
			, Vector2::Zero
			, auraCenterPos[(int)mAuraType]
			, 0.03f
		);
		mAnimator->PlayAnimation(auraNames[(int)mAuraType] + L"anim", true);

		SHARED_MAT noneMat = RESOURCE_FIND(Material, L"noneRect");
		mAnimator->Create(
			L"noneRectAnim"
			, noneMat->GetTexture()
			, Vector2::Zero
			, Vector2(20.f, 20.f)
			, 1
			, Vector2::Zero
			, 0.03f
		);
	}

	void AuraScript::Update()
	{
		Script::Update();
		fAcc += Time::fDeltaTime();
		if(mDuration >= 0)
		{
			if (mDuration <= fAcc)
			{
				mAnimator->PlayAnimation(L"noneRectAnim", false);
			}
		}
		colliderCollided();
	}

	void AuraScript::LateUpdate()
	{
		Script::LateUpdate();
	}


	void AuraScript::Render()
	{
		Script::Render();
	}

    void AuraScript::colliderCollided()
    {
		eAuraFunctionType fType = auraFunction[(int)mAuraType];
		float fAuraFunctionValue1 = auraFunctionValue[(int)fType][0];
		float fAuraFunctionValue2 = auraFunctionValue[(int)fType][1];

		bool coliidePlayer = false;
		if (mCol->GetOnEnter()
			|| mCol->GetOnStay())
		{
			Monster* m = dynamic_cast<Monster*>(mAuraOwner);
			if (m)
			{
				if(mCol->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
				{
					coliidePlayer = true;
				}
			}
			else coliidePlayer = false;
			
			switch (fType)
			{
			case eAuraFunctionType::Slow:
			{
				if (coliidePlayer)
					PlayerManager::player->SetNumericalAdjustmentSpeed(fAuraFunctionValue1
						, fAuraFunctionValue2);
			}
			break;
			default:
			{

			}
			break;
			}
		}
    }
}
