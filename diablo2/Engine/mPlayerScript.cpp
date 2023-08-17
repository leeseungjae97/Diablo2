#include "mPlayerScript.h"

#include "../engine_source/mConstantBuffer.h"
#include "../engine_source/mRenderer.h"
#include "../engine_source/mAnimator.h"
#include "../engine_source/mResources.h"
#include "../engine_source/mMaterial.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/MoveAbleObjectAnimLookUpTables.h"
#include "../engine_source/mAnimation.h"
#include "../engine_source/mApplication.h"
#include "../engine_source/mSkillManager.h"
#include "../engine_source/mInput.h"

#include "mPlayer.h"
#include "mMonster.h"
#include "mPlayerInfo.h"

#include "mSkillStraight.h"
#include "mSkillFall.h"
#include "mSkillMultiFire.h"
#include "mSkill.h"

extern m::Application application;
namespace m
{
	PlayerScript::PlayerScript()
		: mAnimator(nullptr)
		, mDirection()
		, mAnimationType()
		, mRSO(nullptr)
		, mLSO(nullptr)
		, mHSO(nullptr)
		, activeSkillIndex(0)
		, bFire(false)
		, bDamage(false)
	{
	}

	PlayerScript::~PlayerScript(){}

	void PlayerScript::Initialize()
	{
		mAnimator = GET_COMP(GetOwner(), Animator);
		Scene* curScene = SceneManager::GetActiveScene();
		mRSO = new SkillOverlay(1);
		mLSO = new SkillOverlay(0);
		mHSO = new SkillOverlay();

		mRSO->SetActiveOwner(GetOwner());
		mLSO->SetActiveOwner(GetOwner());
		mHSO->SetActiveOwner(GetOwner());
		//SET_POS_VEC(mRSO, GET_POS(GetOwner()));
		//SET_POS_VEC(mLSO, GET_POS(GetOwner()));

		//SET_SCALE_XYZ(mRSO, 100.f, 50.f, 1.f);
		//SET_SCALE_XYZ(mLSO, 100.f, 50.f, 1.f);

		curScene->AddGameObject(eLayerType::Skill, mRSO);
		curScene->AddGameObject(eLayerType::Skill, mLSO);
		curScene->AddGameObject(eLayerType::Skill, mHSO);

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
				, 0.1f
			);
			mAnimator->Create(
				sorceressAnimationString[(UINT)eSorceressAnimationType::SpecialCast] + characterDirectionString[i]
				, tex6->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)eSorceressAnimationType::SpecialCast].y * i)
				, sorceressAnimationSizes[(UINT)eSorceressAnimationType::SpecialCast]
				, sorceressAnimationLength[(UINT)eSorceressAnimationType::SpecialCast]
				, Vector2(0.f, -10.f)
				, 0.03f
			);
			mAnimator->Create(
				sorceressAnimationString[(UINT)eSorceressAnimationType::Natural] + characterDirectionString[i]
				, tex3->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)eSorceressAnimationType::Natural].y * i)
				, sorceressAnimationSizes[(UINT)eSorceressAnimationType::Natural]
				, sorceressAnimationLength[(UINT)eSorceressAnimationType::Natural]
				, Vector2::Zero
				, 0.1f
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
				sorceressAnimationString[(UINT)eSorceressAnimationType::GetHit] + characterDirectionString[i]
				, tex7->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)eSorceressAnimationType::GetHit].y * i)
				, sorceressAnimationSizes[(UINT)eSorceressAnimationType::GetHit]
				, sorceressAnimationLength[(UINT)eSorceressAnimationType::GetHit]
				, Vector2::Zero
				, 0.05f
			);
			mAnimator->Create(
				sorceressAnimationString[(UINT)eSorceressAnimationType::Attack1] + characterDirectionString[i]
				, tex1->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)eSorceressAnimationType::Attack1].y * i)
				, sorceressAnimationSizes[(UINT)eSorceressAnimationType::Attack1]
				, sorceressAnimationLength[(UINT)eSorceressAnimationType::Attack1]
				, Vector2::Zero
				, 0.05f
			);
			mAnimator->StartEvent(sorceressAnimationString[(UINT)eSorceressAnimationType::SpecialCast] + characterDirectionString[i])
				= [this]()
			{
				mAnimator->SetAnimationStartIndex(0);
				mAnimator->SetAnimationProgressIndex(10);
				GetOwner()->SetBattleState(GameObject::eBattleState::Cast);
				bFire = true;
			};
			mAnimator->ProgressEvent(sorceressAnimationString[(UINT)eSorceressAnimationType::SpecialCast] + characterDirectionString[i])
				= [this]()
			{
				if (bFire)
				{
					Skill* skill = nullptr;
					MAKE_SKILL(activeSkillIndex, skill, GET_POS(PlayerInfo::player), eLayerType::PlayerSkill);
					bFire = false;
				}
			};
			mAnimator->EndEvent(sorceressAnimationString[(UINT)eSorceressAnimationType::SpecialCast] + characterDirectionString[i])
				= [this]() { GetOwner()->SetBattleState(GameObject::eBattleState::Idle); };

			mAnimator->StartEvent(sorceressAnimationString[(UINT)eSorceressAnimationType::Attack1] + characterDirectionString[i])
				= [this]()
			{
				//mAnimator->SetAnimationProgressIndex(0);
				mAnimator->SetAnimationProgressIndex(14);
				mAnimator->SetAnimationStartIndex(0);
				AnimationStart(GameObject::eBattleState::Attack);
			};
			mAnimator->EndEvent(sorceressAnimationString[(UINT)eSorceressAnimationType::Attack1] + characterDirectionString[i])
				= [this]() { AnimationComplete(GameObject::eBattleState::Idle); };
			mAnimator->ProgressEvent(sorceressAnimationString[(UINT)eSorceressAnimationType::Attack1] + characterDirectionString[i])
				= [this]()
			{
				AttackProgress();
			};

			mAnimator->StartEvent(sorceressAnimationString[(UINT)eSorceressAnimationType::GetHit] + characterDirectionString[i])
				= [this]() { Hit(true, GameObject::eBattleState::Hit); };
			mAnimator->EndEvent(sorceressAnimationString[(UINT)eSorceressAnimationType::GetHit] + characterDirectionString[i])
				= [this]() { Hit(false, GameObject::eBattleState::Idle); };
		}

		mDirection = eCharacterDirection::Down;
		mAnimationType = eSorceressAnimationType::Natural;
		mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + characterDirectionString[(UINT)mDirection], true);
	}
	void PlayerScript::Update()
	{
		if (nullptr == PlayerInfo::player)
			return;

		Vector3 direction = PlayerInfo::player->GetDirection();

		float degree = RadianToDegree(atan2(direction.x, direction.y));
		int n = degree / (180.f / 9.f);

		if (n > 0)
			mDirection = plusCharacterDirections[n];
		else
			mDirection = minusCharacterDirections[abs(n)];
		//if (degree > -fDivideDegree && degree < fDivideDegree) mDirection = eCharacterDirection::Up;
		//else if (degree < -fDivideDegree && degree > -fDivideDegree * 2) mDirection = eCharacterDirection::LeftUp3;
		//else if (degree < -fDivideDegree * 2 && degree > -fDivideDegree * 3) mDirection = eCharacterDirection::LeftUp2;
		//else if (degree < -fDivideDegree * 3 && degree > -fDivideDegree * 4) mDirection = eCharacterDirection::LeftUp1;
		//else if (degree < -fDivideDegree * 4 && degree > -fDivideDegree * 5) mDirection = eCharacterDirection::Left;
		//else if (degree < -fDivideDegree * 5 && degree > -fDivideDegree * 6) mDirection = eCharacterDirection::LeftDown3;
		//else if (degree < -fDivideDegree * 6 && degree > -fDivideDegree * 7) mDirection = eCharacterDirection::LeftDown2;
		//else if (degree < -fDivideDegree * 7 && degree > -fDivideDegree * 8) mDirection = eCharacterDirection::LeftDown1;
		//else if (degree < -fDivideDegree * 8 && degree > -fDivideDegree * 9) mDirection = eCharacterDirection::Down;
		//else if (degree <  fDivideDegree * 9 && degree >  fDivideDegree * 8) mDirection = eCharacterDirection::Down;
		//else if (degree <  fDivideDegree * 8 && degree >  fDivideDegree * 7) mDirection = eCharacterDirection::RightDown3;
		//else if (degree <  fDivideDegree * 7 && degree >  fDivideDegree * 6) mDirection = eCharacterDirection::RightDown2;
		//else if (degree <  fDivideDegree * 6 && degree >  fDivideDegree * 5) mDirection = eCharacterDirection::RightDown1;
		//else if (degree <  fDivideDegree * 5 && degree >  fDivideDegree * 4) mDirection = eCharacterDirection::Right;
		//else if (degree <  fDivideDegree * 4 && degree >  fDivideDegree * 3) mDirection = eCharacterDirection::RightUp3;
		//else if (degree <  fDivideDegree * 3 && degree >  fDivideDegree * 2) mDirection = eCharacterDirection::RightUp2;
		//else if (degree <  fDivideDegree * 2 && degree >  fDivideDegree) mDirection = eCharacterDirection::RightUp1;

		if (Input::GetKeyUp(eKeyCode::C))
		{
			mAnimationType = eSorceressAnimationType::Attack1;
			SET_SCALE_XYZ(GetOwner(), sorceressAnimationSizes[(UINT)mAnimationType].x, sorceressAnimationSizes[(UINT)mAnimationType].y, 0.f);
			if (mAnimator->GetActiveAnimation()->GetKey() != sorceressAnimationString[(UINT)mAnimationType] + characterDirectionString[(UINT)mDirection])
			{
				mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + characterDirectionString[(UINT)mDirection], false);
			}
		}
		if (Input::GetKeyDown(eKeyCode::RBUTTON))
		{
			mAnimationType = eSorceressAnimationType::SpecialCast;
			SET_SCALE_XYZ(GetOwner(), sorceressAnimationSizes[(UINT)mAnimationType].x, sorceressAnimationSizes[(UINT)mAnimationType].y, 0.f);
			mRSO->ActiveOverlay();
			activeSkillIndex = 1;
			if (mAnimator->GetActiveAnimation()->GetKey() != sorceressAnimationString[(UINT)mAnimationType] + characterDirectionString[(UINT)mDirection])
				mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + characterDirectionString[(UINT)mDirection], false);
		}
		if (PlayerInfo::player->GetHit())
		{
			mAnimationType = eSorceressAnimationType::GetHit;
			SET_SCALE_XYZ(GetOwner(), sorceressAnimationSizes[(UINT)mAnimationType].x, sorceressAnimationSizes[(UINT)mAnimationType].y, 0.f);
			if (mAnimator->GetActiveAnimation()->GetKey() != sorceressAnimationString[(UINT)mAnimationType] + characterDirectionString[(UINT)mDirection])
				mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + characterDirectionString[(UINT)mDirection], false);
		}

		if (
			GetOwner()->GetBattleState() != GameObject::Idle
			&&
			GetOwner()->GetBattleState() != GameObject::Run
			)
			return;

		if (PlayerInfo::player->StopF())
		{
			GetOwner()->SetBattleState(GameObject::Idle);
			mAnimationType = eSorceressAnimationType::Natural;
		}
		else
		{
			GetOwner()->SetBattleState(GameObject::Run);
			mAnimationType = eSorceressAnimationType::Run;
		}

		if (mAnimator->GetActiveAnimation()->GetKey() != sorceressAnimationString[(UINT)mAnimationType] + characterDirectionString[(UINT)mDirection])
		{
			SET_SCALE_XYZ(GetOwner(), sorceressAnimationSizes[(UINT)mAnimationType].x, sorceressAnimationSizes[(UINT)mAnimationType].y, 0.f);
			WSTRING_SUBSTR(mAnimator->GetActiveAnimation()->GetKey(), L'@', subStr1);

			int prevIndex = 0;
			if (subStr1 == sorceressAnimationString[(UINT)eSorceressAnimationType::Run])
				prevIndex = mAnimator->GetAnimationIndex();
			mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + characterDirectionString[(UINT)mDirection], true);
			if (mAnimationType == eSorceressAnimationType::Run)
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
	void PlayerScript::AnimationStart(GameObject::eBattleState state)
	{
		bDamage = false;
		GetOwner()->SetBattleState(state);
	}
	void PlayerScript::AnimationComplete(GameObject::eBattleState state)
	{
		bDamage = false;
		GetOwner()->SetBattleState(state);
	}
	void PlayerScript::Hit(bool hit, GameObject::eBattleState state)
	{
		PlayerInfo::player->SetHit(hit);
		GetOwner()->SetBattleState(state);
		//mRSO->ActiveOverlay();
	}
	void PlayerScript::AttackProgress()
	{

		if (PlayerInfo::player->GetRangeCollider()->GetOnEnter()
			|| PlayerInfo::player->GetRangeCollider()->GetOnStay())
		{
			if (!bDamage)
			{
				for (Collider2D* col : PlayerInfo::player->GetRangeCollider()->GetCollidereds())
				{
					Monster* mon = dynamic_cast<Monster*>(col->GetOwner());
					mon->Hit(10);
				}
				//GetMonster()->Hit(10);
				bDamage = true;
			}
		}
	}
};