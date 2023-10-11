#include "mMonsterScript.h"

#include "../engine_source/mSceneManager.h"
#include "../engine_source/mMaterial.h"
#include "../engine_source/mAnimator.h"
#include "../engine_source/mAnimation.h"
#include "../engine_source/mTime.h"

#include "mPlayer.h"
#include "mMonster.h"
#include "mPlayerManager.h"
#include "mSkillAbnormal.h"
#include "mSkillBuff.h"
#include "mSkillFallExplosion.h"
#include "mSkillOverlay.h"
#include "mSkillMultiFire.h"
#include "mSkillOrb.h"
#include "mAura.h"
#include "mShadowObject.h"

namespace m
{
	template <typename T>
	MonsterScript<T>::MonsterScript()
		: mAnimator(nullptr)
		, mSkill(nullptr)
		, mSkillBuff(nullptr), skillMake(false)
		, iCurSkillIndex(0)
		, mLeftHand(nullptr)
		, mRightHand(nullptr)
		, mAura(nullptr), mMonster(nullptr)
		, mClass(eMonsterClass::Normal), mDirection(0), mPlusDirections(nullptr), mMinusDirections(nullptr)
		, animStrings(nullptr)
		, bFire(false)
		, fAttackDelay(0.f)
		, degree(0)
	    , fSkillCenterPosY(0.f)
	{
		mClass = curMonsterData.mClass;
	}

	template <typename T>
	MonsterScript<T>::~MonsterScript()
	{
		if (mAura)
			mAura->SetState(GameObject::eState::Delete);
	}
	template <typename T>
	void MonsterScript<T>::Initialize()
	{
		mAnimator = GET_COMP(GetOwner(), Animator);
		dynamic_cast<MoveAbleObject*>(GetOwner())->SetMadePath(curMonsterData.bPathImage);
		dynamic_cast<MoveAbleObject*>(GetOwner())->SetSixteenDirection(false);
		Scene* curScene = SceneManager::GetActiveScene();
		Monster* monster = dynamic_cast<Monster*>(GetOwner());

		if (curMonsterData.passiveAura != eAuraType::End)
		{
			mAura = new Aura(GetOwner(), curMonsterData.passiveAura, curMonsterData.auraOffSet);
			if (curMonsterData.wsMonsterName.compare(L"메피스토") == 0)
				mAura->FrontAura();

			mAura->AuraActive();
			curScene->AddGameObject(eLayerType::MonsterAura, mAura);
		}


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
		Vector3 scale = GET_SCALE(GetOwner());
		int m = 0;
		for (int i = 0; i < (UINT)MonsterData::eAnimationType::End; ++i)
		{
			if (curMonsterData.textureString[i] == L"") continue;

			SHARED_MAT mat = RESOURCE_FIND(Material, curMonsterData.textureString[i]);

			float centerPosY = 0.f;
			if (curMonsterData.wsMonsterName.compare(L"메피스토") == 0)
			{
				//if (i == (UINT)T::eAnimationType::SpecialCast)
				//{
				//	fSkillCenterPosY = curMonsterData.animationCenterPos[i].y + (curMonsterData.animationSizes[i].y);
				//}

				centerPosY = curMonsterData.animationCenterPos[i].y + (curMonsterData.animationSizes[i].y);
				dynamic_cast<MoveAbleObject*>(GetOwner())->GetShadowObject()->SetShadowOffset(Vector2(50.f, 50.f));

			}
			else if (curMonsterData.wsMonsterName.compare(L"디아블로") == 0)
			{
				if (i == (UINT)T::eAnimationType::SpecialCast)
				{
					fSkillCenterPosY = 20.f;
				}
				centerPosY = curMonsterData.animationCenterPos[i].y + (curMonsterData.animationSizes[i].y * 2.f);
				dynamic_cast<MoveAbleObject*>(GetOwner())->GetShadowObject()->SetShadowOffset(Vector2(50.f, 50.f));
			}
			else
			{
				//if (i == (UINT)T::eAnimationType::SpecialCast)
				//{
				//	fSkillCenterPosY = curMonsterData.animationCenterPos[i].y + (curMonsterData.animationSizes[i].y * 3.f);
				//}
				centerPosY = curMonsterData.animationCenterPos[i].y + (curMonsterData.animationSizes[i].y * 3.f);
			}

			if (curMonsterData.wsMonsterName.compare(L"디아블로") == 0
				&& i == (UINT)MonsterData::eAnimationType::ToDead)
			{
				//diabloToDead2;
				//diabloToDead3;

				float fOffsetY = curMonsterData.animationCenterPos[i].y;
				SHARED_MAT mat1 = RESOURCE_FIND(Material, L"diabloToDead1");
				SHARED_MAT mat2 = RESOURCE_FIND(Material, L"diabloToDead2");
				SHARED_MAT mat3 = RESOURCE_FIND(Material, L"diabloToDead3");
				mAnimator->Create(
					L"dialoToDead1_anim@"
					, mat1->GetTexture()
					, Vector2(0.0f, 0.0f)
					, curMonsterData.animationSizes[(int)MonsterData::eAnimationType::ToDead]
					, curMonsterData.animationLength[(int)MonsterData::eAnimationType::ToDead]
					, curMonsterData.animationOffset[(int)MonsterData::eAnimationType::ToDead]
					, Vector2(0.f, fOffsetY)
					, curMonsterData.animationDuration[(int)MonsterData::eAnimationType::ToDead]
				);

				mAnimator->Create(
					L"dialoToDead2_anim@"
					, mat2->GetTexture()
					, Vector2(0.0f, 0.0f)
					, curMonsterData.animationSizes[(int)MonsterData::eAnimationType::ToDead]
					, curMonsterData.animationLength[(int)MonsterData::eAnimationType::ToDead]
					, curMonsterData.animationOffset[(int)MonsterData::eAnimationType::ToDead]
					, Vector2(0.f, fOffsetY)
					, curMonsterData.animationDuration[(int)MonsterData::eAnimationType::ToDead]
				);
				mAnimator->Create(
					L"dialoToDead3_anim@"
					, mat3->GetTexture()
					, Vector2(0.0f, 0.0f)
					, curMonsterData.animationSizes[(int)MonsterData::eAnimationType::ToDead]
					, mat3->GetTexture()->GetMetaDataWidth() / 266
					, curMonsterData.animationOffset[(int)MonsterData::eAnimationType::ToDead]
					, Vector2(0.f, fOffsetY)
					, curMonsterData.animationDuration[(int)MonsterData::eAnimationType::ToDead]
				);
				mAnimator->EndEvent(L"dialoToDead1_anim@") = std::make_shared<std::function<void()>>([=]()
				{
					wsDiabloDeadAnimationName = L"dialoToDead2_anim@";
				});
				mAnimator->EndEvent(L"dialoToDead2_anim@") = std::make_shared<std::function<void()>>([=]()
				{
					wsDiabloDeadAnimationName = L"dialoToDead3_anim@";
				});
				mAnimator->EndEvent(L"dialoToDead3_anim@") = std::make_shared<std::function<void()>>([=]()
				{
					if (mRightHand)
					{
						GET_COMP(mRightHand, Animator)->SetSyncAnimator(nullptr);
						mRightHand->SetState(GameObject::eState::Delete);
						mRightHand = nullptr;
					}
					if (mAura)
						mAura->SetState(GameObject::eState::Delete);

					GetOwner()->SetBattleState(GameObject::Dead);
				});
				wsDiabloDeadAnimationName = L"dialoToDead1_anim@";
			}
			else
			{
				for (int j = 0; j < 8; ++j)
				{
					if (!curMonsterData.bPathImage) m = eEightDirection[j];
					else m = j;
					std::wstring curAnimStr = curMonsterData.animationString[i] + animStrings[m];
				
					mAnimator->Create(
						curAnimStr
						, mat->GetTexture()
						, Vector2(0.0f, curMonsterData.animationSizes[i].y * j)
						, curMonsterData.animationSizes[i]
						, curMonsterData.animationLength[i]
						, curMonsterData.animationOffset[i]
						, Vector2(curMonsterData.animationCenterPos[i].x
							, centerPosY)
						, curMonsterData.animationDuration[i]
					);
					if (i == (UINT)MonsterData::eAnimationType::Natural)
					{
						mAnimator->StartEvent(curMonsterData.animationString[i] + animStrings[m])
							= std::make_shared<std::function<void()>>([this]()
						{
							mAnimator->SetAnimationStartIndex(0);
						});
					}
					//mAnimator->StartEvent(curMonsterData.animationString[i] + animStrings[m])
					//	= std::make_shared<std::function<void()>>([=]()
					//{
					//	AnimationStart(GameObject::eBattleState::Attack);
					//	mAnimator->SetAnimationProgressIndex(curMonsterData.animProgressStartIndex[i]);
					//};
					if (i == (UINT)MonsterData::eAnimationType::Attack2)
					{
						mAnimator->StartEvent(curMonsterData.animationString[i] + animStrings[m])
							= std::make_shared<std::function<void()>>([this]()
						{
							AnimationStart(GameObject::eBattleState::Attack);
							mAnimator->SetAnimationProgressIndex(curMonsterData.animProgressStartIndex[(UINT)MonsterData::eAnimationType::Attack2]);
						});
					}
					if (i == (UINT)MonsterData::eAnimationType::Attack1)
					{
						mAnimator->StartEvent(curMonsterData.animationString[i] + animStrings[m])
							= std::make_shared<std::function<void()>>([this]()
						{
							AnimationStart(GameObject::eBattleState::Attack);
							mAnimator->SetAnimationProgressIndex(curMonsterData.animProgressStartIndex[(UINT)MonsterData::eAnimationType::Attack1]);
						});
					}
					if (i == (UINT)MonsterData::eAnimationType::Attack1
						|| i == (UINT)MonsterData::eAnimationType::Attack2)
					{
						mAnimator->EndEvent(curMonsterData.animationString[i] + animStrings[m])
							= std::make_shared<std::function<void()>>([this]()
						{
							//fAttackDelay = 0.f;
							AnimationComplete(GameObject::eBattleState::Idle);
							//mAnimator->SetAnimationProgressIndex(0);
						});
						mAnimator->ProgressEvent(curMonsterData.animationString[i] + animStrings[m])
							= std::make_shared<std::function<void()>>([this]() { AttackProgress(); });
					}
					if (i == (UINT)MonsterData::eAnimationType::ToDead)
					{
						//mAnimator->StartEvent(curMonsterData.animationString[i] + animStrings[m]) = std::make_shared<std::function<void()>>([this]()
						//{
						//	//mAnimator->SetAnimationEndIndex(curMonsterData.animationLength[(UINT)MonsterData::eAnimationType::ToDead]);
						//});
						mAnimator->EndEvent(curMonsterData.animationString[i] + animStrings[m])
							= std::make_shared<std::function<void()>>([this]()
						{
							//if (mRightHand)
							//{
							//	GET_COMP(mRightHand, Animator)->SetSyncAnimator(nullptr);
							//	mRightHand->SetState(GameObject::eState::Delete);
							//	mRightHand = nullptr;
							//}
						    if (mAura)
							    mAura->SetState(GameObject::eState::Delete);
							GetOwner()->SetBattleState(GameObject::Dead);
						});
					}
					if (i == (UINT)MonsterData::eAnimationType::Hit)
					{
						mAnimator->StartEvent(curMonsterData.animationString[i] + animStrings[m])
							= std::make_shared<std::function<void()>>([this]()
						{
							fAttackDelay = 0.f;
							Hit(true, GameObject::eBattleState::Hit);
							//mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)T::eAnimationType::Hit]);
						});
						mAnimator->EndEvent(curMonsterData.animationString[i] + animStrings[m])
							= std::make_shared<std::function<void()>>([this]() { Hit(false, GameObject::eBattleState::Idle); });
					}
					if (i == (UINT)T::eAnimationType::SpecialCast
						|| i == (UINT)T::eAnimationType::Special1
						|| i == (UINT)T::eAnimationType::Special2
						|| i == (UINT)T::eAnimationType::Special3
						|| i == (UINT)T::eAnimationType::Special4)
					{
						makeSkillCastAnimation(i, m);
					}
				}
			}
		}
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

		mAnimationType = MonsterData::eAnimationType::Natural;
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
		SetCenterPosY();
		//if (mMonster->GetBattleState() == GameObject::eBattleState::Dead) return;

		MakeDirection();

		//if (!skillMake)

		//if(mLeftHand)
			//mLeftHand->SetDirection(mDirection);

		if (mMonster->GetBattleState() == GameObject::eBattleState::Dead)
		{
			mAnimationType = MonsterData::eAnimationType::Dead;
			return;
		}

		if (mMonster->GetMonsterHp() == 0)
		{
			DeadAnimation();
			return;
		}

		if (mMonster->GetBattleState() == GameObject::eBattleState::Idle
			|| mMonster->GetBattleState() == GameObject::eBattleState::Run
			/*&& (nullptr == mSkill && nullptr == mSkillBuff)*/)
		{
			int selectSpecialSkillBranshNum = rand() % 1000;
			if (selectSpecialSkillBranshNum == (int)T::eAnimationType::SpecialCast
				|| selectSpecialSkillBranshNum == (int)T::eAnimationType::Special1
				|| selectSpecialSkillBranshNum == (int)T::eAnimationType::Special2
				//|| selectSpecialSkillBranshNum == (int)T::eAnimationType::Special3
				//|| selectSpecialSkillBranshNum == (int)T::eAnimationType::Special4
				)
			{
				if (curMonsterData.animationString[selectSpecialSkillBranshNum] != L"")
					SpecialAttackAnimation(selectSpecialSkillBranshNum);
			}
		}

		if (mMonster->GetBattleState() == GameObject::eBattleState::Cast
			&& curMonsterData.animationString[(UINT)MonsterData::eAnimationType::SpecialCast] != L"")
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
		if (mMonster->GetBattleState() != GameObject::eBattleState::ToDead
			|| mMonster->GetBattleState() != GameObject::eBattleState::Dead)
		{
			if (mRightHand)
				mRightHand->SetAniType((int)mAnimationType);
		}


		if (
			GetOwner()->GetBattleState() == GameObject::Idle
			|| GetOwner()->GetBattleState() == GameObject::Run
			)
		{
			if (mMonster->StopF())
			{
				GetOwner()->SetBattleState(GameObject::Idle);
				mAnimationType = MonsterData::eAnimationType::Natural;
			}
			else
			{
				GetOwner()->SetBattleState(GameObject::Run);
				mAnimationType = MonsterData::eAnimationType::Run;
			}

			ElseAnimationPlay();
			//mLeftHand->SetAniType((int)mAnimationType);
			if (mMonster->GetBattleState() != GameObject::eBattleState::ToDead
				|| mMonster->GetBattleState() != GameObject::eBattleState::Dead)
			{
				if (mRightHand)
					mRightHand->SetAniType((int)mAnimationType);
			}
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
			if (subStr1 == curMonsterData.animationString[(UINT)MonsterData::eAnimationType::Run])
			{
				prevIndex = mAnimator->GetAnimationIndex();
			}

			mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], true);
			if (mAnimationType == MonsterData::eAnimationType::Run)
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

		mAnimationType = MonsterData::eAnimationType::Hit;
		SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
		if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection])
		{
			mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], false);
		}
	}

	template <typename T>
	void MonsterScript<T>::AttackAnimation()
	{
		if (mMonster->GetBattleState() != GameObject::eBattleState::Idle) return;


		if (mMonster->GetRangeCollider()->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
		{
			fAttackDelay += Time::fDeltaTime();
			if (curMonsterData.fAttackDelay <= fAttackDelay)
			{
				fAttackDelay = 0.f;

				if (curMonsterData.animationString[(UINT)MonsterData::eAnimationType::Attack1] != L""
					&& curMonsterData.animationString[(UINT)MonsterData::eAnimationType::Attack2] != L"")
				{
					int randAttackMotion = rand() % 2;
					mAnimationType = randAttackMotion == 1 ? MonsterData::eAnimationType::Attack1 : MonsterData::eAnimationType::Attack2;
				}
				else
				{
					mAnimationType = MonsterData::eAnimationType::Attack1;
				}
				GetOwner()->SetBattleState(GameObject::Attack);
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
		if (mAnimationType != MonsterData::eAnimationType::SpecialCast) return;
		//curMonsterData.bSpecialSkillStopInProgress[];

		//WSTRING_SUBSTR(mAnimator->GetActiveAnimation()->GetKey(), L'@', subStr1);

		int prevIndex = mAnimator->GetAnimationIndex();

		SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
		if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection])
		{
			mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], true);
			mAnimator->SetAnimationIndex(prevIndex);
		}
	}
	template <typename T>
	Collider2D* MonsterScript<T>::getSkillActiveCollider()
	{
		switch (curMonsterData.mSkillActiveColliderType[iCurSkillIndex])
		{
		case eColliderFunctionType::Sight:
		{
			return mMonster->GetSightCollider();
		}
		case eColliderFunctionType::Range:
		{
			return mMonster->GetRangeCollider();
		}
		case eColliderFunctionType::HitArea:
		{
			return mMonster->GetHitAreaCollider();
		}
		default:
		{
			return mMonster->GetSightCollider();
		}
		}
	}
	template <typename T>
	void MonsterScript<T>::SpecialAttackAnimation(int skillIndex)
	{
		if (curMonsterData.animationSizes[skillIndex] == Vector2::Zero) return;

		Collider2D* speiclaAttackCollider = getSkillActiveCollider();

		if (speiclaAttackCollider->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
		{
			GetOwner()->SetBattleState(GameObject::Cast);
			mAnimationType = static_cast<MonsterData::eAnimationType>(skillIndex);
			SET_SCALE_XYZ(GetOwner()
				, curMonsterData.animationSizes[skillIndex].x
				, curMonsterData.animationSizes[skillIndex].y
				, 1.f
			);
			if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[skillIndex] + animStrings[mDirection])
			{
				mAnimator->PlayAnimation(curMonsterData.animationString[skillIndex] + animStrings[mDirection]
					, curMonsterData.bSpecialSkillLoop[skillIndex - (int)T::eAnimationType::SpecialCast]);

				if (curMonsterData.animStartIndex[skillIndex] != 0)
					mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[skillIndex]);
			}
		}
	}

	template <typename T>
	void MonsterScript<T>::DeadAnimation()
	{
		if (mMonster->GetBattleState() == GameObject::eBattleState::Dead) return;

		mMonster->SetBattleState(GameObject::eBattleState::ToDead);
		mAnimationType = MonsterData::eAnimationType::ToDead;

		SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x
			, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);

		if (curMonsterData.wsMonsterName.compare(L"디아블로") == 0)
		{
			if (mAnimator->GetActiveAnimation()->GetKey() != wsDiabloDeadAnimationName)
				mAnimator->PlayAnimation(wsDiabloDeadAnimationName, false);
		}
		else
		{
			if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection])
			{
				mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], false);
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
		if (mMonster->GetBattleState() == GameObject::eBattleState::ToDead
			|| mMonster->GetBattleState() == GameObject::eBattleState::Dead) return;

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

		if (mRightHand)
			mRightHand->SetDirection(mDirection);
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
			PlayerManager::player->Hit(5);
		}
	}

	template<typename T>
	void MonsterScript<T>::Hit(bool hit, GameObject::eBattleState state)
	{
		mMonster->SetHit(hit);
		GetOwner()->SetBattleState(state);
	}

    template <typename T>
    void MonsterScript<T>::SetCenterPosY()
    {
		mMonster->SetCenterPosY(50.f);
  //      float offset = curMonsterData.animationCenterPos[(int)mAnimationType].y + (curMonsterData.animationSizes[(int)mAnimationType].y * 3.f);
		//mMonster->SetCenterPosY(offset);
    }

	template<typename T>
	void MonsterScript<T>::makeSkillCastAnimation(int type, int direction)
	{
		std::wstring skillName = curMonsterData.animationString[type] + animStrings[direction];

		mAnimator->StartEvent(curMonsterData.animationString[type] + animStrings[direction])
			= std::make_shared<std::function<void()>>([=]()
		{
			fAttackDelay = 0.f;
			if (curMonsterData.animStartIndex[(UINT)type] != 0)
				mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)type]);
			if (curMonsterData.animProgressStartIndex[(UINT)type] != 0)
				mAnimator->SetAnimationProgressIndex(curMonsterData.animProgressStartIndex[(UINT)type]);
			if (curMonsterData.animEndIndex[(UINT)type] != 0)
				mAnimator->SetAnimationEndIndex(curMonsterData.animEndIndex[(UINT)type]);
		});
		mAnimator->ProgressEvent(curMonsterData.animationString[type] + animStrings[direction])
			= std::make_shared<std::function<void()>>([=]()
		{
			if (skillMake)
			{
				if (nullptr != mSkill)
				{
					if (mSkill->GetSkillFire())
					{
						if (curMonsterData.bSpecialSkillStopInProgress[iCurSkillIndex])
						{
							mMonster->SetBattleState(GameObject::eBattleState::Idle);
							skillMake = false;
						}

					}
				}
				else
				{
					if (curMonsterData.bSpecialSkillStopInProgress[iCurSkillIndex])
					{
						mMonster->SetBattleState(GameObject::eBattleState::Idle);
						skillMake = false;
					}
				}
			}
			else
			{
				iCurSkillIndex = type - (int)MonsterData::eAnimationType::SpecialCast;
				eSkillType skilltype = curMonsterData.mSpecialSkills[iCurSkillIndex];
				if (skilltype != eSkillType::END)
				{
					makeMonsterSkill(skilltype
						, Vector3(GET_POS(GetOwner()).x,
							GET_POS(GetOwner()).y + fSkillCenterPosY,
							GET_POS(GetOwner()).z)
						, eLayerType::MonsterSkill
						, curMonsterData.mSpecialSkillAddFunction[iCurSkillIndex]
						, curMonsterData.mSpecialSkillCount[iCurSkillIndex]
					);
				}
			}
		});
		mAnimator->EndEvent(curMonsterData.animationString[type] + animStrings[direction])
			= std::make_shared<std::function<void()>>([=]()
		{
			int mIndex = type - (int)T::eAnimationType::SpecialCast;
			if (!curMonsterData.bSpecialSkillLoop[mIndex])
			{
				mMonster->SetBattleState(GameObject::eBattleState::Idle);
				skillMake = false;
			}

		});
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
		case m::eSkillFunctionType::MultiFall:
		{
			mSkill = new SkillMultiFire(targetPos, skillType, skillCount, addFunction, fireLayerType, Vector2(200.f, 50.f));
			mSkill->SetCamera(GetOwner()->GetCamera());
			//skill->SkillFire(); 
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		break;
		case m::eSkillFunctionType::LinearStraight:
		case m::eSkillFunctionType::Raidal:
		{
			mSkill = new SkillMultiFire(vector3Pos, skillType, skillCount
				, addFunction, fireLayerType, Vector2::Zero, GetOwner()->GetCamera());
			mSkill->SetCamera(GetOwner()->GetCamera());
			//skill->SkillFire(); 
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		break;
		case m::eSkillFunctionType::MultiFollowerStraight:
		{
			mSkill = new SkillMultiFire(vector3Pos, skillType, skillCount
				, addFunction, fireLayerType, Vector2(0.f, 0.5f), GetOwner()->GetCamera());
			//skill->SkillFire(); 
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		break;
		case m::eSkillFunctionType::MultiStraight:
		{
			mSkill = new SkillMultiFire(vector3Pos, skillType, 6
				, (int)SkillMultiFire::eFireType::RadialRandomStraight, fireLayerType, Vector2(0.f, 0.5f), GetOwner()->GetCamera());
			//skill->SkillFire(); 
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		break;
		case m::eSkillFunctionType::FixedMultiStraight:
		{
			mSkill = new SkillMultiFire(vector3Pos, skillType, 20
				, (int)SkillMultiFire::eFireType::FixedLinear, fireLayerType, Vector2::Zero, GetOwner()->GetCamera(), 0.08f);
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		break;
		case m::eSkillFunctionType::CircleFire:
		{
			mSkill = new SkillMultiFire(vector3Pos, skillType, skillCount, (int)SkillMultiFire::eFireType::Circle, fireLayerType);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		case m::eSkillFunctionType::Buff:
		{
			mSkillBuff = new SkillBuff(GetOwner(), -1, skillType);
			mSkillBuff->SetCamera(GetOwner()->GetCamera());
			mSkillBuff->ActiveOverlay();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkillBuff);
		}
		break;
		case m::eSkillFunctionType::StunAttack:
		{
			mSkill = new SkillAbnormal(skillType, vector3Pos);
			mSkill->SetSkillOwnerLayer(fireLayerType);
			//Collider2D* rangeCol = dynamic_cast<MoveAbleObject*>(GetOwner())->GetRangeCollider();
			dynamic_cast<SkillAbnormal*>(mSkill)->SetAbnormalCollider(getSkillActiveCollider());
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		break;
		case m::eSkillFunctionType::Orb:
		{
			mSkill = new SkillOrb(skillType, vector3Pos, skillSpeed[(int)skillType], fireLayerType);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
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
