#include "global.hlsli"

RWStructuredBuffer<Tile> tileBuffer : register(u0);
RWStructuredBuffer<TileShared> TileSharedBuffer : register(u1);
RWStructuredBuffer<TileCoord> TileCoordBuffer : register(u2);

[numthreads(128, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    float2 scale = tileBuffer[DTid.x].tileSize;
    float4 pos = tileBuffer[DTid.x].tilePosition;
    float2 otherPos = TileSharedBuffer[DTid.x].mousePos;
    
    float2 vertex[4];
    float gradient[4];
    float intercept[4];
    
    float2 direct[4] =
    {
        { -(scale.x / 2.f), 0 },
        { 0, -(scale.y / 2.f) },
        { (scale.x / 2.f), 0 },
        { 0, (scale.y / 2.f) },
    };
    
    for (int i = 0; i < 4; i++)
    {
        vertex[i].x = pos.x + direct[i].x;
        vertex[i].y = pos.y + direct[i].y;
    }
    for (int i = 0; i < 4; i++)
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
        TileCoordBuffer[DTid.x].mouseHoverTileCoord = float2(5.f, 5.f);
    }
    else
        TileCoordBuffer[DTid.x].mouseHoverTileCoord = float2(-1.f, -1.f);
}