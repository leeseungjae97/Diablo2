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
		, mCol(nullptr)
		, mOverlayType(type)
	{

	}

	AffectOverlayScript::~AffectOverlayScript()
	{
	}

	void AffectOverlayScript::Initialize()
	{
		SkillScript::Initialize();
		mCol = GET_COMP(GetOwner(), Collider2D);
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
		mAnimator->PlayAnimation(affectOverlayNames[(int)mOverlayType] + L"anim", true);
		
	}

	void AffectOverlayScript::Update()
	{
		SkillScript::Update();

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
