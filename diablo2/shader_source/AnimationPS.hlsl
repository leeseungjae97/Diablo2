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
    
    float4 lightColor = float4(0.05f, 0.05f, 0.05f, 1.0f);
    //float4 lightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    for (int i = 0; i < lightsAttribute[0].size; i++)
    {
        CalculateLight2D(lightColor, In.WorldPos, i);
    }
    
    if (lightColor.r > 1.f)
        lightColor.r = 1.f;
    
    if (lightColor.g > 1.f)
        lightColor.g = 1.f;
    
    if (lightColor.b > 1.f)
        lightColor.b = 1.f;
    
    if (lightColor.a > 1.f)
        lightColor.a = 1.f;
    
    if (colorBuffer[0].color.w > 0.0f)
    {
        lightColor += colorBuffer[0].color;
    }
    
    color *= lightColor;
    
    if (mAlpha > 0.0f)
        color.a *= mAlpha;
    
    if(color.a <= 0.0f)
        discard;
    
    return color;
}