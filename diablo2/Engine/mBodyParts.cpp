#include "mBodyParts.h"

#include "../engine_source/mSceneManager.h"

namespace m
{
    BodyParts::BodyParts(eBodyPartsType type, GameObject* _mPartsOwner)
        : mBodyPartsType(type)
        , mPartsOwner(_mPartsOwner)
        , mAnimator(nullptr)
        , mDriection(0)
        , mAnimationType(0)
    {
        SetCamera(_mPartsOwner->GetCamera());

        SET_MESH(this, L"RectMesh");
        SET_MATERIAL(this, L"AnimationMaterial");

        mAnimator = GET_COMP(this, Animator);
        Animator* ownerAnimator = GET_COMP(_mPartsOwner, Animator);

        mAnimator->SetSyncAnimator(ownerAnimator);

        for(int i = 0 ; i < (int)ePlayerAnimationType::End; ++i )
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
                    materialName + pathSixteenDirectionString[j],
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

        mDriection = (int)ePathSixteenDirection::Down;
        mAnimationType = (int)ePlayerAnimationType::Natural;

        Vector2 scale = partsSizes[(int)type][mAnimationType];
        SET_SCALE_XYZ(this, scale.x, scale.y, 1.f);
        mAnimator->PlayAnimation(partsMaterialNames[(int)mBodyPartsType][mAnimationType] + pathSixteenDirectionString[mDriection], true);
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
        Vector3 pos = GET_POS(mPartsOwner);
        pos.x += bodyPartsOffset[(int)mBodyPartsType][mAnimationType].x;
        pos.y += bodyPartsOffset[(int)mBodyPartsType][mAnimationType].y;
        switch (mBodyPartsType)
        {
        case eBodyPartsType::Body:
            {
            pos.z -= 0.1f;
            }
        case eBodyPartsType::Head:
        {
            pos.z -= 0.1f;
        }
        case eBodyPartsType::Body:
        {
            pos.z -= 0.1f;
        }
        case eBodyPartsType::Body:
        {
            pos.z -= 0.1f;
        }
        case eBodyPartsType::Body:
        {
            pos.z -= 0.1f;
        }
        case eBodyPartsType::Body:
        {
            pos.z -= 0.1f;
        }
        }
        SET_POS_VEC(this, pos);

        std::wstring animtionName = partsMaterialNames[(int)mBodyPartsType][mAnimationType] + pathSixteenDirectionString[mDriection];

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
}
