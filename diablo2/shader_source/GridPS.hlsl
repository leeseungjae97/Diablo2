#include "global.hlsli"

struct PSIn
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    float2 GridPos : POSITION;
};

struct PSOut
{
    float4 Pos : SV_Target;
};

PSOut main(PSIn In)
{
    PSOut Out;
    
    Out.Pos = float4(1.0f, 0.0f, 1.0f, 1.0f);
    
    const int width = 100;
    const int height = 100;
       
    int gridX = (int) In.GridPos.x;
    int gridY = (int) In.GridPos.y;
    
    if (abs((gridX + 1) % width) <= 1.0f)
        return Out;
    
    if (abs((gridY + 1) % height) <= 1.0f)
        return Out;
    
    discard;
    
    return Out;
}