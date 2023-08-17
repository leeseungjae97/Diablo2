#include "global.hlsli"
RWStructuredBuffer<Tile> TileBuffer : register(u0);

[numthreads(100, 100, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    
}