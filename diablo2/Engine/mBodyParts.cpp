#include "mBodyParts.h"

#include "../engine_source/mSceneManager.h"

namespace m
{
	BodyParts::BodyParts(eBodyPartsType type, GameObject* _mPartsOwner)
		: mBodyPartsType(type)
		, mPartsOwner(_mPartsOwner)
		, mAnimator(nullptr)
		, mDirection(0)
		, mAnimationType(0)
	{
		SetCamera(_mPartsOwner->GetCamera());

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");

		mAnimator = GET_COMP(this, Animator);
		Animator* ownerAnimator = GET_COMP(_mPartsOwner, Animator);

		mAnimator->SetSyncAnimator(ownerAnimator);

		for (int i = 0; i < (int)ePlayerAnimationType::End; ++i)
		{
			std::wstring materialName = partsMaterialNames[(int)type][i];
			Vector2 size = partsSizes[(int)type][i];
			int len = partsLength[i];
			float durtion = partsDuration[i];
			Vector2 centerPos = partsCenterPos[(int)type][i];
			if (materialName == L"") continue;

			SHARED_MAT mat = RESOURCE_FIND(Material, materialName);

			for (int j = 0; j < (UINT)eSixteenDirection::End; ++j)
			{
				mAnimator->Create(
					materialName + L"@" +pathSixteenDirectionString[j],
					mat->GetTexture(),
					Vector2(0, size.y * j),
					size,
					len,
					Vector2::Zero,
					centerPos,
					durtion
				);
			}
		}

		mDirection = (int)ePathSixteenDirection::Down;
		mAnimationType = (int)ePlayerAnimationType::Natural;

		Vector2 scale = partsSizes[(int)type][mAnimationType];
		SET_SCALE_XYZ(this, scale.x, scale.y, 1.f);
		mAnimator->PlayAnimation(partsMaterialNames[(int)mBodyPartsType][mAnimationType] + L"@" + pathSixteenDirectionString[mDirection], true);
		mAnimator->Sync();
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Object, this);
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
		partAddZWeight();


		std::wstring animtionName = partsMaterialNames[(int)mBodyPartsType][mAnimationType] + L"@" + pathSixteenDirectionString[mDirection];

		if (mAnimator->GetActiveAnimation()->GetKey() != animtionName)
		{
			Vector2 scale = partsSizes[(int)mBodyPartsType][mAnimationType];
			SET_SCALE_XYZ(this, scale.x, scale.y, 1.f);

			mAnimator->PlayAnimation(animtionName, true);
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

	void BodyParts::ChangeHead()
	{
	}
	std::shared_ptr<Texture> BodyParts::GetCurrentImage()
	{
		Animator* animator = GET_COMP(this, Animator);

		if (animator)
		{
			if (animator->GetActiveAnimation())
			{
				std::shared_ptr<Texture> tex = std::make_shared<Texture>();
				Animation* animation = animator->GetActiveAnimation();
				int x = animator->GetAnimationIndex();
				Animation::Sprite sprite = animator->GetActiveAnimation()->GetCurrentSprite();

				int wid = animation->GetAtlas()->GetMetaDataWidth();
				int hei = animation->GetAtlas()->GetMetaDataHeight();

				Vector2 size = Vector2(sprite.size.x * wid, sprite.size.y * hei);

				std::wstring keyName = animator->GetActiveAnimation()->GetKey();
				WSTRING_SUBSTR_WOT(keyName, L'@', subStr);
				subStr += L"S";
				SHARED_MAT mat =RESOURCE_FIND(Material, subStr);

				tex->GetTextureInTexture(mat->GetTexture()
					, Vector2(x * size.x, mDirection * size.y), size.x, size.y);
				return tex;
			}
		}

		return nullptr;
	}
	Vector2 BodyParts::GetSpriteCenterPos()
	{
		return bodyPartsOffset[(int)mBodyPartsType][mAnimationType];
	}
    void BodyParts::partLeftDirectionAddZWeight(float* z)
    {
		std::wstring str = pathSixteenDirectionString[mDirection];
		if(str == L"left_down_2"
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
		pos.x += bodyPartsOffset[(int)mBodyPartsType][mAnimationType].x;
		pos.y += bodyPartsOffset[(int)mBodyPartsType][mAnimationType].y;
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
			pos.z -= 0.00002f;
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
