#include "global.hlsli"
StructuredBuffer<SpriteAlpha> spriteAlpha : register(t22);

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};


float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;

    color = albedoTexture.Sample(pointSampler, In.UV);
    
    float4 lightColor = float4(0.05f, 0.05f, 0.05f, 1.0f);
    for (int i = 0; i < lightsAttribute[0].size; i++)
    {
        CalculateLight2D(lightColor, In.WorldPos, i);
    }
    
    color.xyz *= lightColor.xyz;
    
    color.a *= spriteAlpha[0].alpha;

    if (color.r > 1.f)
        color.r = 1.f;
    
    if (color.g > 1.f)
        color.g = 1.f;
    
    if (color.b > 1.f)
        color.b = 1.f;
    
    if (color.a > 1.f)
        color.a = 1.f;
    
    
    if (color.a <= 0.0f)
        discard;
    
    return color;
}