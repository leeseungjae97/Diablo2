#include "mTileAffectOverlay.h"

#include "../engine_source/mMeshRenderer.h"

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

        ADD_COMP(this, Animator);
        mAOS = AddComponent<AffectOverlayScript>(type);
        mAOS->SetLoopCount(10);
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
        if (GetLayerType() == eLayerType::Player)
        {
            //pos.z = 1.f + ((TileManager::playerStandTile->GetCoord().x * 0.0001f) + (TileManager::playerStandTile->GetCoord().y * 0.0001f));
            pos.z = 1.f + ((TileManager::GetPlayerPosition().x * 0.0001f) + (TileManager::GetPlayerPosition().y * 0.0001f));
        }
        else
        {
            //pos.z = 1.f + ((mCoord.x * 0.0001f) + (mCoord.y * 0.0001f));
            pos.z = 1.f + ((pos.x * 0.0001f) + (pos.y * 0.0001f));
        }
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
}
