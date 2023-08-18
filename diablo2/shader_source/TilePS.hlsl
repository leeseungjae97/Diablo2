#include "global.hlsli"
RWStructuredBuffer<TileShared> TileSharedBuffer : register(u3);

struct GSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
};

float4 main(GSOut In) : SV_TARGET
{
    float4 Out = (float4) 0.0f;
    
    Out = albedoTexture.Sample(pointSampler, In.UV);
    
    float4 mousePos = TileSharedBuffer[0].mousePos;
    
    if (mousePos.x > 10)
        discard;
    
    //Out.a = alpha;
    
    if (Out.a <= 0.0f)
        discard;
    
    return Out;

}