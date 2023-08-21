#include "mMonsterScript.h"

#include "../engine_source/mSceneManager.h"
#include "../engine_source/mMaterial.h"
#include "../engine_source/mAnimator.h"
#include "../engine_source/mAnimation.h"
#include "../engine_source/mTime.h"

#include "mPlayer.h"
#include "mMonster.h"
#include "mPlayerInfo.h"

#include "mSkillMultiFire.h"

namespace m
{
	template <typename T>
	MonsterScript<T>::MonsterScript()
		: mAnimator(nullptr)
		, mSkill(nullptr)
		, mMonster(nullptr)
		, mClass(eMonsterClass::Normal)
		, bFire(false)
		, bDamaged(false)
		, fDelay(0.f)
		, mDirection(0)
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
		mLeftHand = new MonsterHand(GetOwner(), curMonsterData.mMonsterType);
		mRightHand = new MonsterHand(GetOwner(), curMonsterData.mMonsterType);

		int m = 0;
		for (int i = 0; i < (UINT)T::eAnimationType::End; ++i)
		{
			if (curMonsterData.textureString[i] == L"") continue;

			SHARED_MAT mat = RESOURCE_FIND(Material, curMonsterData.textureString[i]);
			
			for (int j = 0; j < 8; ++j)
			{
				if (curMonsterData.bPathImage) m = pathEightDirections[j];
				else m = eEightDirection[j];
				mAnimator->Create(
					curMonsterData.animationString[i] + sixteenDirectionString[m]
					, mat->GetTexture()
					, Vector2(0.0f, curMonsterData.animationSizes[i].y * j)
					, curMonsterData.animationSizes[i]
					, curMonsterData.animationLength[i]
					, curMonsterData.animationOffset[i]
					, curMonsterData.animationDuration[i]
				);
				if (i == (UINT)T::eAnimationType::Natural)
				{
					mAnimator->StartEvent(curMonsterData.animationString[i] + sixteenDirectionString[m])
						= [this]()
					{
						mAnimator->SetAnimationStartIndex(0);
					};
				}
				if (i == (UINT)T::eAnimationType::Attack1)
				{
					mAnimator->StartEvent(curMonsterData.animationString[i] + sixteenDirectionString[m])
						= [this]()
					{
						AnimationStart(GameObject::eBattleState::Attack);
						mAnimator->SetAnimationProgressIndex(curMonsterData.animProgressStartIndex[(UINT)T::eAnimationType::Attack1]);
					};
					mAnimator->EndEvent(curMonsterData.animationString[i] + sixteenDirectionString[m])
						= [this]()
					{
						fDelay = 0.f;
						AnimationComplete(GameObject::eBattleState::Idle);
						mAnimator->SetAnimationProgressIndex(0);
					};
					mAnimator->ProgressEvent(curMonsterData.animationString[i] + sixteenDirectionString[m])
						= [this]() { AttackProgress(); };
				}
				if (i == (UINT)T::eAnimationType::Hit)
				{
					mAnimator->StartEvent(curMonsterData.animationString[i] + sixteenDirectionString[m])
						= [this]()
					{
						Hit(true, GameObject::eBattleState::Hit);
						mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)T::eAnimationType::Hit]);
					};
					mAnimator->EndEvent(curMonsterData.animationString[i] + sixteenDirectionString[m])
						= [this]() { Hit(false, GameObject::eBattleState::Idle); };
				}
				if (i == (UINT)T::eAnimationType::SpecialCast)
				{
					mAnimator->StartEvent(curMonsterData.animationString[i] + sixteenDirectionString[m])
						= [this]()
					{
						mAnimator->SetAnimationProgressIndex(curMonsterData.animProgressStartIndex[(UINT)T::eAnimationType::SpecialCast]);
						mAnimator->SetAnimationEndIndex(curMonsterData.animEndIndex[(UINT)T::eAnimationType::SpecialCast]);
						//mAnimator->SetAnimationProgressStartIndex(curMonsterData.animProgressStartIndex[i]);
					};
					mAnimator->ProgressEvent(curMonsterData.animationString[i] + sixteenDirectionString[m])
						= [this]()
					{
						//Skill* st = new SkillStraight(curMonsterData.mSpecialCastSkillType, GET_POS(GetOwner()), 300.f);
						//ADD_COMP(st, StraightScript);
						//st->SetCamera(GetOwner()->GetCamera());
						//st->SetSkillOwnerLayer(GetOwner()->GetLayerType());
						//st->SkillFire();
						//SceneManager::GetActiveScene()->AddGameObject(eLayerType::Skill, st);
						if (nullptr == mSkill
							|| mSkill->GetSkillFire()) GetOwner()->SetBattleState(GameObject::eBattleState::Idle);
					};
					mAnimator->EndEvent(curMonsterData.animationString[i] + sixteenDirectionString[m])
						= [this]()
					{
						if (nullptr == mSkill
							|| mSkill->GetSkillFire()) GetOwner()->SetBattleState(GameObject::eBattleState::Idle);
					};
				}
			}
		}
		mAnimationType = T::eAnimationType::Natural;
		mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + sixteenDirectionString[mDirection], true);
		SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);

		mMonster = static_cast<Monster*>(GetOwner());

		if (curMonsterData.bPathImage) mPlusDirections = plusPathEightDirections;
		else mPlusDirections = plusEightDirection;
		if (curMonsterData.bPathImage) mMinusDirections = minusPathEightDirections;
		else mMinusDirections = minusEightDirection;
	}
	template <typename T>
	void MonsterScript<T>::Update()
	{
		Script::Update();
		if (nullptr == mMonster)
			return;

		Vector3 initPos = mMonster->GetPrevPosition();
		Vector3 destPos = mMonster->GetDestPosition();

		Vector3 moveVector = destPos - initPos;

		moveVector.Normalize();

		float degree = RadianToDegree(atan2(moveVector.x, moveVector.y));


		int n = degree / (180.f / 5.f);

		if (n > 0)
			mDirection = mPlusDirections[n];
		else
			mDirection = mMinusDirections[abs(n)];

		mLeftHand->SetDirection((int)mDirection);
		mRightHand->SetDirection((int)mDirection);
		/*	if (degree > -fDivideDegree && degree < fDivideDegree) mDirection =   eEightDirection::Up;
			else if (degree < -fDivideDegree && degree > -fDivideDegree * 2) mDirection = eEightDirection::LeftUp;
		else if (degree < -fDivideDegree * 2 && degree > -fDivideDegree * 3) mDirection = eEightDirection::Left;
		else if (degree < -fDivideDegree * 3 && degree > -fDivideDegree * 4) mDirection = eEightDirection::LeftDown;
		else if (degree < -fDivideDegree * 4 && degree > -fDivideDegree * 5) mDirection = eEightDirection::Down;
		else if (degree <  fDivideDegree * 5 && degree >  fDivideDegree * 4) mDirection = eEightDirection::Down;
		else if (degree <  fDivideDegree * 4 && degree >  fDivideDegree * 3) mDirection = eEightDirection::RightDown;
		else if (degree <  fDivideDegree * 3 && degree >  fDivideDegree * 2) mDirection = eEightDirection::Right;
			else if (degree <  fDivideDegree * 2 && degree >  fDivideDegree) mDirection = eEightDirection::RightUp;*/

		if (mMonster->GetBattleState() == GameObject::eBattleState::Idle
			|| mMonster->GetBattleState() == GameObject::eBattleState::Run)
		{
			//if (rand() % 100 == 7)
			//{
			//	//if (mMonster ->GetSightCollider()->GetOnEnter()
			//	//	|| mMonster ->GetSightCollider()->GetOnStay()
			//	//	&& mMonster ->GetSightCollider()->SearchObjectGameObjectId(PlayerInfo::player->GetGameObjectId()))
			//	if (mMonster->GetSightCollider()->SearchObjectGameObjectId(PlayerInfo::player->GetGameObjectId()))
			//	{
			//		GetOwner()->SetBattleState(GameObject::Cast);
			//		mAnimationType = T::eAnimationType::SpecialCast;
			//		SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
			//		if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + eightDirectionString[(UINT)mDirection])
			//		{
			//			if (curMonsterData.mMonsterType == eMonsterType::Diablo)
			//			{
			//				mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + eightDirectionString[(UINT)mDirection], true);
			//				mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)T::eAnimationType::SpecialCast]);

			//				mSkill = new SkillMultiFire(curMonsterData.mSpecialCastSkillType, GET_POS(GetOwner()), curMonsterData.mSpecialCastSkillCount, SkillMultiFire::eFireType::Linear);
			//				mSkill->SetCamera(GetOwner()->GetCamera());
			//				mSkill->SetSkillOwnerLayer(eLayerType::MonsterSkill);
			//				SceneManager::GetActiveScene()->AddGameObject(eLayerType::Skill, mSkill);
			//			}
			//		}
			//	}
			//}
		}
		if (mMonster->GetBattleState() == GameObject::eBattleState::Cast
			&& curMonsterData.textureString[(UINT)T::eAnimationType::SpecialCast] != L"")
		{
			WSTRING_SUBSTR(mAnimator->GetActiveAnimation()->GetKey(), L'@', subStr1);
			int prevIndex = 0;
			if (subStr1 == curMonsterData.animationString[(UINT)T::eAnimationType::SpecialCast])
			{
				prevIndex = mAnimator->GetAnimationIndex();
			}
			mAnimationType = T::eAnimationType::SpecialCast;
			SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
			if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + sixteenDirectionString[mDirection])
			{
				mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + sixteenDirectionString[mDirection], true);
				mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)T::eAnimationType::SpecialCast]);
				mAnimator->SetAnimationIndex(prevIndex);
			}
		}
		if (mMonster->GetRangeCollider()->GetOnEnter()
			|| mMonster->GetRangeCollider()->GetOnStay()
			&& mMonster->GetRangeCollider()->SearchObjectGameObjectId(PlayerInfo::player->GetGameObjectId()))
		{
			fDelay += Time::fDeltaTime();
			if (curMonsterData.fAttackDelay <= fDelay)
			{
				//int randAttackMotion = rand() % 2 + 1;
				//mAnimationType = randAttackMotion == 1 ? T::eAnimationType::Attack1 : T::eAnimationType::Attack2;
				GetOwner()->SetBattleState(GameObject::Attack);
				mAnimationType = T::eAnimationType::Attack1;
				SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
				if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + sixteenDirectionString[mDirection])
				{
					mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + sixteenDirectionString[mDirection], false);
				}
			}

		}
		//if (mMonster ->GetHit())
		//{
			//GetOwner()->SetBattleState(GameObject::Hit);
			//mAnimationType = T::eAnimationType::Hit;
			//SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
			//if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + eightDirectionString[(UINT)mDirection])
			//{
			//	mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + eightDirectionString[(UINT)mDirection], false);
			//}
		//}
		if (
			GetOwner()->GetBattleState() != GameObject::Idle
			&&
			GetOwner()->GetBattleState() != GameObject::Run
			)
			return;

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

		if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + sixteenDirectionString[mDirection]
			&& curMonsterData.textureString[(UINT)mAnimationType] != L"")
		{

			SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);

			WSTRING_SUBSTR(mAnimator->GetActiveAnimation()->GetKey(), L'@', subStr1);

			int prevIndex = 0;
			if (subStr1 == curMonsterData.animationString[(UINT)T::eAnimationType::Run])
			{
				prevIndex = mAnimator->GetAnimationIndex();
			}

			mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + sixteenDirectionString[mDirection], true);
			if (mAnimationType == T::eAnimationType::Run)
			{
				mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)mAnimationType]);
				mAnimator->SetAnimationIndex(prevIndex);
			}
		}
		mLeftHand->SetAniType((int)mAnimationType);
		mRightHand->SetAniType((int)mAnimationType);
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
	void MonsterScript<T>::AnimationStart(GameObject::eBattleState state)
	{
		bDamaged = false;
		GetOwner()->SetBattleState(state);
	}
	template <typename T>
	void MonsterScript<T>::AnimationComplete(GameObject::eBattleState state)
	{
		bDamaged = false;
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
		if (mMonster->GetRangeCollider()->SearchObjectGameObjectId(PlayerInfo::player->GetGameObjectId()))
		{
			if (!bDamaged)
			{
				PlayerInfo::player->Hit(10);
				bDamaged = true;
			}
		}
	}

	template<typename T>
	void MonsterScript<T>::Hit(bool hit, GameObject::eBattleState state)
	{
		mMonster->SetHit(hit);
		GetOwner()->SetBattleState(state);
	}

}