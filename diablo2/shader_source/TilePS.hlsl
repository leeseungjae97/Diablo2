#include "global.hlsli"
Texture2D<float4> greenOutline : register(t0);
Texture2D<float4> greenTile : register(t1);
Texture2D<float4> redTile : register(t2);

StructuredBuffer<Tile> tilesPS : register(t11);
struct GSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    uint Instance : SV_InstanceID;
};

float4 main(GSOut In) : SV_TARGET
{
    float4 Out = (float4) 0.0f;
    
    if (tilesPS[In.Instance].isWall == false)
    {
        Out = greenOutline.Sample(pointSampler, In.UV);
    }
    else
    {
        Out = redTile.Sample(pointSampler, In.UV);
    }
    
    if (Out.a <= 0.0f)
        discard;
    
    return Out;

}