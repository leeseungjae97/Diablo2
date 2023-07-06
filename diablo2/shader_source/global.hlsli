cbuffer Transform : register(b0)
{
    //float4 Pos;
    row_major matrix mWorld;
    row_major matrix mView;
    row_major matrix mProjection;
}
cbuffer Grid : register(b2)
{
    float4 CameraPosition;
    float2 CameraScale;
    float2 Resolution;
}
Texture2D albedoTexture : register(t0);
SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);