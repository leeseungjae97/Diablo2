#include "global.hlsli"
struct VSIn
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    
    float4 world = mul(float4(In.Pos), mWorld);
    float4 view = mul(float4(world), mView);
    float4 proj = mul(float4(view), mProjection);
    
    Out.Pos = proj;
    Out.Color = In.Color;
    Out.UV = In.UV;

    return Out;
}