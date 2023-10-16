#include "global.hlsli"

RWStructuredBuffer<Tile> TileBuffer : register(u0);
RWStructuredBuffer<TileShared> TileSharedBuffer : register(u1);
RWStructuredBuffer<TileComputedCoord> TileCoordBuffer : register(u2);
RWStructuredBuffer<Monster> MonsterBuffer : register(u3);
RWStructuredBuffer<MonsterComputedCoord> MonsterCoordBuffer : register(u4);
RWStructuredBuffer<SkillWallCollision> SkillBuffer : register(u5);
RWStructuredBuffer<SkillWallCollision> GSkillBuffer : register(u6);

[numthreads(1000, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{    

    
    if (TileSharedBuffer[0].tileCount < DTid.x)
    {
        return;
    }
    
    if (TileSharedBuffer[0].hoverUI == true)
    {
        TileCoordBuffer[0].mouseHoverTileCoord = float2(-1.f, -1.f);
        TileCoordBuffer[0].playerStandTileCoord = float2(-1.f, -1.f);
        return;
    }
    if (DTid.x == 0)
    {
        TileCoordBuffer[0].mouseHoverTileCoord = float2(-1.f, -1.f);
        TileCoordBuffer[0].playerStandTileCoord = float2(-1.f, -1.f);
        TileCoordBuffer[0].hoverMonsterTileCoord = float2(-1.f, -1.f);
        TileCoordBuffer[0].hoverMonsterId = -1;

    }
    if (TileBuffer[DTid.x].tileCoord.x == -1.f
        || TileBuffer[DTid.x].tileCoord.y == -1.f)
        return;
    
    uint tileCount = TileSharedBuffer[0].tileCount / 2;
    if (TileBuffer[DTid.x].tileCoord.x > 100.f
        || TileBuffer[DTid.x].tileCoord.y > 100.f)
        return;
  
    float2 scale = TileBuffer[DTid.x].tileSize;
    float2 pos = TileBuffer[DTid.x].tilePosition.xy;
    float2 otherPos = float2(0.f, 0.f);
    
    if (TileBuffer[DTid.x].isWall != false
        && TileBuffer[DTid.x].isThrough == false)
    {
        for (uint i = 0; i < TileSharedBuffer[0].skillCount; ++i)
        {
            otherPos = SkillBuffer[i].position.xy;
            GSkillBuffer[i].skillId = SkillBuffer[i].skillId;
            
            if (PointIntersectRhombus(pos, scale, otherPos) == true)
            {
                GSkillBuffer[i].crash = true;
            }
        }
    }
    
    scale = TileBuffer[DTid.x].tileSize;
    pos = TileBuffer[DTid.x].tilePosition.xy;
    otherPos = TileSharedBuffer[0].mousePos.xy;
    
    if (PointIntersectRhombus(pos, scale, otherPos) == true)
    {
        TileCoordBuffer[0].mouseHoverTileCoord = TileBuffer[DTid.x].tileCoord;
    }
    
    
    
    otherPos = TileSharedBuffer[0].playerPos.xy;
    
    if (PointIntersectRhombus(pos, scale, otherPos) == true)
    {
        TileCoordBuffer[0].playerStandTileCoord = TileBuffer[DTid.x].tileCoord;
    }
    
    for (uint i = 0; i < TileSharedBuffer[0].monsterCount; ++i)
    {
        otherPos = MonsterBuffer[i].monsterPos.xy;
        
        if (TileBuffer[DTid.x].tileCoord.x > 100.f
        || TileBuffer[DTid.x].tileCoord.y > 100.f)
            break;
        
        if (PointIntersectRhombus(pos, scale, otherPos) == true)
        {
            MonsterCoordBuffer[i].monsterCoord = TileBuffer[DTid.x].tileCoord;
        }
    }
    
    otherPos = TileSharedBuffer[0].mousePos.xy;
    for (uint i = 0; i < TileSharedBuffer[0].monsterCount; ++i)
    {
        pos = MonsterBuffer[i].monsterPos.xy;
        scale = MonsterBuffer[i].monsterSize.xy;
        if (PointIntersectRhombus(pos, scale, otherPos) == true)
        {
            TileCoordBuffer[0].hoverMonster = true;
            TileCoordBuffer[0].hoverMonsterId = i;
            TileCoordBuffer[0].hoverMonsterTileCoord = MonsterCoordBuffer[i].monsterCoord;
        }
    }
    //if (DTid.x == 30)
    //{
    //    TileBuffer[DTid.x].isWall = true;
    //}   
    //pos = TileBuffer[DTid.x].tilePosition.xy;
    //scale = TileBuffer[DTid.x].tileSize.xy;
}