#include "mMonsterScript.h"

#include "../engine_source/mMaterial.h"
#include "../engine_source/mAnimator.h"
#include "../engine_source/mAnimation.h"
#include "../engine_source/mTime.h"

#include "mPlayer.h"
#include "mMonster.h"
#include "mPlayerInfo.h"

namespace m
{
	template <typename T>
	MonsterScript<T>::MonsterScript()
		: mDirection(eMonsterDirection::Down)
		, bDamaged(false)
		, fDelay(0.f)
	{
	}
	template <typename T>
	MonsterScript<T>::~MonsterScript()
	{
	}
	template <typename T>
	void MonsterScript<T>::Initialize()
	{
		curMonsterData = T{};
		mAnimator = GET_COMP(GetOwner(), Animator);

		for (int i = 0; i < (UINT)T::eAnimationType::End; ++i)
		{
			SHARED_MAT mat;
			mat = RESOURCE_FIND(Material, curMonsterData.textureString[i]);
			for (int j = 0; j < (UINT)eMonsterDirection::End; ++j)
			{
				mAnimator->Create(
					curMonsterData.animationString[i] + monsterDirectionString[j]
					, mat->GetTexture()
					, Vector2(0.0f, curMonsterData.animationSizes[i].y * j)
					, curMonsterData.animationSizes[i]
					, curMonsterData.animationLength[i]
					, curMonsterData.animationOffset[i]
					, curMonsterData.animationDuration[i]
				);
				if (i == (UINT)T::eAnimationType::Natural)
				{
					mAnimator->StartEvent(curMonsterData.animationString[i] + monsterDirectionString[j])
						= [this]()
					{
						mAnimator->SetAnimationLoopStartIndex(0);
					};
				}
				if (i == (UINT)T::eAnimationType::Attack1)
				{
					mAnimator->StartEvent(curMonsterData.animationString[i] + monsterDirectionString[j])
						= [this]()
					{
						AnimationStart(GameObject::eBattleState::Attack);
						mAnimator->SetAnimationProgressStartIndex(curMonsterData.animProgressStartIndex[(UINT)T::eAnimationType::Attack1]);
					};
					mAnimator->EndEvent(curMonsterData.animationString[i] + monsterDirectionString[j])
						= [this]()
					{
						AnimationComplete(GameObject::eBattleState::Idle);
						mAnimator->SetAnimationProgressStartIndex(0);
					};
					mAnimator->ProgressEvent(curMonsterData.animationString[i] + monsterDirectionString[j])
						= [this]() { AttackProgress(); };
				}
				if (i == (UINT)T::eAnimationType::Hit)
				{
					mAnimator->StartEvent(curMonsterData.animationString[i] + monsterDirectionString[j])
						= [this]()
					{
						Hit(true, GameObject::eBattleState::Hit);
						mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)T::eAnimationType::Hit]);
					};
					mAnimator->EndEvent(curMonsterData.animationString[i] + monsterDirectionString[j])
						= [this]() { Hit(false, GameObject::eBattleState::Idle); };
				}
				if (i == (UINT)T::eAnimationType::Run)
				{
					mAnimator->EndEvent(curMonsterData.animationString[i] + monsterDirectionString[j])
						= [this]()
					{
						mAnimator->SetAnimationLoopStartIndex(0);
						mAnimator->SetAnimationStartIndex(0);
					};
				}
			}
		}
		mDirection = eMonsterDirection::Down;
		mAnimationType = T::eAnimationType::Natural;
		mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + monsterDirectionString[(UINT)mDirection], true);
		SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
	}
	template <typename T>
	void MonsterScript<T>::Update()
	{
		Script::Update();
		if (nullptr == GetMonster())
			return;

		/*if (GetMonster()->GetRangeCollider()->GetOnStay())
		{

		}*/
		if (GetMonster()->GetRangeCollider()->SearchObjectGameObjectId(PlayerInfo::player->GetGameObjectId()))
		{
			fDelay += Time::fDeltaTime();
			if (curMonsterData.fAttackDelay <= fDelay)
			{
				fDelay = 0.f;
				GetOwner()->SetBattleState(GameObject::Attack);
				//int randAttackMotion = rand() % 2 + 1;
				//mAnimationType = randAttackMotion == 1 ? T::eAnimationType::Attack1 : T::eAnimationType::Attack2;
				mAnimationType = T::eAnimationType::Attack1;
				SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
				if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + monsterDirectionString[(UINT)mDirection])
				{
					mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + monsterDirectionString[(UINT)mDirection], false);
				}
			}
		}
		if (GetMonster()->GetHit())
		{
			GetOwner()->SetBattleState(GameObject::Hit);
			mAnimationType = T::eAnimationType::Hit;
			SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
			if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + monsterDirectionString[(UINT)mDirection])
			{
				mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + monsterDirectionString[(UINT)mDirection], false);
			}
		}
		if (
			GetOwner()->GetBattleState() != GameObject::Idle
			&&
			GetOwner()->GetBattleState() != GameObject::Run
			)
			return;

		if (GetMonster()->Stop())
		{
			GetOwner()->SetBattleState(GameObject::Idle);
			mAnimationType = T::eAnimationType::Natural;
		}
		else
		{
			GetOwner()->SetBattleState(GameObject::Run);
			Vector3 initPos = GetMonster()->GetPrevPosition();
			Vector3 destPos = GetMonster()->GetDestPosition();

			Vector3 moveVector = destPos - initPos;

			moveVector.Normalize();

			float degree = RadianToDegree(atan2(moveVector.x, moveVector.y));
			float fDivideDegree = 180.f / 5.f;

			if (degree > -fDivideDegree && degree < fDivideDegree) mDirection = eMonsterDirection::Up;
			else if (degree < -fDivideDegree && degree > -fDivideDegree * 2) mDirection = eMonsterDirection::LeftUp;
			else if (degree < -fDivideDegree * 2 && degree > -fDivideDegree * 3) mDirection = eMonsterDirection::Left;
			else if (degree < -fDivideDegree * 3 && degree > -fDivideDegree * 4) mDirection = eMonsterDirection::LeftDown;
			else if (degree < -fDivideDegree * 4 && degree > -fDivideDegree * 5) mDirection = eMonsterDirection::Down;
			else if (degree <  fDivideDegree * 5 && degree >  fDivideDegree * 4) mDirection = eMonsterDirection::Down;
			else if (degree <  fDivideDegree * 4 && degree >  fDivideDegree * 3) mDirection = eMonsterDirection::RightDown;
			else if (degree <  fDivideDegree * 3 && degree >  fDivideDegree * 2) mDirection = eMonsterDirection::Right;
			else if (degree <  fDivideDegree * 2 && degree >  fDivideDegree) mDirection = eMonsterDirection::RightUp;

			mAnimationType = T::eAnimationType::Run;
		}

		if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + monsterDirectionString[(UINT)mDirection])
		{
			SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);

			WSTRING_SUBSTR(mAnimator->GetActiveAnimation()->GetKey(), L'@', subStr1);

			int prevIndex = 0;
			if (subStr1 == curMonsterData.animationString[(UINT)T::eAnimationType::Run])
				prevIndex = mAnimator->GetAnimationIndex();
			mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + monsterDirectionString[(UINT)mDirection], true);
			if (mAnimationType == T::eAnimationType::Run)
			{
				mAnimator->SetAnimationLoopStartIndex(curMonsterData.animLoopStartIndex[(UINT)mAnimationType]);
				mAnimator->SetAnimationStartIndex(prevIndex);
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

	template<typename T>
	void MonsterScript<T>::AttackProgress()
	{
		if (GetMonster()->GetRangeCollider()->SearchObjectGameObjectId(PlayerInfo::player->GetGameObjectId()))
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
		GetMonster()->SetHit(hit);
		GetOwner()->SetBattleState(state);
	}

}