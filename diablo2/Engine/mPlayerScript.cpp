#include "mPlayerScript.h"

#include "../engine_source/mConstantBuffer.h"
#include "../engine_source/mRenderer.h"
#include "../engine_source/mAnimator.h"
#include "../engine_source/mResources.h"
#include "../engine_source/mMaterial.h"
#include "../engine_source/mMouseManager.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/MoveAbleObjectAnimLookUpTables.h"
#include "../engine_source/mAnimation.h"
#include "../engine_source/mApplication.h"
#include "../engine_source/mSkillManager.h"
#include "../engine_source/mInput.h"

#include "mPlayer.h"
#include "mMonster.h"
#include "mPlayerManager.h"
#include "mPlayerStatus.h"

#include "mSkillStraight.h"
#include "mSkillFall.h"
#include "mSkillMultiFire.h"
#include "mSkillOrb.h"
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

		curScene->AddGameObject(eLayerType::PlayerSkill, mRSO);
		curScene->AddGameObject(eLayerType::PlayerSkill, mLSO);
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

		for (int i = 0; i < (UINT)eSixteenDirection::End; ++i)
		{
			mAnimator->Create(
				sorceressAnimationString[(UINT)ePlayerAnimationType::Run] + sixteenDirectionString[i]
				, tex4->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Run].y * i)
				, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Run]
				, sorceressAnimationLength[(UINT)ePlayerAnimationType::Run]
				, Vector2::Zero
				, 0.1f
			);
			mAnimator->Create(
				sorceressAnimationString[(UINT)ePlayerAnimationType::SpecialCast] + sixteenDirectionString[i]
				, tex6->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)ePlayerAnimationType::SpecialCast].y * i)
				, sorceressAnimationSizes[(UINT)ePlayerAnimationType::SpecialCast]
				, sorceressAnimationLength[(UINT)ePlayerAnimationType::SpecialCast]
				, Vector2(0.f, -10.f)
				, 0.03f
			);
			mAnimator->Create(
				sorceressAnimationString[(UINT)ePlayerAnimationType::Natural] + sixteenDirectionString[i]
				, tex3->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Natural].y * i)
				, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Natural]
				, sorceressAnimationLength[(UINT)ePlayerAnimationType::Natural]
				, Vector2::Zero
				, 0.1f
			);
			//mAnimator->Create(
			//	sorceressAnimationString[(UINT)ePlayerAnimationType::Dead] + sixteenDirectionString[i]
			//	, tex9->GetTexture()
			//	, Vector2(0.0f, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Dead].y * i)
			//	, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Dead]
			//	, sorceressAnimationLength[(UINT)ePlayerAnimationType::Dead]
			//	, Vector2::Zero
			//	, 0.1
			//);
			mAnimator->Create(
				sorceressAnimationString[(UINT)ePlayerAnimationType::GetHit] + sixteenDirectionString[i]
				, tex7->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)ePlayerAnimationType::GetHit].y * i)
				, sorceressAnimationSizes[(UINT)ePlayerAnimationType::GetHit]
				, sorceressAnimationLength[(UINT)ePlayerAnimationType::GetHit]
				, Vector2::Zero
				, 0.05f
			);
			mAnimator->Create(
				sorceressAnimationString[(UINT)ePlayerAnimationType::Attack1] + sixteenDirectionString[i]
				, tex1->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Attack1].y * i)
				, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Attack1]
				, sorceressAnimationLength[(UINT)ePlayerAnimationType::Attack1]
				, Vector2::Zero
				, 0.05f
			);
			mAnimator->StartEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::SpecialCast] + sixteenDirectionString[i])
				= [this]()
			{
				mAnimator->SetAnimationStartIndex(0);
				mAnimator->SetAnimationProgressIndex(10);
				GetOwner()->SetBattleState(GameObject::eBattleState::Cast);
				bFire = true;
			};
			mAnimator->ProgressEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::SpecialCast] + sixteenDirectionString[i])
				= [this]()
			{
				if (bFire)
				{
					Skill* skill = nullptr;
					PlayerManager::player->UseMana(10);
					MAKE_SKILL(PlayerManager::GetSkill(activeSkillIndex), skill, GET_POS(PlayerManager::player), eLayerType::PlayerSkill);
					bFire = false;
				}
			};
			mAnimator->EndEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::SpecialCast] + sixteenDirectionString[i])
				= [this]() { GetOwner()->SetBattleState(GameObject::eBattleState::Idle); };

			mAnimator->StartEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::Attack1] + sixteenDirectionString[i])
				= [this]()
			{
				//mAnimator->SetAnimationProgressIndex(0);
				mAnimator->SetAnimationProgressIndex(14);
				mAnimator->SetAnimationStartIndex(0);
				AnimationStart(GameObject::eBattleState::Attack);
			};
			mAnimator->EndEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::Attack1] + sixteenDirectionString[i])
				= [this]() { AnimationComplete(GameObject::eBattleState::Idle); };
			mAnimator->ProgressEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::Attack1] + sixteenDirectionString[i])
				= [this]()
			{
				AttackProgress();
			};

			mAnimator->StartEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::GetHit] + sixteenDirectionString[i])
				= [this]() { Hit(true, GameObject::eBattleState::Hit); };
			mAnimator->EndEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::GetHit] + sixteenDirectionString[i])
				= [this]() { Hit(false, GameObject::eBattleState::Idle); };
		}

		mDirection = eSixteenDirection::Down;
		mAnimationType = ePlayerAnimationType::Natural;
		mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection], true);
	}
	void PlayerScript::Update()
	{
		if (nullptr == PlayerManager::player)
			return;

		Vector3 direction = PlayerManager::player->GetDirection();

		float degree = RadianToDegree(atan2(direction.x, direction.y));
		int n = degree / (180.f / 9.f);

		if (n > 0)
			mDirection = plusSixteenDirections[n];
		else
			mDirection = minusSixteenDirections[abs(n)];
		//if (degree > -fDivideDegree && degree < fDivideDegree) mDirection = eSixteenDirection::Up;
		//else if (degree < -fDivideDegree && degree > -fDivideDegree * 2) mDirection = eSixteenDirection::LeftUp3;
		//else if (degree < -fDivideDegree * 2 && degree > -fDivideDegree * 3) mDirection = eSixteenDirection::LeftUp2;
		//else if (degree < -fDivideDegree * 3 && degree > -fDivideDegree * 4) mDirection = eSixteenDirection::LeftUp1;
		//else if (degree < -fDivideDegree * 4 && degree > -fDivideDegree * 5) mDirection = eSixteenDirection::Left;
		//else if (degree < -fDivideDegree * 5 && degree > -fDivideDegree * 6) mDirection = eSixteenDirection::LeftDown3;
		//else if (degree < -fDivideDegree * 6 && degree > -fDivideDegree * 7) mDirection = eSixteenDirection::LeftDown2;
		//else if (degree < -fDivideDegree * 7 && degree > -fDivideDegree * 8) mDirection = eSixteenDirection::LeftDown1;
		//else if (degree < -fDivideDegree * 8 && degree > -fDivideDegree * 9) mDirection = eSixteenDirection::Down;
		//else if (degree <  fDivideDegree * 9 && degree >  fDivideDegree * 8) mDirection = eSixteenDirection::Down;
		//else if (degree <  fDivideDegree * 8 && degree >  fDivideDegree * 7) mDirection = eSixteenDirection::RightDown3;
		//else if (degree <  fDivideDegree * 7 && degree >  fDivideDegree * 6) mDirection = eSixteenDirection::RightDown2;
		//else if (degree <  fDivideDegree * 6 && degree >  fDivideDegree * 5) mDirection = eSixteenDirection::RightDown1;
		//else if (degree <  fDivideDegree * 5 && degree >  fDivideDegree * 4) mDirection = eSixteenDirection::Right;
		//else if (degree <  fDivideDegree * 4 && degree >  fDivideDegree * 3) mDirection = eSixteenDirection::RightUp3;
		//else if (degree <  fDivideDegree * 3 && degree >  fDivideDegree * 2) mDirection = eSixteenDirection::RightUp2;
		//else if (degree <  fDivideDegree * 2 && degree >  fDivideDegree) mDirection = eSixteenDirection::RightUp1;

		//if (((Player*)GetOwner())->GetFMID() != -1 && PlayerManager::player->StopF()
		//	&& ((Player*)GetOwner())->GetAttack())
		//{
		//	((Player*)GetOwner())->SetFMID(-1);
		//	((Player*)GetOwner())->SetAttack(false);
		//	mAnimationType = ePlayerAnimationType::Attack1;
		//	SET_SCALE_XYZ(GetOwner(), sorceressAnimationSizes[(UINT)mAnimationType].x, sorceressAnimationSizes[(UINT)mAnimationType].y, 0.f);
		//	if (mAnimator->GetActiveAnimation()->GetKey() != sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection])
		//	{
		//		mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection], false);
		//	}
		//}
		if (Input::GetKeyDown(eKeyCode::RBUTTON))
		{
			mAnimationType = ePlayerAnimationType::SpecialCast;
			SET_SCALE_XYZ(GetOwner(), sorceressAnimationSizes[(UINT)mAnimationType].x, sorceressAnimationSizes[(UINT)mAnimationType].y, 0.f);
			mRSO->ActiveOverlay();
			activeSkillIndex = 1;
			if (mAnimator->GetActiveAnimation()->GetKey() != sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection])
				mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection], false);
		}
		if (PlayerManager::player->GetHit())
		{
			mAnimationType = ePlayerAnimationType::GetHit;
			SET_SCALE_XYZ(GetOwner(), sorceressAnimationSizes[(UINT)mAnimationType].x, sorceressAnimationSizes[(UINT)mAnimationType].y, 0.f);
			if (mAnimator->GetActiveAnimation()->GetKey() != sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection])
				mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection], false);
		}

		if (
			GetOwner()->GetBattleState() != GameObject::Idle
			&&
			GetOwner()->GetBattleState() != GameObject::Run
			)
			return;

		if (PlayerManager::player->StopF())
		{
			GetOwner()->SetBattleState(GameObject::Idle);
			mAnimationType = ePlayerAnimationType::Natural;
		}
		else
		{
			GetOwner()->SetBattleState(GameObject::Run);
			mAnimationType = ePlayerAnimationType::Run;
		}

		if (mAnimator->GetActiveAnimation()->GetKey() != sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection])
		{
			SET_SCALE_XYZ(GetOwner(), sorceressAnimationSizes[(UINT)mAnimationType].x, sorceressAnimationSizes[(UINT)mAnimationType].y, 0.f);
			WSTRING_SUBSTR(mAnimator->GetActiveAnimation()->GetKey(), L'@', subStr1);

			int prevIndex = 0;
			if (subStr1 == sorceressAnimationString[(UINT)ePlayerAnimationType::Run])
				prevIndex = mAnimator->GetAnimationIndex();
			mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection], true);
			if (mAnimationType == ePlayerAnimationType::Run)
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
		PlayerManager::player->SetHit(hit);
		GetOwner()->SetBattleState(state);
		//mRSO->ActiveOverlay();
	}
	void PlayerScript::AttackProgress()
	{
		if (PlayerManager::player->GetRangeCollider()->GetOnEnter()
			|| PlayerManager::player->GetRangeCollider()->GetOnStay())
		{
			if (!bDamage)
			{
				for (Collider2D* col : PlayerManager::player->GetRangeCollider()->GetCollidereds())
				{
					Monster* mon = dynamic_cast<Monster*>(col->GetOwner());
					mon->Hit(10);
				}
				bDamage = true;
			}
		}
	}
};