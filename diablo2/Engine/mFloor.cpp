#include "mFloor.h"

#include "mTime.h"
#include "../engine_source/mMeshRenderer.h"

namespace m
{
    Floor::Floor(Vector3 initPos)
        : fAcc(0.f)
        , iMatIndex(0)
    {
        ADD_COMP(this, MeshRenderer);

        SET_MESH(this, L"RectMesh");
        SET_MATERIAL(this, L"lava1");

        SET_POS_VEC(this, initPos);
        SET_SCALE_XYZ(this, 8000, 4000, 1.f);
    }

    Floor::~Floor()
    {
    }

    void Floor::Initialize()
    {
        GameObject::Initialize();
    }

    void Floor::Update()
    {
        GameObject::Update();
        fAcc += Time::fDeltaTime();
        if(fAcc >= 0.1f)
        {
            ++iMatIndex;
            iMatIndex %= 10;
            SHARED_MAT mat = RESOURCE_FIND(Material, stage1Floors[iMatIndex]);

            SET_MATERIAL(this, stage1Floors[iMatIndex]);
            fAcc = 0.0f;
        }
    }

    void Floor::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void Floor::Render()
    {
        GameObject::Render();
    }
}
