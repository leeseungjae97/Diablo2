#include "global.hlsli"

//structedBuffer
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


VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    
    //In.Pos.x += SpriteOffsetOfCenterPos.x;
    //In.Pos.y += SpriteOffsetOfCenterPos.y;
    
    float4 world = mul(float4(In.Pos, 1.0f), mWorld);
    float4 view = mul(world, mView);
    float4 proj = mul(view, mProjection);
    
    Out.Pos = proj;
    Out.WorldPos = world.xyz;
    Out.Color = In.Color;
    Out.UV = In.UV;

    return Out;
}