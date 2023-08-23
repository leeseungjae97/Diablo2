#include "global.hlsli"
//RWStructuredBuffer<PathfindingTile> openBuffer : register(u0);
//RWStructuredBuffer<PathfindingTile> closeBuffer : register(u1);
//RWStructuredBuffer<Tile> pathBuffer : register(u0);
//RWStructuredBuffer<PathfindingShared> sharedBuffer : register(u1);
//RWStructuredBuffer<PathfindingTile> tilesBuffer : register(u2);

[numthreads(1, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    //uint3 groupThreadID : SV_GroupThreadID;
    //uint3 groupIndex : SV_GroupIndex;
    //uint tileIndex : SV_PrimitiveID;
    //uint tileIndex : SV_InstanceID;
    
    //Tile openBuffer[1000] = { };
    //Tile closeBuffer[10000] = { };
    
    //int openIdx = sharedBuffer[0].pathBufferIndex;
    //while (openIdx != 0)
    {
        //while (openBuffer[openIdx].erased == true) ++openIndex;
        
        //PathfindingTile tile = openBuffer[openIdx];
        
        //for (int i = 0; i < openIdx; ++i)
        //{
        //    if (openBuffer[openIdx].G + openBuffer[openIdx].H <=
        //        tile.G + tile.H
        //        && openBuffer[openIdx].H < tile.H)
        //    {
        //        tile = openBuffer[i];
        //    }
        //}

        //openBuffer[tile.inOpenBufferIndex].erased;
        
        //closeBuffer[sharedBuffer[0].closedBufferIndex] = tile;
        
        //openBufferAdd(0, 0, float2(), 1.f, tile, 0, true, true, false, 1);
    }
}