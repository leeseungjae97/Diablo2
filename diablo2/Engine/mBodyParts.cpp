#include "mBodyParts.h"

#include "ItemLookUpTables.h"
#include "mShadowObject.h"

#include "../engine_source/mStashManager.h"
#include "../engine_source/mSceneManager.h"

namespace m
{
	BodyParts::BodyParts(eBodyPartsType type, GameObject* _mPartsOwner)
		: mBodyPartsType(type)
		, mPartsOwner(_mPartsOwner)
		, mAnimator(nullptr)
		, mDirection(0)
		, mAnimationType(0)
	    , iCurItem(0)
	    , iPrevItem(0)
	{
		SetCamera(_mPartsOwner->GetCamera());

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");

		mAnimator = GET_COMP(this, Animator);
		Animator* ownerAnimator = GET_COMP(_mPartsOwner, Animator);

		mAnimator->SetSyncAnimator(ownerAnimator);

		int initCount = 0;
		for (int i = 0; i < (int)ePlayerAnimationType::End; ++i)
		{
			std::wstring materialName = partsMaterialNames[(int)type][i];
			Vector2 size = partsSizes[(int)type][i];
			int len = partsLength[i];
			float durtion = partsDuration[i];
			//Vector2 centerPos = partsCenterPos[(int)type][i];
			if (materialName == L"") continue;

			++initCount;

			SHARED_MAT mat = RESOURCE_FIND(Material, materialName);

			for (int j = 0; j < (UINT)eSixteenDirection::End; ++j)
			{
				mAnimator->Create(
					materialName + L"@" + pathSixteenDirectionString[j],
					mat->GetTexture(),
					Vector2(0, size.y * j),
					size,
					len,
					Vector2::Zero,
					Vector2::Zero,
					durtion
				);
			}
		}

		mDirection = (int)ePathSixteenDirection::Down;
		mAnimationType = (int)ePlayerAnimationType::Natural;

		if (initCount == 0)
		{
			SHARED_MAT noneMat = RESOURCE_FIND(Material, L"noneRect");
			mAnimator->Create(
				L"noneRectAnim"
				, noneMat->GetTexture()
				, Vector2::Zero
				, Vector2(20.f, 20.f)
				, 1
				, Vector2::Zero
				, Vector2::Zero
				, 0.03f
			);
			SET_SCALE_XYZ(this, 20.f, 20.f, 1.f);
			mAnimator->PlayAnimation(L"noneRectAnim", true);
			mAnimator->DeSync();
		}
		else
		{
			Vector2 scale = partsSizes[(int)type][mAnimationType];
			SET_SCALE_XYZ(this, scale.x, scale.y, 1.f);
			mAnimator->PlayAnimation(partsMaterialNames[(int)mBodyPartsType][mAnimationType] + L"@" + pathSixteenDirectionString[mDirection], true);
			mAnimator->Sync();
		}
		
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Object, this);

		mShadow = new ShadowObject(this);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Shadow, mShadow);

		wsCurNames = partsMaterialNames[(int)mBodyPartsType];
		vCurSizes = partsSizes[(int)mBodyPartsType];
		vPartsOffset = bodyPartsOffset[(int)mBodyPartsType];
	}
	BodyParts::~BodyParts()
	{
	}

	void BodyParts::Initialize()
	{
		GameObject::Initialize();
	}

	void BodyParts::Update()
	{
		GameObject::Update();
		if (mShadow && nullptr == mShadow->GetCamera()) mShadow->SetCamera(GetCamera());
		imageChangeEquiment();
		shadowOffset();
		partAddZWeight();

		if(wsCurNames[mAnimationType] != L"")
		{
			std::wstring animtionName = wsCurNames[mAnimationType] + L"@" + pathSixteenDirectionString[mDirection];

			if (mAnimator->GetActiveAnimation()->GetKey() != animtionName)
			{
				Vector2 scale = vCurSizes[mAnimationType];
				SET_SCALE_XYZ(this, scale.x, scale.y, 1.f);

				mAnimator->PlayAnimation(animtionName, true);
			}
		}
	}

	void BodyParts::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void BodyParts::Render()
	{
		GameObject::Render();
	}
    void BodyParts::imageChangeEquiment()
    {
		iPrevItem = iCurItem;
		switch (mBodyPartsType)
		{
		case eBodyPartsType::Body:
		{
			iCurItem = StashManager::GetArmorItem();
		}
		break;
		case eBodyPartsType::Head:
		{
			iCurItem = StashManager::GetHelmetItem();
		}
		break;
		case eBodyPartsType::LeftArm:
		{
			iCurItem = StashManager::GetLeftWeaponItem();
		}
		break;
		case eBodyPartsType::RightArm:
		{
			iCurItem = StashManager::GetRightWeaponItem();
		}
		break;
		case eBodyPartsType::Leg:
		{
			iCurItem = StashManager::GetShoesItem();
		}
		break;
		case eBodyPartsType::RightHand:
		{
			iCurItem = StashManager::GetRightWeaponItem();
		}
		break;
		default:
		{
			iCurItem = 0;
		}
		break;
		}

		if(iPrevItem != iCurItem)
		    changeAnimation();
    }

    void BodyParts::changeAnimation()
    {
		if(iCurItem == 0 )
		{
			wsCurNames = partsMaterialNames[(int)mBodyPartsType];
			vCurSizes = partsSizes[(int)mBodyPartsType];
			vPartsOffset = bodyPartsOffset[(int)mBodyPartsType];
			if(mBodyPartsType == eBodyPartsType::RightHand)
			{
				mAnimator->PlayAnimation(L"noneRectAnim", true);
				mAnimator->DeSync();
			}
		}
		else
		{
			wsCurNames = itemBodyPartMaterialNames[iCurItem][(int)mBodyPartsType];
			vCurSizes = itemBodyPartSizes[iCurItem][(int)mBodyPartsType];
			vPartsOffset = itemAnimCenterPos[iCurItem][(int)mBodyPartsType];

			for (int i = 0; i < (int)ePlayerAnimationType::End; ++i)
			{
				std::wstring materialName = wsCurNames[i];
				Vector2 size = vCurSizes[i];

				int len = partsLength[i];
				float durtion = partsDuration[i];

				if (materialName == L"") continue;

				SHARED_MAT mat = RESOURCE_FIND(Material, materialName);

				for (int j = 0; j < (UINT)eSixteenDirection::End; ++j)
				{
					mAnimator->Create(
						materialName + L"@" + pathSixteenDirectionString[j],
						mat->GetTexture(),
						Vector2(0, size.y * j),
						size,
						len,
						Vector2::Zero,
						Vector2::Zero,
						durtion
					);
				}
			}
			mAnimator->Sync();
		}
    }

    void BodyParts::shadowOffset()
	{
		if (nullptr == mShadow) return;

		Vector2 shadowOffset = bodyPartsShadowOffset[(int)mBodyPartsType][mAnimationType];
		mShadow->SetShadowOffset(shadowOffset);
	}

	void BodyParts::partLeftDirectionAddZWeight(float* z)
	{
		std::wstring str = pathSixteenDirectionString[mDirection];
		if (str == L"left_down_2"
			|| str == L"left_up_2"
			|| str == L"left_down_1"
			|| str == L"left_down_3"
			|| str == L"left_up_1"
			|| str == L"left_up_3"
			|| str == L"left"
			)
		{
			*z -= 0.00005f;
		}
	}

	void BodyParts::partRightDirectionAddZWeight(float* z)
	{
		std::wstring str = pathSixteenDirectionString[mDirection];
		if (str == L"right_up_2"
			|| str == L"right_down_2"
			|| str == L"right"
			|| str == L"right_up_1"
			|| str == L"right_up_3"
			|| str == L"right_down_1"
			|| str == L"right_down_3"
			)
		{
			*z -= 0.00005f;
		}
	}

	void BodyParts::partAddZWeight()
	{
		Vector3 pos = GET_POS(mPartsOwner);
		pos.x += vPartsOffset[mAnimationType].x;
		pos.y += vPartsOffset[mAnimationType].y;
		switch (mBodyPartsType)
		{
		case eBodyPartsType::Body:
		{
			pos.z -= 0.000015f;
		}
		break;
		case eBodyPartsType::Head:
		{
			pos.z -= 0.00002f;
		}
		break;
		case eBodyPartsType::LeftArm:
		{
			pos.z -= 0.00001f;
			partLeftDirectionAddZWeight(&pos.z);
		}
		break;
		case eBodyPartsType::RightArm:
		{
			pos.z -= 0.00001f;
			partRightDirectionAddZWeight(&pos.z);
		}
		break;
		case eBodyPartsType::Leg:
		{
			pos.z -= 0.000016f;
		}
		break;
		case eBodyPartsType::RightHand:
		{
			pos.z -= 0.00001f;
			partRightDirectionAddZWeight(&pos.z);
		}
		break;
		default:
		{
			pos.z -= 0.00001f;
		}
		break;
		}

		SET_POS_VEC(this, pos);
	}
}
