#include "global.hlsli"
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
    
    if (uvControlType == 1)
    {
        if (In.UV.y < UVYCoord)
        {
            discard;
        }
        else
        {
            color = albedoTexture.Sample(pointSampler, In.UV);
        }
    }
    if (uvControlType == 2)
    {
        if (In.UV.x < 1.f - UVYCoord)
        {
            color = albedoTexture.Sample(pointSampler, In.UV);
        }
        else
        {
            discard;
        }
    }
    
    //float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);
    
    //for (int i = 0; i < 2; i++)
    //{
    //    CalculateLight2D(lightColor, In.WorldPos, i);
    //}
    
    //color *= lightColor;
    
    if(color.a <= 0.0f)
        discard;
    
    return color;
}