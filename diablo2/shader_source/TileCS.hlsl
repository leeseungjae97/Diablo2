#include "global.hlsli"

RWStructuredBuffer<Tile> tileBuffer : register(u0);
RWStructuredBuffer<TileShared> TileSharedBuffer : register(u1);
RWStructuredBuffer<TileCoord> TileCoordBuffer : register(u2);
RWStructuredBuffer<Monster> MonsterBuffer : register(u3);
RWStructuredBuffer<MonsterCoord> MonsterCoordBuffer : register(u4);

[numthreads(100, 1, 1)]
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
    }
    
    
    float2 scale = tileBuffer[DTid.x].tileSize;
    float2 pos = tileBuffer[DTid.x].tilePosition.xy;
    float2 otherPos = TileSharedBuffer[0].mousePos.xy;
    
    if (PointIntersectRhombus(pos, scale, otherPos) == true)
    {
        TileCoordBuffer[0].mouseHoverTileCoord = tileBuffer[DTid.x].tileCoord;
    }
    
    otherPos = TileSharedBuffer[0].playerPos.xy;
    
    if (PointIntersectRhombus(pos, scale, otherPos) == true)
    {
        TileCoordBuffer[0].playerStandTileCoord = tileBuffer[DTid.x].tileCoord;
    }
    
    
    for (uint i = 0; i < TileSharedBuffer[0].monsterCount; ++i)
    {
        otherPos = MonsterBuffer[i].monsterPos.xy;
        if (PointIntersectRhombus(pos, scale, otherPos) == true)
        {
            MonsterCoordBuffer[i].monsterCoord = tileBuffer[DTid.x].tileCoord;
        }
    }
}