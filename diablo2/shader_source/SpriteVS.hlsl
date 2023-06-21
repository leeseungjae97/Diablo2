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

cbuffer Transform : register(b0)
{
    //float4 Pos;
    row_major matrix mWorld;
    row_major matrix mView;
    row_major matrix mProjection;
}

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    //Out.Pos = float4(In.Pos, 1.0f);
    //Out.Pos.x += Pos.x;
    //Out.Pos.y += Pos.y;
    
    float4 world = mul(float4(In.Pos, 1.0f), mWorld);
    Out.Pos = world;
    Out.UV = In.UV;
    Out.Color = In.Color;

    return Out;
}