#include "mMonsterScript.h"

#include "../engine_source/mSceneManager.h"
#include "../engine_source/mMaterial.h"
#include "../engine_source/mAnimator.h"
#include "../engine_source/mAnimation.h"
#include "../engine_source/mTime.h"

#include "mPlayer.h"
#include "mMonster.h"
#include "mPlayerManager.h"
#include "mSkillBuff.h"
#include "mSkillFallExplosion.h"
#include "mSkillOverlay.h"
#include "mSkillMultiFire.h"
#include "mSkillOrb.h"

namespace m
{
	template <typename T>
	MonsterScript<T>::MonsterScript()
		: mAnimator(nullptr)
		, mSkill(nullptr)
		, mMonster(nullptr)
		, mClass(eMonsterClass::Normal)
		, bFire(false)
		, fAttackDelay(0.f)
		, mDirection(0)
	    , skillMake(false)
		, mLeftHand(nullptr)
		, mRightHand(nullptr)

	{
		curMonsterData = T{};
		mClass = curMonsterData.mClass;
	}
	template <typename T>
	MonsterScript<T>::~MonsterScript()
	{
	}
	template <typename T>
	void MonsterScript<T>::Initialize()
	{
		mAnimator = GET_COMP(GetOwner(), Animator);
		dynamic_cast<MoveAbleObject*>(GetOwner())->SetMadePath(curMonsterData.bPathImage);
		dynamic_cast<MoveAbleObject*>(GetOwner())->SetSixteenDirection(false);
		Scene* curScene = SceneManager::GetActiveScene();
		Monster* monster = dynamic_cast<Monster*>(GetOwner());
		mSO = new SkillOverlay();
		mSO->SetActiveOwner(GetOwner());
		curScene->AddGameObject(eLayerType::MonsterSkill, mSO);

		//mLeftHand = new MonsterHand(monster, curMonsterData.mMonsterType, false);

		if (curMonsterData.bHandAnim)
		{
			mRightHand = new MonsterHand(monster, curMonsterData.mMonsterType, true);

			//mLeftHand->SetCamera(GetOwner()->GetCamera());
			mRightHand->SetCamera(GetOwner()->GetCamera());
			Animator* rightAnimator = GET_COMP(mRightHand, Animator);
			rightAnimator->SetSyncAnimator(mAnimator);
			rightAnimator->Sync();
			curScene->AddGameObject(eLayerType::Monster, mRightHand);
		}
		//curScene->AddGameObject(eLayerType::Monster, mLeftHand);

		if (curMonsterData.bPathImage)
		{
			mPlusDirections = pathPlusEightDirections;
			mMinusDirections = pathMinusEightDirections;
			animStrings = pathSixteenDirectionString;
		}
		else
		{
			mPlusDirections = plusEightDirections;
			mMinusDirections = minusEightDirections;
			animStrings = sixteenDirectionString;
		}

		int m = 0;
		for (int i = 0; i < (UINT)T::eAnimationType::End; ++i)
		{
			if (curMonsterData.textureString[i] == L"") continue;

			SHARED_MAT mat = RESOURCE_FIND(Material, curMonsterData.textureString[i]);

			for (int j = 0; j < 8; ++j)
			{
				if (!curMonsterData.bPathImage) m = eEightDirection[j];
				else m = j;

				mAnimator->Create(
					curMonsterData.animationString[i] + animStrings[m]
					, mat->GetTexture()
					, Vector2(0.0f, curMonsterData.animationSizes[i].y * j)
					, curMonsterData.animationSizes[i]
					, curMonsterData.animationLength[i]
					, curMonsterData.animationOffset[i]
					, curMonsterData.animationDuration[i]
				);
				if (i == (UINT)T::eAnimationType::Natural)
				{
					mAnimator->StartEvent(curMonsterData.animationString[i] + animStrings[m])
						= [this]()
					{
						mAnimator->SetAnimationStartIndex(0);
					};
				}
				if (i == (UINT)T::eAnimationType::Attack1)
				{
					mAnimator->StartEvent(curMonsterData.animationString[i] + animStrings[m])
						= [this]()
					{
						AnimationStart(GameObject::eBattleState::Attack);
						mAnimator->SetAnimationProgressIndex(curMonsterData.animProgressStartIndex[(UINT)T::eAnimationType::Attack1]);
					};
					mAnimator->EndEvent(curMonsterData.animationString[i] + animStrings[m])
						= [this]()
					{
						//fAttackDelay = 0.f;
						AnimationComplete(GameObject::eBattleState::Idle);
						mAnimator->SetAnimationProgressIndex(0);
					};
					mAnimator->ProgressEvent(curMonsterData.animationString[i] + animStrings[m])
						= [this]() { AttackProgress(); };
				}
				if (i == (UINT)T::eAnimationType::Hit)
				{
					mAnimator->StartEvent(curMonsterData.animationString[i] + animStrings[m])
						= [this]()
					{
						Hit(true, GameObject::eBattleState::Hit);
						//mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)T::eAnimationType::Hit]);
					};
					mAnimator->EndEvent(curMonsterData.animationString[i] + animStrings[m])
						= [this]() { Hit(false, GameObject::eBattleState::Idle); };
				}
				if (i == (UINT)T::eAnimationType::SpecialCast)
				{
					mAnimator->StartEvent(curMonsterData.animationString[i] + animStrings[m])
						= [this]()
					{
						//if (skillCastTypes[(int)skillType] != eSkillCastType::END)
						//{
						//	mSO->SetSkillCastType(skillCastTypes[(int)skillType]);
						//	mSO->ActiveOverlay();
						//}
						mAnimator->SetAnimationProgressIndex(curMonsterData.animProgressStartIndex[(UINT)T::eAnimationType::SpecialCast]);
						mAnimator->SetAnimationEndIndex(curMonsterData.animEndIndex[(UINT)T::eAnimationType::SpecialCast]);
						//mAnimator->SetAnimationProgressStartIndex(curMonsterData.animProgressStartIndex[i]);
					};
					mAnimator->ProgressEvent(curMonsterData.animationString[i] + animStrings[m])
						= [this]()
					{
						if(skillMake)
						{
							if (nullptr != mSkill)
							{
								if (mSkill->GetSkillFire())
								{
									mMonster->SetBattleState(GameObject::eBattleState::Idle);
									skillMake = false;
								}
							}
							else
							{
								mMonster->SetBattleState(GameObject::eBattleState::Idle);
								skillMake = false;
							}
						}
						else
						{
							int randSkillIndex = 0;
							eSkillType skilltype = curMonsterData.mSpecialSkills[randSkillIndex];
							if (skilltype != eSkillType::END)
							{
								makeMonsterSkill(skilltype
									, GET_POS(GetOwner())
									, eLayerType::MonsterSkill
									, curMonsterData.mSpecialSkillAddFunction[randSkillIndex]
									, curMonsterData.mSpecialSkillCount[randSkillIndex]
								);
							}
						}
					};
					mAnimator->EndEvent(curMonsterData.animationString[i] + animStrings[m])
						= [this]()
					{
						//if (skillMake)
						//{
						//	if (nullptr != mSkill)
						//	{
						//		if (mSkill->GetSkillFire())
						//		{
						//			GetOwner()->SetBattleState(GameObject::eBattleState::Idle);
						//			skillMake = false;
						//		}
						//	}
						//	else
						//	{
						//		GetOwner()->SetBattleState(GameObject::eBattleState::Idle);
						//		skillMake = false;
						//	}
						//}
					};
				}
			}
		}
		mAnimationType = T::eAnimationType::Natural;
		mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], true);
		SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);

		mMonster = static_cast<Monster*>(GetOwner());
	}
	template <typename T>
	void MonsterScript<T>::Update()
	{
		Script::Update();
		if (nullptr == mMonster)
			return;

		MakeDirection();

		//if(!bCanDamaged)
		//	fCanDamagedDelay += Time::fDeltaTime();

		//if (fCanDamagedDelay >= 10.f)
		//{
		//	bCanDamaged = true;
		//	fCanDamagedDelay = 0.f;
		//}


		//if (!skillMake)
			
		//if(mLeftHand)
			//mLeftHand->SetDirection(mDirection);

		if (mRightHand)
			mRightHand->SetDirection(mDirection);

		if (mMonster->GetBattleState() == GameObject::eBattleState::Idle
			|| mMonster->GetBattleState() == GameObject::eBattleState::Run)
		{
			if (rand() % 100 == 7 && curMonsterData.textureString[(UINT)T::eAnimationType::SpecialCast] != L"")
			{
				SpecialAttackAnimation();
			}
		}

		if (mMonster->GetBattleState() == GameObject::eBattleState::Cast
			&& curMonsterData.textureString[(UINT)T::eAnimationType::SpecialCast] != L"")
		{
			SpecialAttackAnimationConitnue();
		}

		if (mMonster->Arrival())
		{
			AttackAnimation();
		}

		if (curMonsterData.mClass != eMonsterClass::Boss && mMonster->GetHit())
		{
			//GetOwner()->SetBattleState(GameObject::Hit);
			HitAnimation();
		}

		//mLeftHand->SetAniType((int)mAnimationType);
		if (mRightHand)
			mRightHand->SetAniType((int)mAnimationType);

		if (
			GetOwner()->GetBattleState() == GameObject::Idle
			|| GetOwner()->GetBattleState() == GameObject::Run
			)
		{
			if (mMonster->StopF())
			{
				GetOwner()->SetBattleState(GameObject::Idle);
				mAnimationType = T::eAnimationType::Natural;
			}
			else
			{
				GetOwner()->SetBattleState(GameObject::Run);
				mAnimationType = T::eAnimationType::Run;
			}

			ElseAnimationPlay();
			//mLeftHand->SetAniType((int)mAnimationType);
			if (mRightHand)
				mRightHand->SetAniType((int)mAnimationType);
		}
	}
	template <typename T>
	void MonsterScript<T>::ElseAnimationPlay()
	{
		if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection]
			&& curMonsterData.textureString[(UINT)mAnimationType] != L"")
		{

			SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);

			WSTRING_SUBSTR(mAnimator->GetActiveAnimation()->GetKey(), L'@', subStr1);

			int prevIndex = 0;
			if (subStr1 == curMonsterData.animationString[(UINT)T::eAnimationType::Run])
			{
				prevIndex = mAnimator->GetAnimationIndex();
			}

			mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], true);
			if (mAnimationType == T::eAnimationType::Run)
			{
				mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)mAnimationType]);
				mAnimator->SetAnimationIndex(prevIndex);
			}
		}
	}
	template <typename T>
	void MonsterScript<T>::HitAnimation()
	{
		//if (mMonster->GetBattleState() != GameObject::eBattleState::Idle) return;

		mAnimationType = T::eAnimationType::Hit;
		SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
		if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection])
		{
			mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], false);
		}
	}

	template <typename T>
	void MonsterScript<T>::AttackAnimation()
	{
		if(mMonster->GetBattleState() != GameObject::eBattleState::Idle) return;

		if (mMonster->GetRangeCollider()->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
		{
			fAttackDelay += Time::fDeltaTime();
			if (curMonsterData.fAttackDelay <= fAttackDelay)
			{
				fAttackDelay = 0.f;
				//int randAttackMotion = rand() % 2 + 1;
				//mAnimationType = randAttackMotion == 1 ? T::eAnimationType::Attack1 : T::eAnimationType::Attack2;
				GetOwner()->SetBattleState(GameObject::Attack);
				mAnimationType = T::eAnimationType::Attack1;
				SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
				if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection])
				{
					mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], false);
				}
			}
		}
	}

	template <typename T>
	void MonsterScript<T>::SpecialAttackAnimationConitnue()
	{
		WSTRING_SUBSTR(mAnimator->GetActiveAnimation()->GetKey(), L'@', subStr1);
		int prevIndex = 0;
		if (subStr1 == curMonsterData.animationString[(UINT)T::eAnimationType::SpecialCast])
		{
			prevIndex = mAnimator->GetAnimationIndex();
		}
		mAnimationType = T::eAnimationType::SpecialCast;
		SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
		if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection])
		{
			mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], true);
			mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)T::eAnimationType::SpecialCast]);
			mAnimator->SetAnimationIndex(prevIndex);
		}
	}
	template <typename T>
	void MonsterScript<T>::SpecialAttackAnimation()
	{
		if (mMonster->GetSightCollider()->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
		{
			GetOwner()->SetBattleState(GameObject::Cast);
			mAnimationType = T::eAnimationType::SpecialCast;
			SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
			if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection])
			{
				mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], true);
				mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)T::eAnimationType::SpecialCast]);
			}
		}
	}

	template <typename T>
	void MonsterScript<T>::LateUpdate()
	{
	}
	template <typename T>
	void MonsterScript<T>::Render()
	{
	}

	template <typename T>
	void MonsterScript<T>::MakeDirection()
	{
		Vector3 initPos = mMonster->GetPrevPosition();
		Vector3 destPos = mMonster->GetDestPosition();

		Vector3 moveVector = destPos - initPos;

		moveVector.Normalize();

		degree = RadianToDegree(atan2(moveVector.x, moveVector.y));


		int n = degree / (180.f / 5.f);
		if (n > 4) n = 4;

		if (n > 0)
			mDirection = mPlusDirections[n];
		else
			mDirection = mMinusDirections[abs(n)];
	}

	template <typename T>
	void MonsterScript<T>::AnimationStart(GameObject::eBattleState state)
	{
		GetOwner()->SetBattleState(state);
	}
	template <typename T>
	void MonsterScript<T>::AnimationComplete(GameObject::eBattleState state)
	{
		GetOwner()->SetBattleState(state);
	}

	//template<typename T>
	//void MonsterScript<T>::OnCollisionEnter(Collider2D* other)
	//{
	//	
	//}

	//template<typename T>
	//void MonsterScript<T>::OnCollisionStay(Collider2D* other)
	//{
	//	
	//}

	//template<typename T>
	//void MonsterScript<T>::OnCollisionExit(Collider2D* other)
	//{
	//}

	template<typename T>
	void MonsterScript<T>::AttackProgress()
	{
		if (mMonster->GetRangeCollider()->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
		{
			PlayerManager::player->Hit(10);
		}
	}

	template<typename T>
	void MonsterScript<T>::Hit(bool hit, GameObject::eBattleState state)
	{
		mMonster->SetHit(hit);
		GetOwner()->SetBattleState(state);
	}
	template<typename T>
	void MonsterScript<T>::makeMonsterSkill(eSkillType skillType, Vector3 vector3Pos
		, eLayerType fireLayerType, int addFunction, int skillCount)
	{
		Vector3 targetPos = TileManager::GetPlayerPosition();
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
			mSkill = new SkillFall(skillType, targetPos);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		case m::eSkillFunctionType::FallExplosion:
		{
			mSkill = new SkillFallExplosion(skillType, targetPos, fireLayerType);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
			break; 
		case m::eSkillFunctionType::MutiFall:
		{
			mSkill = new SkillMultiFire(targetPos, skillType, skillCount, addFunction, fireLayerType, Vector2(200.f, 50.f));
			mSkill->SetCamera(GetOwner()->GetCamera());
			//skill->SkillFire(); 
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
			break; 
		case m::eSkillFunctionType::MultiStraight:
		case m::eSkillFunctionType::Raidal:
		{
			mSkill = new SkillMultiFire(GET_POS(GetOwner()), skillType, skillCount, addFunction, fireLayerType);
			mSkill->SetCamera(GetOwner()->GetCamera());
			//skill->SkillFire(); 
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
			break; 
		case m::eSkillFunctionType::Buff:
		{
			mSkillBuff= new SkillBuff(GetOwner(), -1, skillType); 
			mSkillBuff->SetCamera(GetOwner()->GetCamera()); 
			mSkillBuff->ActiveOverlay(); 
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::PlayerSkill, mSkillBuff);
		}
			break; 
		case m::eSkillFunctionType::Orb:
		{
			mSkill = new SkillOrb(skillType, GET_POS(GetOwner()), 300.f);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::PlayerSkill, mSkill);
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
}
