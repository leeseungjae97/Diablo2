#include "mMonsterScript.h"

#include "../engine_source/mMaterial.h"

#include "mMonster.h"

namespace m
{
	template <typename T>
	MonsterScript<T>::MonsterScript()
		: mDirection(eMonsterDirection::Down)
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
		GET_COMP(GetOwner(), mAnimator, Animator);

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
					, Vector2::Zero
					, 0.1
				);
				if (i == (UINT)T::eAnimationType::Attack1)
				{
					mAnimator->StartEvent(curMonsterData.animationString[i] + monsterDirectionString[j])
						= [this]() { AnimationStart(GameObject::eBattleState::Attack); };
					mAnimator->EndEvent(curMonsterData.animationString[i] + monsterDirectionString[j])
						= [this]() { AnimationComplete(GameObject::eBattleState::Idle); };
				}
				
			}
		}
		mDirection = eMonsterDirection::Down;
		mAnimationType = T::eAnimationType::Natural;
		mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + monsterDirectionString[(UINT)mDirection], true);
	}
	template <typename T>
	void MonsterScript<T>::Update()
	{
		if (nullptr == GetMonster())
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

			if (     degree > -fDivideDegree     && degree < fDivideDegree     ) mDirection = eMonsterDirection::Up;
			else if (degree < -fDivideDegree     && degree > -fDivideDegree * 2) mDirection = eMonsterDirection::LeftUp;
			else if (degree < -fDivideDegree * 2 && degree > -fDivideDegree * 3) mDirection = eMonsterDirection::Left;
			else if (degree < -fDivideDegree * 3 && degree > -fDivideDegree * 4) mDirection = eMonsterDirection::LeftDown;
			else if (degree < -fDivideDegree * 4 && degree > -fDivideDegree * 5) mDirection = eMonsterDirection::Down;
			else if (degree <  fDivideDegree * 5 && degree >  fDivideDegree * 4) mDirection = eMonsterDirection::Down;
			else if (degree <  fDivideDegree * 4 && degree >  fDivideDegree * 3) mDirection = eMonsterDirection::RightDown;
			else if (degree <  fDivideDegree * 3 && degree >  fDivideDegree * 2) mDirection = eMonsterDirection::Right;
			else if (degree <  fDivideDegree * 2 && degree >  fDivideDegree    ) mDirection = eMonsterDirection::RightUp;

			mAnimationType = T::eAnimationType::Run;
		}

		if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + monsterDirectionString[(UINT)mDirection])
		{
			SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
			int prevIndex = mAnimator->GetAnimationIndex();
			mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + monsterDirectionString[(UINT)mDirection], true);
			if (mAnimationType == T::eAnimationType::Run)
				mAnimator->SetAnimationIndex(prevIndex);
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
		GetOwner()->SetBattleState(state);
	}
	template <typename T>
	void MonsterScript<T>::AnimationComplete(GameObject::eBattleState state)
	{
		GetOwner()->SetBattleState(state);
	}

}