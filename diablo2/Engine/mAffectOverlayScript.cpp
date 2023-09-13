#include "mAffectOverlayScript.h"

#include "mMonster.h"
#include "mPlayer.h"
#include "mTime.h"
#include "../engine_source/mMaterial.h"

namespace m
{
	AffectOverlayScript::AffectOverlayScript(eAffectOverlayType type)
		: iCurLoopCount(0)
		, iMaxLoopCount(0)
		, mOverlayType(type)
	    , bAtiveAffectOverlay(false)
	{

	}

	AffectOverlayScript::~AffectOverlayScript()
	{
	}

	void AffectOverlayScript::Initialize()
	{
		SkillScript::Initialize();
		mAnimator = GET_COMP(GetOwner(), Animator);

		SHARED_MAT mat = RESOURCE_FIND(Material, affectOverlayNames[(int)mOverlayType]);
		mAnimator->Create(
			affectOverlayNames[(int)mOverlayType] + L"anim"
			, mat->GetTexture()
			, Vector2::Zero
			, affectOverlaySizes[(int)mOverlayType]
			, affectOverlayLength[(int)mOverlayType]
			, Vector2::Zero
			, affectOverlayDuration[(int)mOverlayType]
		);
		mAnimator->GetActiveAnimation();
		mAnimator->StartEvent(affectOverlayNames[(int)mOverlayType] + L"anim") = [this]()
		{
			int startIdx = affectOverlayLoopAnimationIndex[(int)mOverlayType][0];
			int endIdx = affectOverlayLoopAnimationIndex[(int)mOverlayType][1];
			int progIdx = affectOverlayLoopAnimationIndex[(int)mOverlayType][2];

			mAnimator->SetAnimationStartIndex(startIdx);
			mAnimator->SetAnimationEndIndex(endIdx);
			mAnimator->SetAnimationProgressIndex(progIdx);
		};

		mAnimator->ProgressEvent(affectOverlayNames[(int)mOverlayType] + L"anim") = [this]()
		{
			iCurLoopCount = mAnimator->GetLoopCount();
		};
		
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

		mAnimator->PlayAnimation(L"noneRectAnim", false);
	}

	void AffectOverlayScript::Update()
	{
		SkillScript::Update();
		if(bAtiveAffectOverlay)
		{
			ADD_COMP(GetOwner(), Collider2D);
			bAtiveAffectOverlay = false;
			mAnimator->PlayAnimation(affectOverlayNames[(int)mOverlayType] + L"anim", true);
		}
		if (iCurLoopCount >= iMaxLoopCount)
		{
			mAnimator->SetAnimationStartIndex(0);
			mAnimator->GetActiveAnimation()->SetReverse(false);
			if(mAnimator->GetActiveAnimation()->IsStop())
			{
				GetOwner()->SetState(GameObject::Delete);
			}
		}
	}

	void AffectOverlayScript::LateUpdate()
	{
		SkillScript::LateUpdate();
	}

	void AffectOverlayScript::Render()
	{
		SkillScript::Render();
	}

	void AffectOverlayScript::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetColliderFunctionType() == eColliderFunctionType::HitArea)
		{
			if (dynamic_cast<Monster*>(other->GetOwner()))
				dynamic_cast<Monster*>(other->GetOwner())->Hit(10);

			if (dynamic_cast<Player*>(other->GetOwner()))
				dynamic_cast<Player*>(other->GetOwner())->Hit(10);
		}
	}
    //void AffectOverlayScript::OnCollisionExit(Collider2D* other)
	//{
	//	SkillScript::OnCollisionExit(other);
	//}

	//void AffectOverlayScript::OnCollisionStay(Collider2D* other)
	//{
	//	SkillScript::OnCollisionStay(other);
	//}
}
