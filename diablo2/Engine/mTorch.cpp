#include "mTorch.h"

#include "../engine_source/mLight.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/mTileManager.h"
#include "../engine_source/mWallObjectManager.h"

#include "mShadowObject.h"
#include "mTorchScript.h"

namespace m
{
    Torch::Torch(Vector3 initPos, Vector2 coord, Camera* camera, eTorchType type)
        : mCoord(coord)
    {
        SetCamera(camera);

        ADD_COMP(this, MeshRenderer);
        ADD_COMP(this, Animator);

        SET_MESH(this, L"BMesh");
        SET_MATERIAL(this, L"AnimationMaterial");

        SET_POS_VEC(this, initPos);
        SET_SCALE_XYZ(this, vTorchSizes[(int)type].x, vTorchSizes[(int)type].y, 1.f);

        AddComponent<TorchScript>(type);

        Light* lightComp = AddComponent<Light>();
        lightComp->SetType(eLightType::Point);
        lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 0.5f));
        lightComp->SetRadiusX(300.0f);
        lightComp->SetRadiusY(150.0f);

        SceneManager::GetActiveScene()->AddGameObject(eLayerType::Object, this);

        mShadow = new ShadowObject(this, true);
        SceneManager::GetActiveScene()->AddGameObject(eLayerType::Shadow, mShadow);

        WallObjectManager::Add(this);
        TileManager::pathFindingTiles[mCoord.y][mCoord.x]->SetIsWall(true);
    }

    Torch::~Torch()
    {
        if (mShadow)
            mShadow->SetState(Delete);
    }

    void Torch::Initialize()
    {
        GameObject::Initialize();
    }

    void Torch::Update()
    {
        GameObject::Update();
        if (nullptr == mShadow->GetCamera()) mShadow->SetCamera(GetCamera());

        Vector3 pos = GET_POS(this);
        pos.z = 1.f + ((pos.x * 0.0001f) + (pos.y * 0.0001f));

        SET_POS_VEC(this, pos);
    }

    void Torch::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void Torch::Render()
    {
        GameObject::Render();
    }
}
