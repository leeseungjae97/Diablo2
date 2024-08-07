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
    
    if (animationType == 1)
    {
        float2 diff = (AtlasSize - SpriteSize) / 2.0f;
        float2 UV = (SpriteLeftTop - diff - SpriteOffset)
                + (AtlasSize * In.UV);

        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
            || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;

        color = atlasTexture.Sample(pointSampler, UV);
    }
    
    float4 lightColor = float4(0.f, 0.f, 0.f, 0.8f);
    //float4 lightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    //if (colorBuffer[0].color.w > 0.0f)
    //{
    //    lightColor += colorBuffer[0].color;
    //}
    
    color *= lightColor;
    
    if (mAlpha > 0.0f)
        color.a *= mAlpha;
    
    if (color.a <= 0.0f)
        discard;
    
    return color;
}