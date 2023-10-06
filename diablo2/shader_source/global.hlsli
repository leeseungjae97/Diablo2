#ifndef GLOBAL_INCLUDED

#define GLOBAL_INCLUDED
cbuffer Transform : register(b0)
{
    row_major matrix mWorld;
    row_major matrix mView;
    row_major matrix mProjection;
}
cbuffer Grid : register(b2)
{
    float4 CameraPosition;
    float2 CameraScale;
    float2 Resolution;
}
cbuffer Animator : register(b3)
{
    float2 SpriteLeftTop;
    float2 SpriteSize;
    float2 SpriteOffset;
    float2 AtlasSize;
    float2 SpriteOffsetOfCenterPos;
    
    uint animationType;
    float mAlpha;
}
cbuffer UVControl : register(b4)
{
    float UVYCoord;
    uint uvControlType;
}
cbuffer ParticleSystem : register(b5)
{
    uint elementCount;
    float elapsedTime;
    float deltaTime;
    float alpha;
    int padd2;
}
cbuffer Noise : register(b6)
{
    float4 noiseTextureSize;
}

struct DrawObject
{
    float4 position;
    float2 size;
};
struct Tile
{
    float4 tilePosition;
    float2 tileSize;
    float2 tileCoord;
    
    bool isWall;
    bool isThrough;
    
    //float2 parentCoord;
    
    //bool isWall;
    //bool onMonster;
    
    //uint willOnMonsterCount;
    
    //bool inClose;
    //bool inOpen;
    
    //int G;
    //int H;
};
struct TileShared
{
    float4 mousePos;
    float4 playerPos;
    uint tileCount;
    uint monsterCount;
    bool hoverUI;
};
struct Monster
{
    float4 monsterPos;
    float3 monsterSize;
    float2 monsterNextCoord;
    int monsterCount;
};
struct MonsterComputedCoord
{
    float2 monsterCoord;
};
struct TileComputedCoord
{
    float2 mouseHoverTileCoord;
    float2 playerStandTileCoord;
    float2 hoverMonsterTileCoord;
    int hoverMonsterId;
    bool hoverMonster;
};
struct ParticleShared
{
    uint ActiveSharedCount;
};
struct PathFinderSharedData
{
    bool findStart;
    float4 startTileCoord;
    float4 targetTileCoord;
    
    float searchSize;
    
    bool allowdiagonal;
    bool dontcrosscorner;

    int xLength;
    int yLength;
    
    bool isMonster;
    int monsterId;
};
struct LightAttribute
{
    float4 color;
    float4 position;
    float4 direction;
    
    uint type;
    float radiusX;
    float radiusY;
    float angle;
    int pad;
    int size;
};
struct TrappingColor
{
    float4 color;
};
struct SpriteOffsetCenter
{
    float2 offset;
};
struct SpriteAlpha
{
    float alpha;
};
struct Particle
{
    float4 position;
    float4 direction;
    
    float alpha;
    float alpha2;
    float alpha3;
    float endTime;
    float time;
    float speed;
    uint active;
};
struct SkillWallCollision
{
    float3 position;
    uint skillId;
    uint size;
    bool crash;
};
StructuredBuffer<Tile> tiles : register(t11);
StructuredBuffer<Monster> monsters : register(t12);

StructuredBuffer<LightAttribute> lightsAttribute : register(t13);
StructuredBuffer<Particle> particles : register(t14);

Texture2D albedoTexture : register(t0);
Texture2D gameView : register(t61);
Texture2D noiseTexture : register(t15);
Texture2D atlasTexture : register(t16);

SamplerState pointSampler : register(s0);
//SamplerState anisotropicSampler : register(s1);

static float GaussianFilter[5][5] =
{
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.0219f, 0.0983f, 0.1621f, 0.0983f, 0.0219f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
};
static float direct1[4][2] =
{
    1, 1,
    1, -1,
    -1, -1,
    -1, 1
};

static float direct2[4][2] =
{
    1, 0,
    0, 1,
    -1, 0,
    0, -1
};

float4 GaussianBlur(float2 UV)
{
    float4 Out = (float4) 0.0f;
    
    if (1.f < UV.x)
        UV.x = frac(UV.x);
    else if (UV.x < 0.0f)
        UV.x = 1.0f + frac(UV.x);
        
    if (1.f < UV.y)
        UV.y = frac(UV.y);
    else if (UV.y < 0.0f)
        UV.y = 1.0f + frac(UV.y);
    
    int2 iUV = UV * noiseTextureSize.xy;
    iUV -= int2(2, 2);
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int2 idx = int2(iUV.y + i, iUV.x + j);
            Out += noiseTexture[idx] * GaussianFilter[i][j];
        }
    }
    
    return Out;
}
void CalculateLight2D(in out float4 lightColor, float3 position, int idx)
{
    if (0 == lightsAttribute[idx].type)
    {
        lightColor += lightsAttribute[idx].color;
    }
    else if (1 == lightsAttribute[idx].type)
    {
        float lengthX = (position.x - lightsAttribute[idx].position.x) / lightsAttribute[idx].radiusX;
        float lengthY = (position.y - lightsAttribute[idx].position.y) / lightsAttribute[idx].radiusY;

        float distanceSquared = lengthX * lengthX + lengthY * lengthY;

        if (distanceSquared < 1.0f)
        {
            float ratio = 1.0f - distanceSquared;
            if (lightColor.a + lightsAttribute[idx].color.a * ratio < 1.f)
                lightColor.a += lightsAttribute[idx].color.a * ratio;
            else 
                lightColor.a = 1.f;
            
            if (lightColor.g + lightsAttribute[idx].color.g * ratio < 1.f)
                lightColor.g += lightsAttribute[idx].color.g * ratio;
            else 
                lightColor.g = 1.f;
            
            if (lightColor.b + lightsAttribute[idx].color.b * ratio < 1.f)
                lightColor.b += lightsAttribute[idx].color.b * ratio;
            else 
                lightColor.b = 1.f;
            
            if (lightColor.r + lightsAttribute[idx].color.r * ratio < 1.f)
                lightColor.r += lightsAttribute[idx].color.r * ratio;
            else
                lightColor.r = 1.f;
            
            //lightColor += lightsAttribute[idx].color * ratio;
        }
    }
}

bool PointIntersectRhombus(float2 pos, float2 scale, float2 otherPos)
{
    float2 vertex[4];
    float gradient[4];
    float intercept[4];
    uint i = 0;
    float2 direct[4] =
    {
        { -(scale.x / 2.f), 0 },
        { 0, -(scale.y / 2.f) },
        { (scale.x / 2.f), 0 },
        { 0, (scale.y / 2.f) }
    };
    
    for (i = 0; i < 4; ++i)
    {
        vertex[i].x = pos.x + direct[i].x;
        vertex[i].y = pos.y + direct[i].y;
    }
    for (i = 0; i < 4; ++i)
    {
        gradient[i] = ((vertex[i].y - vertex[(i + 1) % 4].y) / (vertex[i].x - vertex[(i + 1) % 4].x));
        intercept[i] = vertex[i].y - gradient[i] * vertex[i].x;
    }
    float _y = otherPos.y;
    float _x = otherPos.x;

    if (gradient[0] * _x + intercept[0] < _y
        && gradient[1] * _x + intercept[1] < _y
        && gradient[2] * _x + intercept[2] > _y
        && gradient[3] * _x + intercept[3] > _y)
    {
        return true;
    }
    else
        return false;
}

//void openTilesAdd(
//            int y
//            , int x
//            , uint3 id
//            , RWStructuredBuffer<Tile> TilesBuffer
//            , RWStructuredBuffer<Monster> MonsterBuffer
//            , RWStructuredBuffer<PathFinderSharedData> PathFinderSharedBuffer
//            , RWStructuredBuffer<Tile> openBuffer
//            , int openIdx
//            , int openSize
//            , Tile curTile)
//{
//    if (PathFinderSharedBuffer[0].isMonster
//			&& mMonsterOwner - > GetNextMoveCoord() == Vector2(x, y)
//			&& TileManager::pathFindingTiles[y][x] - > GetMonsterNext() != 0)
//        return;
    
//    float2 mTargetCoord = PathFinderSharedBuffer[0].targetTileCoord.xy;
//    float searchTileSize = PathFinderSharedBuffer[0].searchSize;
    
//    if (x >= (mTargetCoord.x - searchTileSize < 0 ? 0 : mTargetCoord.x - searchTileSize)
//			&& x < mTargetCoord.x + searchTileSize
//			&& y >= (mTargetCoord.y - searchTileSize < 0 ? 0 : mTargetCoord.y - searchTileSize)
//			&& y < mTargetCoord.y + searchTileSize
//			&& TilesBuffer[y * 10 + x].isWall == false
//			&& TilesBuffer[y * 10 + x].onMonster == false
//			&& TilesBuffer[y * 10 + x].inClose == false)
//    {
//        if (PathFinderSharedBuffer[0].allowdiagonal)
//        {
//            if (TilesBuffer[curTile.tileCoord.y * 10 + x].isWall
//					&& TilesBuffer[y * 10 + curTile.tileCoord.x].isWall)
//                return;
//        }
//        if (PathFinderSharedBuffer[0].dontcrosscorner)
//        {
//            if (TilesBuffer[y * 10 + curTile.tileCoord.x].isWall || TilesBuffer[curTile.tileCoord.y * 10 + x].isWall)
//                return;
//        }
//        Tile neighborTile = TilesBuffer[y * 10 + x];
//        int moveCost = curTile.G
//						 + (curTile.tileCoord.x - x == 0
//						 || curTile.tileCoord.y - y == 0 ? 10 : 14);

//        if (moveCost < neighborTile.G || !neighborTile.inOpen)
//        {
//            neighborTile.G = moveCost;
//            neighborTile.H = ((abs(neighborTile.tileCoord.x - mTargetCoord.x)
//									+ abs(neighborTile.tileCoord.y - mTargetCoord.y)) * 10);
//            neighborTile.parentCoord = curTile.tileCoord;

//            neighborTile.inOpen = true;
//            openBuffer[openSize] = neighborTile;
//        }
//    }
//}

#endif