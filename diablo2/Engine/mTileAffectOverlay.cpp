#include "mTileAffectOverlay.h"

#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mLight.h"

#include "mAffectOverlayScript.h"
#include "mTileManager.h"

namespace m
{
    TileAffectOverlay::TileAffectOverlay(Vector3 initPos, eAffectOverlayType type, eLayerType mOwnerType)
        : GameObject()
    {
        SET_POS_VEC(this, initPos);
        SET_SCALE_XYZ(this
            , affectOverlaySizes[(int)type].x
            , affectOverlaySizes[(int)type].y
            , 1.f);

        ADD_COMP(this, MeshRenderer);

        SET_MESH(this, L"RectMesh");
        SET_MATERIAL(this, L"AnimationMaterial");
        ADD_COMP(this, Collider2D);
        ADD_COMP(this, Animator);
        mAOS = AddComponent<AffectOverlayScript>(type);

        Light* lightComp = AddComponent<Light>();
        lightComp->SetType(eLightType::Point);
        lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 0.3f));
        lightComp->SetRadiusX(200.0f);
        lightComp->SetRadiusY(100.0f);
    }

    TileAffectOverlay::~TileAffectOverlay()
    {
    }

    void TileAffectOverlay::Initialize()
    {
        GameObject::Initialize();
    }

    void TileAffectOverlay::Update()
    {
        GameObject::Update();
        addZWeight();
        
    }
    void TileAffectOverlay::addZWeight()
    {
        Vector3 pos = GET_POS(this);
        pos.z = 1.f + ((pos.x * 0.0001f) + (pos.y * 0.0001f));
        SET_POS_VEC(this, pos);
    }
    void TileAffectOverlay::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void TileAffectOverlay::Render()
    {
        GameObject::Render();
    }

    void TileAffectOverlay::ActiveOverlay()
    {
        if(mAOS)
            mAOS->ActiveAffectOverlay();
    }

    void TileAffectOverlay::SetLoopCount(int count)
    {
        mAOS->SetLoopCount(count);
    }
}
