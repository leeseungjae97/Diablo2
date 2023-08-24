#include "global.hlsli"

RWStructuredBuffer<Tile> TileBuffer : register(u0);
RWStructuredBuffer<Tile> openBuffer : register(u1);
RWStructuredBuffer<Tile> closeBuffer : register(u2);
RWStructuredBuffer<Monster> MonsterBuffer : register(u3);
RWStructuredBuffer<PathFinderSharedData> PathFinderSharedBuffer : register(u4);
RWStructuredBuffer<Tile> PathTileBuffer : register(u5);

[numthreads(5, 5, 5)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    //if (DTid.x > 100)
        //return;
    
    float2 targetCoord = float2(PathFinderSharedBuffer[0].targetTileCoord.x, PathFinderSharedBuffer[0].targetTileCoord.y);
    float2 startCoord = float2(PathFinderSharedBuffer[0].startTileCoord.x, PathFinderSharedBuffer[0].startTileCoord.y);
    
    Tile targetTile = TileBuffer[targetCoord.y * 10 + targetCoord.x];
    Tile startTile = TileBuffer[startCoord.y * 10 + startCoord.x];
    
    int xLength = PathFinderSharedBuffer[0].xLength;
    int yLength = PathFinderSharedBuffer[0].yLength;
    
    int dy = 0;
    int dx = 0;
    if (DTid.x == 0)
    {
        Tile tile = TileBuffer[startCoord.y * 10 + startCoord.x];
        openBuffer[0] = tile;
    }
    
    
    int openSize = 1;
    int openIdx = 0;
    int closeSize = 0;
   
    int i = 0;
    while (openIdx <= openSize)
    {
        Tile curTile;
        if (openIdx == 0 && openSize == 0)
        {
            curTile = openBuffer[openIdx];
        }
        else
        {
            while (openBuffer[openIdx].inOpen == false)
                ++openIdx;
            
            if (openIdx > openSize)
                return;
            
            curTile = openBuffer[openIdx];
        }
        
        
        
        for (i = openIdx; i < openSize; ++i)
        {
            if (openBuffer[i].G + openBuffer[i].H <= curTile.G + curTile.H
                && openBuffer[i].H < curTile.H)
            {
                curTile = openBuffer[i];
            }
        }

        openBuffer[openIdx].inOpen = false;
        
        curTile.inClose = true;
        
        closeBuffer[closeSize] = curTile;
        ++closeSize;
        
        if (curTile.tileCoord.x == targetTile.tileCoord.x
         && curTile.tileCoord.y == targetTile.tileCoord.y)
        {
            int idx = 0;
            Tile targetCurTile = targetTile;
            while (targetCurTile.tileCoord.x != startTile.tileCoord.x
                || targetCurTile.tileCoord.y != startTile.tileCoord.y)
            {
                PathTileBuffer[idx] = targetCurTile;
                ++idx;
                targetCurTile = TileBuffer[targetCurTile.parentCoord.y * 10 + targetCurTile.parentCoord.x];
            }
            PathTileBuffer[idx] = startTile;
            ++idx;
        }
        if (PathFinderSharedBuffer[0].allowdiagonal)
        {
            for (i = 0; i < 4; ++i)
            {
                dy = curTile.tileCoord.y + direct1[i][0];
                dx = curTile.tileCoord.x + direct1[i][1];
                if (dy < 0 || dx < 0 || dy >= yLength || dx >= xLength)
                    continue;
                
                //openTilesAdd(dy, dx, DTid, TileBuffer, MonsterBuffer, PathFinderSharedBuffer, openTiles, openIdx, openSize, curTile);
            }
        }
        for (i = 0; i < 4; ++i)
        {
            dy = curTile.tileCoord.y + direct2[i][0];
            dx = curTile.tileCoord.x + direct2[i][1];
            if (dy < 0 || dx < 0 || dy >= yLength || dx >= xLength)
                continue;
            
            //openTilesAdd(dy, dx, DTid, TileBuffer, MonsterBuffer, PathFinderSharedBuffer, openTiles, openIdx, openSize, curTile);
        }
    }
}