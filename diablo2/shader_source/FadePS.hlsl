#include "global.hlsli"
StructuredBuffer<TrappingColor> colorBuffer : register(t20);

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
    
    color.a = colorBuffer[0].color.w;
    
    if (color.a <= 0.0f)
        discard;
    
    return color;
}