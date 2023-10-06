#include "mAura.h"

#include "mAuraScript.h"
namespace m
{
    Aura::Aura(GameObject* owner, eAuraType type, Vector2 centerOffset)
        : mOwner(owner)
        , vCenterPosOffset(centerOffset)
        , bFront(false)
    {
        ADD_COMP(this, MeshRenderer);
        ADD_COMP(this, Animator);
        SET_MESH(this, L"RectMesh");
        SET_MATERIAL(this, L"AnimationMaterial");

        mCol = ADD_COMP(this, Collider2D);
        mCol->SetType(eColliderType::Circle);
        mCol->AddExceptType(owner->GetLayerType());
        mCol->SetScale(Vector3(300.f, 150.f, 1.f));
        //col->SetScale(Vector3(100.f, 50, 1.f));

        SetCamera(owner->GetCamera());

        bottomAuraPosition();
        
        mAS = AddComponent<AuraScript>(type, -1.f);
        mAS->SetAuraCollider(mCol);
        mAS->SetAuraOwner(owner);
    }

    Aura::~Aura()
    {
    }

    void Aura::bottomAuraPosition()
    {
        Vector3 pos = GET_POS(mOwner);
        pos.x += vCenterPosOffset.x;
        pos.y += vCenterPosOffset.y;
        if(bFront)
            pos.z -= 0.00001f;
        else
            pos.z += 0.00001f;

        SET_POS_VEC(this, pos);
    }

    void Aura::Update()
    {
        GameObject::Update();

        bottomAuraPosition();
        
    }

    void Aura::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void Aura::Initialize()
    {
        GameObject::Initialize();
    }

    void Aura::Render()
    {
        GameObject::Render();
    }

    void Aura::AuraActive()
    {
        if (mAS)
            mAS->AuraActive();
    }

    void Aura::SetAura(eAuraType type, eLayerType layerType)
    {
        if(mAS)
            mAS->SetAura(type, auraFunctionValue[(int)type][1], layerType);

        if (mCol)
            mCol->SetScale(auraColliderSizes[(int)type]);
    }
}
