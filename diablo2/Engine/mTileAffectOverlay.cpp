#include "mTileAffectOverlay.h"

#include "../engine_source/mMeshRenderer.h"

#include "mAffectOverlayScript.h"

namespace m
{
    TileAffectOverlay::TileAffectOverlay(Vector3 initPos, eAffectOverlayType type, eLayerType mOwnerType)
        :MoveAbleObject(initPos, 0.f, true)
    {
        SET_POS_VEC(this, initPos);
        SET_SCALE_XYZ(this
            , affectOverlaySizes[(int)type].x
            , affectOverlaySizes[(int)type].y
            , 1.f);
        
        SET_MESH(this, L"RectMesh");
        SET_MATERIAL(this, L"AnimationMaterial");

        //Collider2D* col = ADD_COMP(this, Collider2D);
        
        bodyBoxCollider->AddExceptType(mOwnerType);

        ADD_COMP(this, Animator);
        mAOS = AddComponent<AffectOverlayScript>(type);
        mAOS->SetLoopCount(10);
    }

    TileAffectOverlay::~TileAffectOverlay()
    {
    }

    void TileAffectOverlay::Initialize()
    {
        MoveAbleObject::Initialize();
    }

    void TileAffectOverlay::Update()
    {
        MoveAbleObject::Update();
    }

    void TileAffectOverlay::LateUpdate()
    {
        MoveAbleObject::LateUpdate();
    }

    void TileAffectOverlay::Render()
    {
        MoveAbleObject::Render();
    }

    void TileAffectOverlay::Hit(int damage)
    {
    }
}
