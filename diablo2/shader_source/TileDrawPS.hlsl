#include "global.hlsli"
//Texture2D<float4> noneTile : register(t0);
//Texture2D<float4> greenTile : register(t1);

struct GSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    uint Instance : SV_InstanceID;
};
float4 main(GSOut In) : SV_TARGET
{
    float4 Out = (float4) 0.f;
    
    Out = albedoTexture.Sample(pointSampler, In.UV);
    
    if(Out.a <= 0.0f)
        discard;
    
    return Out;
}