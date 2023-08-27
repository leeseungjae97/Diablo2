#include "global.hlsli"
StructuredBuffer<TrappingColor> colorBuffer : register(t20);
StructuredBuffer<float4> textureBuffer : register(t21);
struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;

    color = albedoTexture.Sample(pointSampler, In.UV);

    float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.f);
    if (colorBuffer[0].color.w > 0.0f)
    {
        lightColor += colorBuffer[0].color;
        color *= lightColor;
        //color *= colorBuffer[0].color;
    }
    
    
    if (color.a <= 0.0f)
        discard;
    
    return color;
}