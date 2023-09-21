#include "mSummonsScript.h"

#include "mMonster.h"
#include "../engine_source/MoveAbleObjectAnimLookUpTables.h"
#include "../engine_source/mMaterial.h"
#include "../engine_source/mSceneManager.h"

#include "mMoveAbleObject.h"
#include "mOverlay.h"
#include "mSkill.h"
#include "mSkillStraight.h"

namespace m
{
	template <typename T>
	SummonsScript<T>::SummonsScript(float summonTime)
		: mAnimationType(SummonsData::eSummonsAnimationType::Natural)
		, mAnimator(nullptr)
		, mDirection(0)
		, fSummonTime(summonTime)
		, mSkill(nullptr)
		, skillMake(false)
		, fAttackDelay(2.f)
		, fAttackAcc(0.f)
	{
	}

	template <typename T>
	SummonsScript<T>::~SummonsScript()
	{
	}
	template <typename T>
	void SummonsScript<T>::Initialize()
	{
		Script::Initialize();
		MoveAbleObject* owner = dynamic_cast<MoveAbleObject*>(GetOwner());
		owner->GetRangeCollider()->SetScale(Vector3(curSummonsData.attackRange.x, curSummonsData.attackRange.y, 1.f));

		mAnimator = GET_COMP(GetOwner(), Animator);
		for (int i = 0; i < (int)SummonsData::eSummonsAnimationType::End; ++i)
		{
			if (curSummonsData.summonMaterialString[i] == L"") continue;

			SHARED_MAT mat = RESOURCE_FIND(Material, curSummonsData.summonMaterialString[i]);
			for (int j = 0; j < 8; ++j)
			{
				mAnimator->Create(
					curSummonsData.summonMaterialString[i] + pathSixteenDirectionString[j]
					, mat->GetTexture()
					, Vector2(0.f, curSummonsData.summonsSize[i].y * j)
					, curSummonsData.summonsSize[i]
					, curSummonsData.summonsAnimLength[i]
					, curSummonsData.summonsOffset[i]
					, curSummonsData.summonsAnimDuration[i]
				);
				if (i == (UINT)SummonsData::eSummonsAnimationType::Summon)
				{
					mAnimator->EndEvent(curSummonsData.summonMaterialString[i] + pathSixteenDirectionString[j]) = [=]()
					{
						GetOwner()->SetBattleState(GameObject::eBattleState::Idle);
					};
				}
				if (i == (UINT)SummonsData::eSummonsAnimationType::Attack)
				{
					mAnimator->StartEvent(curSummonsData.summonMaterialString[i] + pathSixteenDirectionString[j]) = [=]()
					{
						if (curSummonsData.summonsProgIndex[i] != 0)
							mAnimator->SetAnimationProgressIndex(curSummonsData.summonsProgIndex[i]);

					};
					mAnimator->ProgressEvent(curSummonsData.summonMaterialString[i] + pathSixteenDirectionString[j]) = [=]()
					{
						if (skillMake)
						{
							//if(nullptr != mSkill)
							//{
							//	GetOwner()->SetBattleState(GameObject::eBattleState::Idle);
							//	skillMake = false;
							//}else
							//{
							//	GetOwner()->SetBattleState(GameObject::eBattleState::Idle);
							//	skillMake = false;
							//}
						}
						else
						{
							makeSkill(curSummonsData.summonSkill, GET_POS(GetOwner()), eLayerType::PlayerSkill);
						}
					};
					mAnimator->EndEvent(curSummonsData.summonMaterialString[i] + pathSixteenDirectionString[j]) = [=]()
					{
						GetOwner()->SetBattleState(GameObject::eBattleState::Idle);
						skillMake = false;
					};
				}
				if (i == (UINT)SummonsData::eSummonsAnimationType::Dead)
				{
					mAnimator->EndEvent(curSummonsData.summonMaterialString[i] + pathSixteenDirectionString[j]) = [=]()
					{
						GetOwner()->SetState(GameObject::Delete);
						mOL1->SetState(GameObject::Delete);
						mOL2->SetState(GameObject::Delete);
					};
				}
			}
		}
		makeDirection();

		GetOwner()->SetBattleState(GameObject::eBattleState::Cast);
		mAnimationType = SummonsData::eSummonsAnimationType::Summon;

		SET_SCALE_XYZ(GetOwner(), curSummonsData.summonsSize[(UINT)mAnimationType].x
			, curSummonsData.summonsSize[(UINT)mAnimationType].y, 1.f);

		mAnimator->PlayAnimation(curSummonsData.summonMaterialString[(int)mAnimationType] + pathSixteenDirectionString[mDirection], false);
		mOL2 = new Overlay(curSummonsData.overlay2MaterialString[(int)mAnimationType],
			GET_POS(GetOwner()),
			curSummonsData.overlay2Size[(int)mAnimationType],
			curSummonsData.overlay2Offset[(int)mAnimationType],
			curSummonsData.overlay2CenterPos[(int)mAnimationType],
			curSummonsData.overlay2AnimLength[(int)mAnimationType],
			curSummonsData.overlay2AnimDuration[(int)mAnimationType],
			false
		);

		mOL1 = new Overlay(curSummonsData.overlayMaterialString[(int)mAnimationType],
			GET_POS(GetOwner()),
			curSummonsData.overlaySize[(int)mAnimationType],
			curSummonsData.overlayOffset[(int)mAnimationType],
			curSummonsData.overlayCenterPos[(int)mAnimationType],
			curSummonsData.overlayAnimLength[(int)mAnimationType],
			curSummonsData.overlayAnimDuration[(int)mAnimationType],
			false
		);

		mOL1->SetDirection(mDirection);
		mOL1->SetSyncPlay(mAnimator);

		mOL2->SetDirection(-1);
		mOL2->OverDraw();

		mOL1->SetMoveAbleObject(dynamic_cast<MoveAbleObject*>(GetOwner()));
		mOL2->SetMoveAbleObject(dynamic_cast<MoveAbleObject*>(GetOwner()));

		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Summons, mOL1);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Summons, mOL2);
	}
	template <typename T>
	void SummonsScript<T>::Update()
	{
		Script::Update();
		if (nullptr == mOL1->GetCamera())
			mOL1->SetCamera(GetOwner()->GetCamera());
		if (nullptr == mOL2->GetCamera())
			mOL2->SetCamera(GetOwner()->GetCamera());

		fSummonTime -= Time::fDeltaTime();
		if (fSummonTime <= 0.f)
		{
			GetOwner()->SetBattleState(GameObject::eBattleState::Dead);
		}


		if (GetOwner()->GetBattleState() != GameObject::eBattleState::Cast)
		{
			makeDirection();
			checkAttack();
		}
		if (GetOwner()->GetBattleState() == GameObject::eBattleState::Idle)
		{
			mAnimationType = SummonsData::eSummonsAnimationType::Natural;
		}
		if (GetOwner()->GetBattleState() == GameObject::eBattleState::Attack)
		{
			mAnimationType = SummonsData::eSummonsAnimationType::Attack;
		}
		if (GetOwner()->GetBattleState() == GameObject::eBattleState::Dead)
		{
			mAnimationType = SummonsData::eSummonsAnimationType::Dead;
		}
		if (nullptr == mAnimator->GetActiveAnimation() ||
			mAnimator->GetActiveAnimation()->GetKey() != curSummonsData.summonMaterialString[(int)mAnimationType] + pathSixteenDirectionString[mDirection])
		{
			SET_SCALE_XYZ(GetOwner(), curSummonsData.summonsSize[(UINT)mAnimationType].x
				, curSummonsData.summonsSize[(UINT)mAnimationType].y, 1.f);
			bool loop = false;
			if (mAnimationType == SummonsData::eSummonsAnimationType::Natural) loop = true;

			mOL2->MakeOverlay(curSummonsData.overlay2MaterialString[(int)mAnimationType],
				curSummonsData.overlay2Size[(int)mAnimationType],
				curSummonsData.overlay2Offset[(int)mAnimationType],
				curSummonsData.overlay2CenterPos[(int)mAnimationType],
				curSummonsData.overlay2AnimLength[(int)mAnimationType],
				curSummonsData.overlay2AnimDuration[(int)mAnimationType],
				loop
			);

			mOL1->MakeOverlay(curSummonsData.overlayMaterialString[(int)mAnimationType],
				curSummonsData.overlaySize[(int)mAnimationType],
				curSummonsData.overlayOffset[(int)mAnimationType],
				curSummonsData.overlayCenterPos[(int)mAnimationType],
				curSummonsData.overlayAnimLength[(int)mAnimationType],
				curSummonsData.overlayAnimDuration[(int)mAnimationType],
				loop
			);
			mAnimator->PlayAnimation(
				curSummonsData.summonMaterialString[(int)mAnimationType] + pathSixteenDirectionString[mDirection]
				, loop
			);
		}

	}
	template <typename T>
	void SummonsScript<T>::makeDirection()
	{
		Vector3 direction = dynamic_cast<MoveAbleObject*>(GetOwner())->GetDirection();

		float degree = RadianToDegree(atan2(direction.x, direction.y));

		int n = degree / (180.f / 5.f);
		if (n > 4) n = 4;

		if (n > 0)
			mDirection = pathPlusEightDirections[n];
		else
			mDirection = pathMinusEightDirections[abs(n)];

		if (mOL1)
			mOL1->SetDirection(mDirection);
	}

	template <typename T>
	void SummonsScript<T>::checkAttack()
	{
		MoveAbleObject* owner = dynamic_cast<MoveAbleObject*>(GetOwner());
		Monster* monster = owner->GetRangeCollider()->SearchCollideredMonster();
		if (monster)
		{
			fAttackAcc -= Time::fDeltaTime();
			if (fAttackAcc <= 0.f)
			{
				GetOwner()->SetBattleState(GameObject::eBattleState::Attack);
				fAttackAcc = fAttackDelay;
			}

		}
	}

	template <typename T>
	void SummonsScript<T>::LateUpdate()
	{
		Script::LateUpdate();
	}
	template <typename T>
	void SummonsScript<T>::Render()
	{
		Script::Render();
	}

	template <typename T>
	void SummonsScript<T>::makeSkill(eSkillType skillType, Vector3 initPos, eLayerType fireLayerType)
	{
		MoveAbleObject* owner = dynamic_cast<MoveAbleObject*>(GetOwner());
		Monster* monster = owner->GetRangeCollider()->SearchCollideredMonster();
		if (nullptr == monster) return;

		Vector3 targetPos = GET_POS(monster);
		switch (skillFunctionTypes[(int)skillType])
		{
		case m::eSkillFunctionType::Straight:
		{
			mSkill = new SkillStraight(skillType, initPos, skillSpeed[(int)skillType]);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SetDestPosition(targetPos);
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		break;
		default:
		{
			mSkill = new Skill(skillType, initPos);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		break;
		}

		if (nullptr != mSkill)
		{
			skillMake = true;
		}
	}
}
