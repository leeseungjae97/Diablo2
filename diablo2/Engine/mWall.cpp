#include "mWall.h"

#include "../engine_source/mTileManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mSceneManager.h"

namespace m
{
    Wall::Wall(Camera* camera, Vector2 coord)
        : mCoord(coord)
    {
        SetCamera(camera);
        ADD_COMP(this, MeshRenderer);

        SET_MESH(this, L"BMesh");
        SET_MATERIAL(this, L"wall1");

        TileManager::pathFindingTiles[mCoord.y][mCoord.x]->SetIsWall(true);

        MAKE_GET_TEX(this, tex);
        SET_SCALE_TEX_SIZE(this, tex, 1.f);
        Vector3 scale = GET_SCALE(this);
        Collider2D* col =ADD_COMP(this, Collider2D);

        col->SetCenter(Vector2(0.f, scale.y / 2.f));
        col->SetScale(Vector3(1.f, scale.y / 2.f, 1.f));

        SceneManager::GetActiveScene()->AddGameObject(eLayerType::Wall, this);
        //ADD_COMP(this, WallScript);
    }

    Wall::~Wall()
    {
    }

    void Wall::Initialize()
    {
        GameObject::Initialize();
    }

    void Wall::Update()
    {
        GameObject::Update();

        Vector3 pos = GET_POS(this);
        pos.z = 1.f + ((pos.x * 0.0001f) + (pos.y * 0.0001f));
        SET_POS_VEC(this, pos);
    }

    void Wall::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void Wall::Render()
    {
        GameObject::Render();
    }
}
