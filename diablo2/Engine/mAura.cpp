#include "mAura.h"

#include "mAuraScript.h"
namespace m
{
    Aura::Aura(GameObject* owner, eAuraType type, Vector2 centerOffset)
        : mOwner(owner)
        , vCenterPosOffset(centerOffset)
    {
        ADD_COMP(this, MeshRenderer);
        ADD_COMP(this, Animator);
        SET_MESH(this, L"RectMesh");
        SET_MATERIAL(this, L"AnimationMaterial");

        Collider2D* col= ADD_COMP(this, Collider2D);
        col->SetType(eColliderType::Circle);
        col->AddExceptType(owner->GetLayerType());
        col->SetScale(Vector3(300.f, 150.f, 1.f));
        //col->SetScale(Vector3(100.f, 50, 1.f));

        SetCamera(owner->GetCamera());

        //bottomAuraPosition();
        SET_SCALE_XYZ(this, auraSizes[(int)type].x, auraSizes[(int)type].y, 1.f);
        AuraScript* mAS = AddComponent<AuraScript>(type, -1.f);
        mAS->SetAuraCollider(col);
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
        pos.z += 0.1f;
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
}
