#include "mPlayerScript.h"

#include "../engine_source/mGameObject.h"
#include "../engine_source/mConstantBuffer.h"
#include "../engine_source/mRenderer.h"
#include "../engine_source/mAnimator.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mResources.h"
#include "../engine_source/mMaterial.h"
#include "../engine_source/AnimLookUpTables.h"
#include "../engine_source/mAnimation.h"
#include "../engine_source/mApplication.h"
#include "../engine_source/mInput.h"

#include "mPlayer.h"

extern m::Application application;
namespace m
{
	PlayerScript::PlayerScript()
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
		//Animator* at = GetOwner()->GetComponent<Animator>();
		//at->CompleteEvent(L"sorceressTownWalk_anim") = std::bind(&PlayerScript::Complete, this);

		GET_COMP(GetOwner(), mAnimator, Animator);

		SHARED_MAT tex1 = RESOURCE_FIND(Material, L"sorceressAttack1");
		SHARED_MAT tex2 = RESOURCE_FIND(Material, L"sorceressAttack2");
		SHARED_MAT tex3 = RESOURCE_FIND(Material, L"sorceressNatural");

		SHARED_MAT tex4 = RESOURCE_FIND(Material, L"sorceressRun");
		SHARED_MAT tex5 = RESOURCE_FIND(Material, L"sorceressWalk");
		SHARED_MAT tex6 = RESOURCE_FIND(Material, L"sorceressSpecialCast");
		SHARED_MAT tex7 = RESOURCE_FIND(Material, L"sorceressGetHit");
		SHARED_MAT tex8 = RESOURCE_FIND(Material, L"sorceressTownWalk");

		SHARED_MAT tex9 = RESOURCE_FIND(Material, L"sorceressDead");

		for (int i = 0; i < (UINT)eCharacterDirection::End; ++i)
		{
			mAnimator->Create(
				sorceressAnimationString[(UINT)eSorceressAnimationType::Run] + characterDirectionString[i]
				, tex4->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)eSorceressAnimationType::Run].y * i)
				, sorceressAnimationSizes[(UINT)eSorceressAnimationType::Run]
				, sorceressAnimationLength[(UINT)eSorceressAnimationType::Run]
				, Vector2::Zero
				, 0.1
			);
			mAnimator->Create(
				sorceressAnimationString[(UINT)eSorceressAnimationType::Natural] + characterDirectionString[i]
				, tex3->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)eSorceressAnimationType::Natural].y * i)
				, sorceressAnimationSizes[(UINT)eSorceressAnimationType::Natural]
				, sorceressAnimationLength[(UINT)eSorceressAnimationType::Natural]
				, Vector2::Zero
				, 0.1
			);
			//mAnimator->Create(
			//	sorceressAnimationString[(UINT)eSorceressAnimationType::Dead] + characterDirectionString[i]
			//	, tex9->GetTexture()
			//	, Vector2(0.0f, sorceressAnimationSizes[(UINT)eSorceressAnimationType::Dead].y * i)
			//	, sorceressAnimationSizes[(UINT)eSorceressAnimationType::Dead]
			//	, sorceressAnimationLength[(UINT)eSorceressAnimationType::Dead]
			//	, Vector2::Zero
			//	, 0.1
			//);
			mAnimator->Create(
				sorceressAnimationString[(UINT)eSorceressAnimationType::Attack1] + characterDirectionString[i]
				, tex1->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)eSorceressAnimationType::Attack1].y * i)
				, sorceressAnimationSizes[(UINT)eSorceressAnimationType::Attack1]
				, sorceressAnimationLength[(UINT)eSorceressAnimationType::Attack1]
				, Vector2::Zero
				, 0.07
			);
			mAnimator->StartEvent(sorceressAnimationString[(UINT)eSorceressAnimationType::Attack1] + characterDirectionString[i]) = std::bind(&PlayerScript::AttackStart, this);
			mAnimator->CompleteEvent(sorceressAnimationString[(UINT)eSorceressAnimationType::Attack1] + characterDirectionString[i]) = std::bind(&PlayerScript::AttackComplete, this);
		}
		
		mDirection = eCharacterDirection::Down;
		mAnimationType = eSorceressAnimationType::Natural;
		mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + characterDirectionString[(UINT)mDirection], true);
	}
	void PlayerScript::Update()
	{
		if (nullptr == GetPlayer())
			return;

		SET_SCALE_XYZ(GetOwner(), sorceressAnimationSizes[(UINT)mAnimationType].x, sorceressAnimationSizes[(UINT)mAnimationType].y, 0.f);

		if (Input::GetKeyUpOne(eKeyCode::C))
		{
			mAnimationType = eSorceressAnimationType::Attack1;
			//GetOwner()->SetBattleState(GameObject::Attack);
			if (mAnimator->GetActiveAnimation()->GetKey() != sorceressAnimationString[(UINT)mAnimationType] + characterDirectionString[(UINT)mDirection])
				mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + characterDirectionString[(UINT)mDirection], true);
		}
		if (GetOwner()->GetBattleState() == GameObject::Attack)
			return;

		if (GetPlayer()->Stop())
		{
			GetOwner()->SetBattleState(GameObject::Idle);
			mAnimationType = eSorceressAnimationType::Natural;
		}
		else
		{
			GetOwner()->SetBattleState(GameObject::Run);
			Vector3 initPos = GetPlayer()->GetPrevPosition();
			Vector3 destPos = GetPlayer()->GetDestPosition();

			Vector3 moveVector = destPos - initPos;

			moveVector.Normalize();

			float degree = RadianToDegree(atan2(moveVector.x, moveVector.y));
			float fDivideDegree = 180.f / 9.f;
			mDirection = eCharacterDirection::Down;
			if (	 degree > -fDivideDegree     && degree <  fDivideDegree    ) mDirection = eCharacterDirection::Up;
			else if (degree < -fDivideDegree	 && degree > -fDivideDegree * 2) mDirection = eCharacterDirection::LeftUp3;
			else if (degree < -fDivideDegree * 2 && degree > -fDivideDegree * 3) mDirection = eCharacterDirection::LeftUp2;
			else if (degree < -fDivideDegree * 3 && degree > -fDivideDegree * 4) mDirection = eCharacterDirection::LeftUp1;
			else if (degree < -fDivideDegree * 4 && degree > -fDivideDegree * 5) mDirection = eCharacterDirection::Left;
			else if (degree < -fDivideDegree * 5 && degree > -fDivideDegree * 6) mDirection = eCharacterDirection::LeftDown3;
			else if (degree < -fDivideDegree * 6 && degree > -fDivideDegree * 7) mDirection = eCharacterDirection::LeftDown2;
			else if (degree < -fDivideDegree * 7 && degree > -fDivideDegree * 8) mDirection = eCharacterDirection::LeftDown1;
			else if (degree < -fDivideDegree * 8 && degree > -fDivideDegree * 9) mDirection = eCharacterDirection::Down;
			else if (degree <  fDivideDegree * 9 && degree >  fDivideDegree * 8) mDirection = eCharacterDirection::Down;
			else if (degree <  fDivideDegree * 8 && degree >  fDivideDegree * 7) mDirection = eCharacterDirection::RightDown3;
			else if (degree <  fDivideDegree * 7 && degree >  fDivideDegree * 6) mDirection = eCharacterDirection::RightDown2;
			else if (degree <  fDivideDegree * 6 && degree >  fDivideDegree * 5) mDirection = eCharacterDirection::RightDown1;
			else if (degree <  fDivideDegree * 5 && degree >  fDivideDegree * 4) mDirection = eCharacterDirection::Right;
			else if (degree <  fDivideDegree * 4 && degree >  fDivideDegree * 3) mDirection = eCharacterDirection::RightUp3;
			else if (degree <  fDivideDegree * 3 && degree >  fDivideDegree * 2) mDirection = eCharacterDirection::RightUp2;
			else if (degree <  fDivideDegree * 2 && degree >  fDivideDegree	   ) mDirection = eCharacterDirection::RightUp1;
			//else if( degree >-)	
			mAnimationType = eSorceressAnimationType::Run;
		}
		if (mAnimator->GetActiveAnimation()->GetKey() != sorceressAnimationString[(UINT)mAnimationType] + characterDirectionString[(UINT)mDirection])
		{
			int prevIndex = mAnimator->GetAnimationIndex();
			mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + characterDirectionString[(UINT)mDirection], true);
			if(mAnimationType == eSorceressAnimationType::Run)
				mAnimator->SetAnimationIndex(prevIndex);
		}

	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}
	void PlayerScript::Complete()
	{
	}
	void PlayerScript::AttackStart()
	{
		GetOwner()->SetBattleState(GameObject::Attack);
	}
	void PlayerScript::AttackComplete()
	{
		GetOwner()->SetBattleState(GameObject::Idle);
	}
};