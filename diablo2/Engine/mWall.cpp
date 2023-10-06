#include "mWall.h"

#include "../engine_source/mTileManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/mWallObjectManager.h"

#include "mPlayer.h"
#include "mPlayerManager.h"

namespace m
{
    Wall::Wall(eWallType type, Camera* camera, Vector2 coord)
        : mCoord(coord)
        , mWallType(type)
    {
        SetCamera(camera);

        MeshRenderer* mr =ADD_COMP(this, MeshRenderer);

        SET_MESH(this, L"BMesh");
        SET_MATERIAL(this, wallMaterialNames[(int)type]);

        MarkingWallToPathFinder();

        MAKE_GET_TEX(this, tex);
        SET_SCALE_TEX_SIZE(this, tex, 1.f);
        Vector3 scale = GET_SCALE(this);

        mr->AddSpriteOffSetCenterBuffer();
        mr->SetSpriteOffsetCenter(Vector2(0, -TileManager::tileYSize / scale.y));
        if(type == eWallType::Stage2Wall1)
        {
            mr->SetSpriteOffsetCenter(Vector2(0, (- scale.y / 3.f) / scale.y));
        }
        if(type == eWallType::Stage1Door)
        {
            mr->SetSpriteOffsetCenter(Vector2(0, (-TileManager::tileYSize - 18.f) / scale.y));
        }
        if (type == eWallType::Stage1Chair)
        {
            mr->SetSpriteOffsetCenter(Vector2(0, 0));
        }


        mr->AddSpriteAlphaBuffer();

        //Collider2D* col =ADD_COMP(this, Collider2D);

        //col->SetCenter(Vector2(0.f, (scale.y / 2.f) - TileManager::tileYSize));
        //col->SetScale(Vector3(1.f, scale.y / 2.f, 1.f));

        SceneManager::GetActiveScene()->AddGameObject(eLayerType::Wall, this);

        WallObjectManager::Add(this);
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
        Vector3 playerPos = GET_POS(PlayerManager::player);
        if(playerPos.z > pos.z)
        {
            MeshRenderer* mr =GET_COMP(this, MeshRenderer);
            mr->SetSpriteAlpha(0.5f);
        }else
        {
            MeshRenderer* mr = GET_COMP(this, MeshRenderer);
            mr->SetSpriteAlpha(1.f);
        }
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

    void Wall::MarkingWallToPathFinder()
    {
        int sizeX = wallSizes[(int)mWallType][0];
        int sizeY = wallSizes[(int)mWallType][1];
        eWallDirection direction = wallDirections[(int)mWallType];
        
        if(direction == eWallDirection::LeftUpRightDown)
        {
            if(sizeX == 3)
            {
                if(mCoord.y - 1 >= 0)
                    TileManager::pathFindingTiles[mCoord.y - 1][mCoord.x]->SetIsWall(true);
                if (mCoord.y + 1 < 100)
                    TileManager::pathFindingTiles[mCoord.y + 1][mCoord.x]->SetIsWall(true);
            }
            TileManager::pathFindingTiles[mCoord.y][mCoord.x]->SetIsWall(true);
        }
        if (direction == eWallDirection::LeftDownRightUp)
        {
            if (sizeY == 3)
            {
                if (mCoord.x - 1 >= 0)
                    TileManager::pathFindingTiles[mCoord.y][mCoord.x - 1]->SetIsWall(true);
                if (mCoord.x + 1 < 100)
                    TileManager::pathFindingTiles[mCoord.y][mCoord.x + 1]->SetIsWall(true);
            }
            TileManager::pathFindingTiles[mCoord.y][mCoord.x]->SetIsWall(true);
        }
        if(direction == eWallDirection::Point)
        {
            TileManager::pathFindingTiles[mCoord.y][mCoord.x]->SetIsWall(true);
        }
        if (direction == eWallDirection::Tile)
        {
            if (sizeY == 2)
            {
                if (mCoord.y + 1 < 100)
                    TileManager::pathFindingTiles[mCoord.y + 1][mCoord.x]->SetIsWall(true);
            }
            if(sizeX == 2)
            {
                if (mCoord.x + 1 < 100)
                    TileManager::pathFindingTiles[mCoord.y][mCoord.x + 1]->SetIsWall(true);
            }
            if (sizeY == 2 && sizeX == 2)
            {
                if (mCoord.x + 1 < 100 && mCoord.y + 1 < 100)
                    TileManager::pathFindingTiles[mCoord.y + 1][mCoord.x + 1]->SetIsWall(true);
            }
            TileManager::pathFindingTiles[mCoord.y][mCoord.x]->SetIsWall(true);
        }
    }
}
