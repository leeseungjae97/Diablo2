#include "global.hlsli"
StructuredBuffer<DrawObject> drawObjectsBuffer : register(t20);

struct VSOut
{
    float4 LocalPos : SV_Position;
    uint Instance : SV_InstanceID;
};

struct GSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    uint Instance : SV_InstanceID;
};

[maxvertexcount(6)]
void main(point VSOut In[1], inout TriangleStream<GSOut> output)
{
    GSOut Out[4] = { (GSOut) 0.0f, (GSOut) 0.0f, (GSOut) 0.0f, (GSOut) 0.0f };
    
    float3 worldPos = (In[0].LocalPos.xyz)
                    + drawObjectsBuffer[In[0].Instance].position.xyz;
    
    float3 viewPos = mul(float4(worldPos, 1.0f), mView).xyz;
    
    float3 NewPos[4] =
    {
        viewPos - float3(-0.5f * drawObjectsBuffer[In[0].Instance].size.x, 0.5f * drawObjectsBuffer[In[0].Instance].size.y, 0.f),
        viewPos - float3(0.5f * drawObjectsBuffer[In[0].Instance].size.x, 0.5f * drawObjectsBuffer[In[0].Instance].size.y, 0.f),
        viewPos - float3(0.5f * drawObjectsBuffer[In[0].Instance].size.x, -0.5f * drawObjectsBuffer[In[0].Instance].size.y, 0.f),
        viewPos - float3(-0.5f * drawObjectsBuffer[In[0].Instance].size.x, -0.5f * drawObjectsBuffer[In[0].Instance].size.y, 0.f)
    };
    for (int i = 0; i < 4; ++i)
    {
        Out[i].Pos = mul(float4(NewPos[i], 1.0f), mProjection);
    }
    
    Out[0].UV = float2(0.0f, 0.0f);
    Out[1].UV = float2(1.0f, 0.0f);
    Out[2].UV = float2(1.0f, 1.0f);
    Out[3].UV = float2(0.0f, 1.0f);
    
    Out[0].Instance = In[0].Instance;
    Out[1].Instance = In[0].Instance;
    Out[2].Instance = In[0].Instance;
    Out[3].Instance = In[0].Instance;
    
    output.Append(Out[0]);
    output.Append(Out[1]);
    output.Append(Out[2]);
    output.RestartStrip();

    output.Append(Out[0]);
    output.Append(Out[2]);
    output.Append(Out[3]);
    output.RestartStrip();
}