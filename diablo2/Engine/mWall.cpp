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
            SceneManager::GetActiveScene()->AddGameObject(eLayerType::Wall, this);
        }
        else if(type == eWallType::Stage1Door)
        {
            mr->SetSpriteOffsetCenter(Vector2(0, (-TileManager::tileYSize - 18.f) / scale.y));
            SceneManager::GetActiveScene()->AddGameObject(eLayerType::Wall, this);
        }
        else if (type == eWallType::Stage1Chair)
        {
            mr->SetSpriteOffsetCenter(Vector2(0, 0));
            SceneManager::GetActiveScene()->AddGameObject(eLayerType::Wall, this);
        }
        else if(type == eWallType::Stage0Wall1)
        {
            mr->SetSpriteOffsetCenter(Vector2(0, 0.f));
            SceneManager::GetActiveScene()->AddGameObject(eLayerType::NoCullWall, this);
        }else
        {
            SceneManager::GetActiveScene()->AddGameObject(eLayerType::Wall, this);
        }
        mr->AddSpriteAlphaBuffer();
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

        if(GetLayerType() == eLayerType::Wall)
        {    
            if (playerPos.z > pos.z)
            {
                MeshRenderer* mr = GET_COMP(this, MeshRenderer);
                mr->SetSpriteAlpha(0.5f);
            }
            else
            {
                MeshRenderer* mr = GET_COMP(this, MeshRenderer);
                mr->SetSpriteAlpha(1.f);
            }
        }else
        {
            MeshRenderer* mr = GET_COMP(this, MeshRenderer);
            mr->SetSpriteAlpha(1.f);
            pos.z -= playerPos.z;
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
        if (direction == eWallDirection::Door) return;

        if(direction == eWallDirection::LeftUpRightDown)
        {
            if(sizeX == 3)
            {
                if(mCoord.y - 1 >= 0)
                {
                    TileManager::pathFindingTiles[mCoord.y - 1][mCoord.x]->SetIsWall(true);
                    TileManager::pathFindingTiles[mCoord.y - 1][mCoord.x]->SetThroughWall(false);
                }
                if (mCoord.y + 1 < 100)
                {
                    TileManager::pathFindingTiles[mCoord.y + 1][mCoord.x]->SetIsWall(true);
                    TileManager::pathFindingTiles[mCoord.y + 1][mCoord.x]->SetThroughWall(false);
                }
            }

        }
        if (direction == eWallDirection::LeftDownRightUp)
        {
            if (sizeY == 3)
            {
                if (mCoord.x - 1 >= 0)
                {
                    TileManager::pathFindingTiles[mCoord.y][mCoord.x - 1]->SetIsWall(true);
                    TileManager::pathFindingTiles[mCoord.y][mCoord.x - 1]->SetThroughWall(false);
                    
                }
                if (mCoord.x + 1 < 100)
                {
                    TileManager::pathFindingTiles[mCoord.y][mCoord.x + 1]->SetIsWall(true);
                    TileManager::pathFindingTiles[mCoord.y][mCoord.x + 1]->SetThroughWall(false);
                }

            }
        }
        if (direction == eWallDirection::Tile)
        {
            if (sizeY == 2)
            {
                if (mCoord.y + 1 < 100)
                {
                    TileManager::pathFindingTiles[mCoord.y + 1][mCoord.x]->SetIsWall(true);
                    TileManager::pathFindingTiles[mCoord.y + 1][mCoord.x]->SetThroughWall(false);
                }
                    
            }
            if(sizeX == 2)
            {
                if (mCoord.x + 1 < 100)
                {
                    TileManager::pathFindingTiles[mCoord.y][mCoord.x + 1]->SetIsWall(true);
                    TileManager::pathFindingTiles[mCoord.y][mCoord.x + 1]->SetThroughWall(false);
                }
                    
            }
            if (sizeY == 2 && sizeX == 2)
            {
                if (mCoord.x + 1 < 100 && mCoord.y + 1 < 100)
                {
                    TileManager::pathFindingTiles[mCoord.y + 1][mCoord.x + 1]->SetIsWall(true);
                    TileManager::pathFindingTiles[mCoord.y + 1][mCoord.x + 1]->SetThroughWall(false);
                }
                    
            }
        }
        TileManager::pathFindingTiles[mCoord.y][mCoord.x]->SetIsWall(true);
        TileManager::pathFindingTiles[mCoord.y][mCoord.x]->SetThroughWall(false);
    }
}
