#include "mAuraScript.h"

#include "mMaterial.h"
#include "mMonster.h"
#include "mMouseManager.h"
#include "mMoveAbleObject.h"
#include "mOverlayEffectSkillScript.h"
#include "mPlayer.h"
#include "mSceneManager.h"
#include "mSkillFall.h"
#include "mTime.h"

namespace m
{
	AuraScript::AuraScript(eAuraType type, float auraDuration, eLayerType layerType)
		: mAuraType(type)
		, mDuration(auraDuration)
		, fAcc(0.f)
		, fCollideAcc(0.f)
	    , bAuraActive(false)
	    , mFireSkillLayer(layerType)
	    , bStartCastAnim(false)
	{
	}

	AuraScript::~AuraScript()
	{
	}

	void AuraScript::Initialize()
	{
		Script::Initialize();
		mAnimator = GET_COMP(GetOwner(), Animator);
		SHARED_MAT mat = RESOURCE_FIND(Material, auraNames[(int)mAuraType]);

		if (nullptr != mat)
		{
			SET_SCALE_XYZ(GetOwner(), auraSizes[(int)mAuraType].x
				, auraSizes[(int)mAuraType].y, 1.f);
			mAnimator->Create(
				auraNames[(int)mAuraType] + L"anim"
				, mat->GetTexture()
				, Vector2::Zero
				, auraSizes[(int)mAuraType]
				, auraLength[(int)mAuraType]
				, Vector2::Zero
				, auraCenterPos[(int)mAuraType]
				, 0.03f
			);
		}

		SHARED_MAT noneMat = RESOURCE_FIND(Material, L"noneRect");
		mAnimator->Create(
			L"noneRectAnim"
			, noneMat->GetTexture()
			, Vector2::Zero
			, Vector2(20.f, 20.f)
			, 1
			, Vector2::Zero
			, 0.03f
		);
		mAnimator->PlayAnimation(L"noneRectAnim", true);
	}

	void AuraScript::Update()
	{
		Script::Update();
		if(bAuraActive && mAuraType != eAuraType::End)
		{
			if(bStartCastAnim)
			{
				if (mAnimator->GetActiveAnimation()->GetKey() != auraStartNames[(int)mAuraType] + L"anim")
				{
					SET_SCALE_XYZ(GetOwner(), auraStartSizes[(int)mAuraType].x
						, auraStartSizes[(int)mAuraType].y, 1.f);
					mAnimator->PlayAnimation(auraStartNames[(int)mAuraType] + L"anim", false);
				}
				
			}else
			{
				if (mAnimator->GetActiveAnimation()->GetKey() != auraNames[(int)mAuraType] + L"anim")
				{
					SET_SCALE_XYZ(GetOwner(), auraSizes[(int)mAuraType].x
						, auraSizes[(int)mAuraType].y, 1.f);
					mAnimator->PlayAnimation(auraNames[(int)mAuraType] + L"anim", true);
				}
			}
			

			fAcc += Time::fDeltaTime();
			fCollideAcc += Time::fDeltaTime();
			if (mDuration > 0)
			{
				if (mDuration <= fAcc)
				{
					mAnimator->PlayAnimation(L"noneRectAnim", true);
					bAuraActive = false;
				}
			}
			colliderCollided();
		}	
	}

	void AuraScript::LateUpdate()
	{
		Script::LateUpdate();
	}


	void AuraScript::Render()
	{
		Script::Render();
	}

    void AuraScript::SetAura(eAuraType type, float auraDuration, eLayerType layerType)
    {
		fAcc = 0.f;
		mAuraType = type;
		mDuration = auraDuration;
		mFireSkillLayer = layerType;
		bAuraActive = false;
		fAuraValue = auraFunctionValue[(int)type][0];
		mAnimator->PlayAnimation(L"noneRectAnim", true);

		SHARED_MAT mat = RESOURCE_FIND(Material, auraNames[(int)mAuraType]);
		
		if (nullptr == mat) return;

		mAnimator->Create(
			auraNames[(int)mAuraType] + L"anim"
			, mat->GetTexture()
			, Vector2::Zero
			, auraSizes[(int)mAuraType]
			, auraLength[(int)mAuraType]
			, Vector2::Zero
			, auraCenterPos[(int)mAuraType]
			, 0.03f
		);

		SHARED_MAT startMat = RESOURCE_FIND(Material, auraStartNames[(int)mAuraType]);

		if (nullptr == startMat)
		{
			bStartCastAnim = false;
			return;
		}

		bStartCastAnim = true;
		mAnimator->Create(
			auraStartNames[(int)mAuraType] + L"anim"
			, startMat->GetTexture()
			, Vector2::Zero
			, auraStartSizes[(int)mAuraType]
			, auraStartLength[(int)mAuraType]
			, Vector2::Zero
			, auraStartCenterPos[(int)mAuraType]
			, 0.03f
		);
		mAnimator->EndEvent(auraStartNames[(int)mAuraType] + L"anim") = [=]()
		{
			bStartCastAnim = false;
		};
    }

	void AuraScript::colliderCollided()
	{
		eAuraFunctionType fType = auraFunction[(int)mAuraType];
		if (fType == eAuraFunctionType::End) return;

		float fAuraFunctionValue1 = auraFunctionValue[(int)fType][0];
		float fAuraFunctionValue2 = auraFunctionValue[(int)fType][1];

		bool coliidePlayer = false;
		if (mCol->GetOnEnter()
			|| mCol->GetOnStay())
		{
			Monster* m = dynamic_cast<Monster*>(mAuraOwner);
			if (m)
			{
				if (mCol->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
				{
					coliidePlayer = true;
				}
			}
			else coliidePlayer = false;

			switch (fType)
			{
			case eAuraFunctionType::Slow:
			{
				if (coliidePlayer)
					PlayerManager::player->SetNumericalAdjustmentSpeed(fAuraFunctionValue1
						, fAuraFunctionValue2);
				else
				{

				}
			}
			case eAuraFunctionType::TargetDamage:
			{

				if(fCollideAcc >= fAuraValue)
				{
					fCollideAcc = 0.f;
					targetDamage();
				}
				

				//if (coliidePlayer)
				//{
				//	PlayerManager::player->Hit(10);
				//}
				//else
				//{
				//	m->Hit(10);
				//}
			}
			break;
			default:
			{

			}
			break;
			}
		}
	}
	void AuraScript::targetDamage()
	{
		if (mCol->GetCollidereds().empty()) return;

		for (Collider2D* col : mCol->GetCollidereds())
		{
			if (col->GetColliderFunctionType() != eColliderFunctionType::HitArea) continue;

			Monster* monster = dynamic_cast<Monster*>(col->GetOwner());

			if (monster)
			{
				eSkillType skillType = auraAddSkill[(int)mAuraType];
				Vector3 pos = GET_POS(monster);
				pos.y += 300.f;

				SkillFall* skill = new SkillFall(skillType
					, pos
					, 300.f
					, false
					, false
					, eAccessorySkillType::END, monster
				);

				skill->SetCamera(GetOwner()->GetCamera());
				skill->SkillFire();
				SceneManager::GetActiveScene()->AddGameObject(mFireSkillLayer, skill);

				return;
			}
		}
	}
}
