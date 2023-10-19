#include "mPlayerScript.h"

#include "../engine_source/mAudioSource.h"
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
#include "../engine_source/SummonsLookUpTables.h"

#include "mPlayer.h"
#include "mMonster.h"
#include "mPlayerManager.h"
#include "mPlayerStatus.h"

#include "mSkillStraight.h"
#include "mSkillFall.h"
#include "mSkillBuff.h"
#include "mSkillFallExplosion.h"
#include "mSkillMultiFire.h"
#include "mSkillOrb.h"
#include "mSkill.h"
#include "mSkillChain.h"
#include "mSkillFollower.h"
#include "mSkillFollowing.h"
#include "mSkillMultiSummons.h"
#include "mSkillPush.h"
#include "mSkillRange.h"
#include "mSkillSummons.h"
#include "mSkillWall.h"

#include "mPlayerHand.h"
#include "mAura.h"
#include "mBodyParts.h"
#include "mShadowObject.h"
#include "mStageManager.h"

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
		, mSkill(nullptr)
		, mSkillBuff(nullptr)
		, mHead(nullptr)
		, mLeftArm(nullptr)
		, mRightArm(nullptr)
		, mBody(nullptr)
		, mLeg(nullptr)
		, mRightHand(nullptr)
	{
	}

	PlayerScript::~PlayerScript()
	{
		if (mHead)
			mHead->SetState(GameObject::Delete);
		if (mLeftArm)
			mLeftArm->SetState(GameObject::Delete);
		if(mRightArm)
			mRightArm->SetState(GameObject::Delete);
		if(mBody)
			mBody->SetState(GameObject::Delete);
		if(mLeg)
			mLeg->SetState(GameObject::Delete);
		if(mRightHand)
			mRightHand->SetState(GameObject::Delete);
	}

	void PlayerScript::Initialize()
	{
		mAnimator = GET_COMP(GetOwner(), Animator);
		mAudioSource = GET_COMP(GetOwner(), AudioSource);

		Scene* curScene = SceneManager::GetActiveScene();
		mRSO = new SkillOverlay(1);
		mLSO = new SkillOverlay(0);
		mHSO = new SkillOverlay();
		mBackSO = new SkillOverlay();

		mRSO->SetActiveOwner(GetOwner());
		mLSO->SetActiveOwner(GetOwner());
		mHSO->SetActiveOwner(GetOwner());
		mBackSO->SetActiveOwner(GetOwner());
		mBackSO->Back();

		mBody = new BodyParts(eBodyPartsType::Body, GetOwner());
		mLeftArm = new BodyParts(eBodyPartsType::LeftArm, GetOwner());
		mRightArm = new BodyParts(eBodyPartsType::RightArm, GetOwner());
		mLeg = new BodyParts(eBodyPartsType::Leg, GetOwner());
		mHead = new BodyParts(eBodyPartsType::Head, GetOwner());
		mRightHand = new BodyParts(eBodyPartsType::RightHand, GetOwner());
			//mBody
			//mLeg
		
		//mRightHand = new PlayerHand(GetOwner(), true);
		
		//SET_POS_VEC(mRSO, GET_POS(GetOwner()));
		//SET_POS_VEC(mLSO, GET_POS(GetOwner()));

		//SET_SCALE_XYZ(mRSO, 100.f, 50.f, 1.f);
		//SET_SCALE_XYZ(mLSO, 100.f, 50.f, 1.f);
		mAura = new Aura(GetOwner(), eAuraType::End, Vector2::Zero);

		curScene->AddGameObject(eLayerType::PlayerSkill, mRSO);
		curScene->AddGameObject(eLayerType::PlayerSkill, mLSO);
		curScene->AddGameObject(eLayerType::Skill, mHSO);
		curScene->AddGameObject(eLayerType::Skill, mBackSO);
		curScene->AddGameObject(eLayerType::PlayerAura, mAura);

		SHARED_MAT tex1 = RESOURCE_FIND(Material, L"sorceressAttack1");
		SHARED_MAT tex2 = RESOURCE_FIND(Material, L"sorceressAttack2");
		SHARED_MAT tex3 = RESOURCE_FIND(Material, L"sorceressNatural");

		SHARED_MAT tex4 = RESOURCE_FIND(Material, L"sorceressRun");
		SHARED_MAT tex5 = RESOURCE_FIND(Material, L"sorceressWalk");
		SHARED_MAT tex6 = RESOURCE_FIND(Material, L"sorceressSpecialCast");
		SHARED_MAT tex7 = RESOURCE_FIND(Material, L"sorceressGetHit");
		SHARED_MAT tex8 = RESOURCE_FIND(Material, L"sorceressTownWalk");

		SHARED_MAT tex9 = RESOURCE_FIND(Material, L"sorceressDead");

		Vector3 scale = GET_SCALE(GetOwner());
		Vector2 scaleOffset = Vector2(0.f, scale.y * 4);

		for (int i = 0; i < (UINT)eSixteenDirection::End; ++i)
		{
			mAnimator->Create(
				sorceressAnimationString[(UINT)ePlayerAnimationType::Run] + sixteenDirectionString[i]
				, tex4->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Run].y * i)
				, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Run]
				, sorceressAnimationLength[(UINT)ePlayerAnimationType::Run]
				, Vector2::Zero
				, Vector2(0.f, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Run].y * 4)
				, 0.07f
			);
			mAnimator->Create(
				sorceressAnimationString[(UINT)ePlayerAnimationType::SpecialCast] + sixteenDirectionString[i]
				, tex6->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)ePlayerAnimationType::SpecialCast].y * i)
				, sorceressAnimationSizes[(UINT)ePlayerAnimationType::SpecialCast]
				, sorceressAnimationLength[(UINT)ePlayerAnimationType::SpecialCast]
				, Vector2(0.f, -5.f)
				, Vector2(0.f, sorceressAnimationSizes[(UINT)ePlayerAnimationType::SpecialCast].y * 4)
				, 0.03f
			);
			mAnimator->Create(
				sorceressAnimationString[(UINT)ePlayerAnimationType::Natural] + sixteenDirectionString[i]
				, tex3->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Natural].y * i)
				, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Natural]
				, sorceressAnimationLength[(UINT)ePlayerAnimationType::Natural]
				, Vector2::Zero
				, Vector2(0.f, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Natural].y * 4)
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
				, Vector2(0.f, sorceressAnimationSizes[(UINT)ePlayerAnimationType::GetHit].y * 4)
				, 0.05f
			);
			mAnimator->Create(
				sorceressAnimationString[(UINT)ePlayerAnimationType::Attack1] + sixteenDirectionString[i]
				, tex1->GetTexture()
				, Vector2(0.0f, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Attack1].y * i)
				, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Attack1]
				, sorceressAnimationLength[(UINT)ePlayerAnimationType::Attack1]
				, Vector2::Zero
				, Vector2(0.f, sorceressAnimationSizes[(UINT)ePlayerAnimationType::Attack1].y)
				, 0.05f
			);
			mAnimator->StartEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::SpecialCast] + sixteenDirectionString[i])
			= std::make_shared<std::function<void()>>([this]()
				{
					if (PlayerManager::GetSkill(activeSkillIndex) == eSkillType::inferno)
					{
						mAnimator->SetAnimationStartIndex(9);
						mAnimator->SetAnimationEndIndex(12);
					}
					else
						mAnimator->SetAnimationStartIndex(0);

			        mAnimator->SetAnimationProgressIndex(10);
			        GetOwner()->SetBattleState(GameObject::eBattleState::Cast);
				});
			mAnimator->ProgressEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::SpecialCast] + sixteenDirectionString[i])
				= std::make_shared<std::function<void()>>([=]()
	    	{
				if (PlayerManager::GetSkill(activeSkillIndex) == eSkillType::inferno)
				{
					if (skillMake)
					{
						if (nullptr != mSkill)
						{
							if (mSkill->GetSkillFire())
							{
								int endIndex = mAnimator->GetActiveAnimation()->GetAltasLength();
								mAnimator->SetAnimationEndIndex(endIndex);
								skillMake = false;
							}
						}
						else
						{
							skillMake = false;
							int endIndex = mAnimator->GetActiveAnimation()->GetAltasLength();
							mAnimator->SetAnimationEndIndex(endIndex);
						}
					}
					else
					{
						if (bFire)
						{
							PlayerManager::player->UseMana(1);
							makeSkill(PlayerManager::GetSkill(activeSkillIndex)
								, activeSkillIndex
								, GET_POS(PlayerManager::player)
								, eLayerType::PlayerSkill);
							bFire = false;
						}
					}
				}
				else
				{
					if (bFire)
					{
						PlayerManager::player->UseMana(1);
						makeSkill(PlayerManager::GetSkill(activeSkillIndex)
							, activeSkillIndex
							, GET_POS(PlayerManager::player)
							, eLayerType::PlayerSkill);
						bFire = false;
					}
				}
			   
			});
			//mAnimator->EndEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::SpecialCast] + sixteenDirectionString[i])
			//	= std::make_shared<std::function<void()>>([this]()
			//{

			//});
			//mAnimator->EndEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::SpecialCast] + sixteenDirectionString[i])
			mAnimator->CompleteEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::SpecialCast] + sixteenDirectionString[i])
				= std::make_shared<std::function<void()>>([this]()
					{
						if (PlayerManager::GetSkill(activeSkillIndex) == eSkillType::inferno)
						{
							if (!skillMake)
							{
								GetOwner()->SetBattleState(GameObject::eBattleState::Idle);
							}
						}
						else
						{
							mAnimator->SetAnimationStartIndex(0);
							GetOwner()->SetBattleState(GameObject::eBattleState::Idle);
						}

					});
			mAnimator->EndEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::SpecialCast] + sixteenDirectionString[i])
				= std::make_shared<std::function<void()>>([this]()
			{
				if (PlayerManager::GetSkill(activeSkillIndex) == eSkillType::inferno)
				{
				     if(!skillMake)
				     {
					     GetOwner()->SetBattleState(GameObject::eBattleState::Idle);
				     }
				}else
				{
					mAnimator->SetAnimationStartIndex(0);
					GetOwner()->SetBattleState(GameObject::eBattleState::Idle);
				}
				
			});

			mAnimator->StartEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::Attack1] + sixteenDirectionString[i])
				= std::make_shared<std::function<void()>>([this]()
			{
				//mAnimator->SetAnimationProgressIndex(0);
				mAnimator->SetAnimationProgressIndex(14);
				mAnimator->SetAnimationStartIndex(0);
				AnimationStart(GameObject::eBattleState::Attack);
			});
			mAnimator->EndEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::Attack1] + sixteenDirectionString[i])
				= std::make_shared<std::function<void()>>([this]() { AnimationComplete(GameObject::eBattleState::Idle); });
			mAnimator->ProgressEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::Attack1] + sixteenDirectionString[i])
				= std::make_shared<std::function<void()>>([this]()
			{
				AttackProgress();
			});

			mAnimator->StartEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::GetHit] + sixteenDirectionString[i])
				= std::make_shared<std::function<void()>>([this]() { Hit(true, GameObject::eBattleState::Hit); });
			mAnimator->EndEvent(sorceressAnimationString[(UINT)ePlayerAnimationType::GetHit] + sixteenDirectionString[i])
				= std::make_shared<std::function<void()>>([this]() { Hit(false, GameObject::eBattleState::Idle); });
		}

		mDirection = (int)eSixteenDirection::Down;
		mAnimationType = ePlayerAnimationType::Natural;
		mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection], true);
	}
	void PlayerScript::Update()
	{
		if (nullptr == PlayerManager::player)
			return;
		MakeDirection();

		mHead->SetAnimationType((int)mAnimationType);
		mLeftArm->SetAnimationType((int)mAnimationType);
		mRightArm->SetAnimationType((int)mAnimationType);
		mBody->SetAnimationType((int)mAnimationType);
		mLeg->SetAnimationType((int)mAnimationType);
		mRightHand->SetAnimationType((int)mAnimationType);

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
		if (Input::GetKeyDownOne(eKeyCode::RBUTTON))
		{
			mAnimationType = ePlayerAnimationType::SpecialCast;
		    SpecialCastAnimation(1);
		}

		SpecialAttackAnimationConitnue();

		if (PlayerManager::player->GetHit())
		{
			mAnimationType = ePlayerAnimationType::GetHit;
			SET_SCALE_XYZ(GetOwner(), sorceressAnimationSizes[(UINT)mAnimationType].x, sorceressAnimationSizes[(UINT)mAnimationType].y, 0.f);
			if (mAnimator->GetActiveAnimation()->GetKey() != sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection])
				mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection], false);

			mAudioSource->Play(ePlayerVoiceSoundType::Hit);
		}
		if (GetStun())
		{
			GetOwner()->SetBattleState(GameObject::Idle);
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
			ePlayerRunSoundType prst = ePlayerRunSoundType::End;
			if (StageManager::stageNum == -1)
				prst = ePlayerRunSoundType::PlayerStoneRun;
			if (StageManager::stageNum == 5)
				prst = ePlayerRunSoundType::PlayerOStoneRun;
			if (StageManager::stageNum == 6)
				prst = ePlayerRunSoundType::PlayerOStoneRun;
			if (StageManager::stageNum == 0)
				prst = ePlayerRunSoundType::PlayerDirtRun;
			if (StageManager::stageNum == 1)
				prst = ePlayerRunSoundType::PlayerStoneRun;
			if (StageManager::stageNum == 2)
				prst = ePlayerRunSoundType::PlayerSandRun;
			if (StageManager::stageNum == 3)
				prst = ePlayerRunSoundType::PlayerOStoneRun;
			if (StageManager::stageNum == 4)
				prst = ePlayerRunSoundType::PlayerOStoneRun;
			mAudioSource->PlaySounds(prst);
		}
		ElseAnimationPlay();
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
		GetOwner()->SetBattleState(state);
	}
	void PlayerScript::AnimationComplete(GameObject::eBattleState state)
	{
		GetOwner()->SetBattleState(state);
	}
	void PlayerScript::Hit(bool hit, GameObject::eBattleState state)
	{
		PlayerManager::player->SetHit(hit);
		GetOwner()->SetBattleState(state);
		//mRSO->ActiveOverlay();
	}

    void PlayerScript::SpecialAttackAnimationConitnue()
    {
		if (mAnimationType != ePlayerAnimationType::SpecialCast) return;

		int prevIndex = mAnimator->GetAnimationIndex();

		if (mAnimator->GetActiveAnimation()->GetKey() != sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection])
		{
			SET_SCALE_XYZ(GetOwner(), sorceressAnimationSizes[(UINT)mAnimationType].x
				, sorceressAnimationSizes[(UINT)mAnimationType].y, 0.f);

			mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection], true);
			mAnimator->SetAnimationIndex(prevIndex);
		}
    }

    void PlayerScript::AttackProgress()
	{
		if (PlayerManager::player->GetRangeCollider()->GetOnEnter()
			|| PlayerManager::player->GetRangeCollider()->GetOnStay())
		{
			for (Collider2D* col : PlayerManager::player->GetRangeCollider()->GetCollidereds())
			{
				Monster* mon = dynamic_cast<Monster*>(col->GetOwner());
				mon->Hit(PlayerStatus::damage);
			}
		}
	}

	void PlayerScript::SetStun(float second)
	{
		dynamic_cast<Player*>(GetOwner())->Stun(second);
	}
	bool PlayerScript::GetStun()
	{
		return dynamic_cast<Player*>(GetOwner())->GetStun();
	}

	void PlayerScript::makeSkill(eSkillType skillType, int activeSkillIndex, Vector3 vector3Pos, eLayerType fireLayerType)
	{
		if(skillType == eSkillType::telekinesis)
		{
			AudioSource* as = GET_COMP(GetOwner(), AudioSource);
			std::wstring name = skillSoundPath[(int)skillType][0];
			if (as)
				as->Play(name, skillSoundLoop[(int)skillType], true);
		}
		

		switch (skillFunctionTypes[(int)skillType])
		{
		case m::eSkillFunctionType::Straight:
		{
			mSkill = new SkillStraight(skillType, vector3Pos, skillSpeed[(int)skillType]);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		break;
		case m::eSkillFunctionType::Fall:
		{
			Vector3 unprojMousePos = MouseManager::UnprojectionMousePos(GET_POS(GetOwner()).z, GetOwner()->GetCamera());
			unprojMousePos.y += 300.f;
			unprojMousePos.z = GET_POS(GetOwner()).z;
			mSkill = new SkillFall(skillType, unprojMousePos);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		case m::eSkillFunctionType::FallExplosion:
		{
			Vector3 unprojMousePos = MouseManager::UnprojectionMousePos(GET_POS(GetOwner()).z, GetOwner()->GetCamera());
			unprojMousePos.z = GET_POS(GetOwner()).z;
			mSkill = new SkillFallExplosion(skillType, unprojMousePos, fireLayerType);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		break;
		case m::eSkillFunctionType::MultiFall:
		{
			Vector3 unprojMousePos = MouseManager::UnprojectionMousePos(GET_POS(GetOwner()).z, GetOwner()->GetCamera());
			unprojMousePos.y += 300.f;
			unprojMousePos.z = GET_POS(GetOwner()).z;
			mSkill = new SkillMultiFire(unprojMousePos, skillType, 20, (int)SkillMultiFire::eFireType::RandomFall, fireLayerType, Vector2(200.f, 50.f));
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		break;
		case m::eSkillFunctionType::LinearStraight:
		{
			int count = 0;
			if (skillType == eSkillType::inferno)
				count = 40;
			else
				count = 20;
			mSkill = new SkillMultiFire(GET_POS(GetOwner()), skillType, count, (int)SkillMultiFire::eFireType::Linear, fireLayerType);
			mSkill->SetCamera(GetOwner()->GetCamera());
			//mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		break;
		case m::eSkillFunctionType::MultiStraight:
		{
			mSkill = new SkillMultiFire(GET_POS(GetOwner()), skillType, 6
				, (int)SkillMultiFire::eFireType::RadialRandomStraight, fireLayerType, Vector2(0.f, 0.5f), GetOwner()->GetCamera());
			mSkill->SetCamera(GetOwner()->GetCamera());
			//skill->SkillFire(); 
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		break;
		case m::eSkillFunctionType::FixedMultiStraight:
		{
			mSkill = new SkillMultiFire(GET_POS(GetOwner()), skillType, 20
				, (int)SkillMultiFire::eFireType::FixedLinear, fireLayerType, Vector2::Zero, GetOwner()->GetCamera(), 0.08f);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		break;
		case m::eSkillFunctionType::Wall:
		{
			mSkill = new SkillWall(skillType, GET_POS(GetOwner()), GetOwner()->GetCamera(), eLayerType::PlayerSkill);
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		break;
		case m::eSkillFunctionType::Follower:
		{
			mSkill = new SkillFollowing(skillType, GetOwner(), 10.f / 0.08f, GET_POS(GetOwner()), GetOwner()->GetCamera());
			mSkill->SetSkillOwnerLayer(fireLayerType);
			((SkillFollowing*)mSkill)->SetFollowerGenerateTime(0.08f);
			((SkillFollowing*)mSkill)->SetFollowerLoopCount(5);
			((SkillFollowing*)mSkill)->Initialize();
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		break;
		case m::eSkillFunctionType::CircleFire:
		{
			mSkill = new SkillMultiFire(GET_POS(GetOwner()), skillType, 64, (int)SkillMultiFire::eFireType::Circle, fireLayerType);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		break;
		case m::eSkillFunctionType::Buff:
		{
			mSkillBuff = new SkillBuff(GetOwner(), activeSkillIndex, skillType);
			mSkillBuff->SetCamera(GetOwner()->GetCamera());
			mSkillBuff->ActiveOverlay();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkillBuff);
		}
		break;
		case m::eSkillFunctionType::Orb:
		{
			mSkill = new SkillOrb(skillType, GET_POS(GetOwner()), skillSpeed[(int)skillType], fireLayerType);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		break;
		case m::eSkillFunctionType::Summons:
		{
			Vector3 unprojMousePos = MouseManager::UnprojectionMousePos(GET_POS(GetOwner()).z, GetOwner()->GetCamera());
			unprojMousePos.z = GET_POS(GetOwner()).z;
			SkillSummons* ss = new SkillSummons((int)eSummonsType::Hydra, unprojMousePos, unprojMousePos, 100.f);
			ss->SetCamera(GetOwner()->GetCamera());
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, ss);
		}
		break;
		case m::eSkillFunctionType::MultiSummons:
		{
			Vector3 unprojMousePos = MouseManager::UnprojectionMousePos(GET_POS(GetOwner()).z, GetOwner()->GetCamera());
			unprojMousePos.z = GET_POS(GetOwner()).z;
			SkillMultiSummons* sms = new SkillMultiSummons(eSummonsType::Hydra, unprojMousePos
				, GetOwner()->GetCamera(), 10.f, 3, fireLayerType);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, sms);
		}
		break;
		case m::eSkillFunctionType::Push:
		{
			SkillPush::Push(GET_POS(GetOwner()), GetOwner()->GetCamera());
		}
		break;
		case m::eSkillFunctionType::RangeDamage:
		{
			mSkill = new SkillRange(skillType, GetOwner(), fireLayerType, GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		break;
		case m::eSkillFunctionType::Chain:
		{
			mSkill = new SkillChain(skillType, GET_POS(GetOwner()), 2, fireLayerType, GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		break;
		case m::eSkillFunctionType::Aura:
		{
			eAuraType aType = skillAuraTypes[(int)skillType];
			mAura->SetAura(aType, fireLayerType, 10.f);
			mAura->AuraActive();
		}
		break;
		case m::eSkillFunctionType::None:
			break;
		case m::eSkillFunctionType::END:
			break;
		default:
		{
			mSkill = new Skill(skillType, vector3Pos);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		break;
		}
		if (nullptr != mSkill || nullptr != mSkillBuff)
		{
			skillMake = true;
		}
	}

	void PlayerScript::MakeDirection()
	{
		Vector3 direction = PlayerManager::player->GetDirection();

		float degree = RadianToDegree(atan2(direction.x, direction.y));

		int n = degree / (180.f / 9.f);
		
		if (n > 8) n = 8;

		int iBPDirection = 0;
		if (n > 0)
		{
			mDirection = plusSixteenDirections[n];
		}
		else
		{
			mDirection = minusSixteenDirections[abs(n)];
		}

		int m = degree / (180.f / 18.f);
		if (m > 0)
		{
			iBPDirection = pathPlusSixteenDirections[m];
		}
		else
		{
			iBPDirection = pathMinusSixteenDirections[abs(m)];
		}
		
		
		if (mHead)
			mHead->SetDirection(iBPDirection);
		if(mLeftArm)
			mLeftArm->SetDirection(iBPDirection);
		if(mRightArm)
			mRightArm->SetDirection(iBPDirection);
		if(mBody)
			mBody->SetDirection(iBPDirection);
		if(mLeg)
			mLeg->SetDirection(iBPDirection);
		if(mRightHand)
			mRightHand->SetDirection(iBPDirection);
	}

	void PlayerScript::SpecialCastAnimation(int skillIndex)
	{
		if (GetOwner()->GetBattleState() == GameObject::Cast) return;

		bFire = true;

		if (castBack[(int)skillCastTypes[(UINT)PlayerManager::GetSkill(skillIndex)]])
		{
			mBackSO->SetSkillIndex(skillIndex);
			mBackSO->SetSkillCastType(skillCastTypes[(UINT)PlayerManager::GetSkill(skillIndex)]);
			mBackSO->ActiveOverlay();
		}
		if (skillIndex == 1)
			mRSO->ActiveOverlay();
		else
			mLSO->ActiveOverlay();

		activeSkillIndex = skillIndex;
		SET_SCALE_XYZ(GetOwner(), sorceressAnimationSizes[(UINT)mAnimationType].x, sorceressAnimationSizes[(UINT)mAnimationType].y, 0.f);

		if (mAnimator->GetActiveAnimation()->GetKey() != sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection])
		{
			bool loop = false;
			if (PlayerManager::GetSkill(activeSkillIndex) == eSkillType::inferno) loop = true;

			mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection], loop);
		}

	}

	void PlayerScript::ElseAnimationPlay()
	{
		if (mAnimator->GetActiveAnimation()->GetKey() != sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection])
		{
			SET_SCALE_XYZ(GetOwner(), sorceressAnimationSizes[(UINT)mAnimationType].x, sorceressAnimationSizes[(UINT)mAnimationType].y, 0.f);
			WSTRING_SUBSTR(mAnimator->GetActiveAnimation()->GetKey(), L'@', subStr1);

			int prevIndex = 0;
			if (subStr1 == sorceressAnimationString[(UINT)ePlayerAnimationType::Run])
			{
				prevIndex = mAnimator->GetAnimationIndex();
			}
			mAnimator->PlayAnimation(sorceressAnimationString[(UINT)mAnimationType] + sixteenDirectionString[(UINT)mDirection], true);
			if (mAnimationType == ePlayerAnimationType::Run)
			{
				if (prevIndex != 0)
				{
					if (prevIndex + 1 < mAnimator->GetActiveAnimation()->GetAltasLength())
						mAnimator->SetAnimationIndex(prevIndex + 1);
					else
						mAnimator->SetAnimationIndex(prevIndex);
				}
			}
		}
	}
};