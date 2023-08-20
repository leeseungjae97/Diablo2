cbuffer Transform : register(b0)
{
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
cbuffer Animator : register(b3)
{
    float2 SpriteLeftTop;
    float2 SpriteSize;
    float2 SpriteOffset;
    float2 AtlasSize;
    uint animationType;
    float mAlpha;
}
cbuffer UVControl : register(b4)
{
    float UVYCoord;
    uint uvControlType;
}
cbuffer ParticleSystem : register(b5)
{
    uint elementCount;
    float elapsedTime;
    float deltaTime;
    float alpha;
    int padd2;
}
cbuffer Noise : register(b6)
{
    float4 noiseTextureSize;
}
struct TileCoord
{
    float2 mouseHoverTileCoord;
    float2 playerStandTileCoord;
};
struct Tile
{
    float4 tilePosition;
    float2 tileSize;
    float2 tileCoord;
};
struct TileShared
{
    float4 mousePos;
    float4 playerPos;
    uint tileCount;
    uint monsterCount;
    bool hoverUI;
};
struct Monster
{
    float4 monsterPos;
    uint monsterCount;
};
struct MonsterCoord
{
    float2 monsterCoord;
};
struct ParticleShared
{
    uint ActiveSharedCount;
};
struct LightAttribute
{
    float4 color;
    float4 position;
    float4 direction;
    
    uint type;
    float radius;
    float angle;
    int pad;
};
struct Particle
{
    float4 position;
    float4 direction;
    
    float alpha;
    float alpha2;
    float alpha3;
    float endTime;
    float time;
    float speed;
    uint active;
};


StructuredBuffer<Tile> tiles : register(t11);
StructuredBuffer<LightAttribute> lightsAttribute : register(t13);
StructuredBuffer<Particle> particles : register(t14);

Texture2D albedoTexture : register(t0);
Texture2D atlasTexture : register(t12);
Texture2D noiseTexture : register(t15);

SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);

static float GaussianFilter[5][5] =
{
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.0219f, 0.0983f, 0.1621f, 0.0983f, 0.0219f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
};

float4 GaussianBlur(float2 UV)
{
    float4 Out = (float4) 0.0f;
    
    if (1.f < UV.x)
        UV.x = frac(UV.x);
    else if (UV.x < 0.0f)
        UV.x = 1.0f + frac(UV.x);
        
    if (1.f < UV.y)
        UV.y = frac(UV.y);
    else if (UV.y < 0.0f)
        UV.y = 1.0f + frac(UV.y);
    
    int2 iUV = UV * noiseTextureSize.xy;
    iUV -= int2(2, 2);
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int2 idx = int2(iUV.y + i, iUV.x + j);
            Out += noiseTexture[idx] * GaussianFilter[i][j];
        }
    }
    
    return Out;
}

void CalculateLight2D(in out float4 lightColor, float3 position, int idx)
{
    if (0 == lightsAttribute[idx].type)
    {
        lightColor += lightsAttribute[idx].color;
    }
    else if (1 == lightsAttribute[idx].type)
    {
        float length = distance(position.xy, lightsAttribute[idx].position.xy);
        
        if (length < lightsAttribute[idx].radius)
        {
            float ratio = 1.0f - (length / lightsAttribute[idx].radius);
            lightColor += lightsAttribute[idx].color * ratio;
        }
    }
    else
    {
        
    }
}

bool PointIntersectRhombus(float2 pos, float2 scale, float2 otherPos)
{
    float2 vertex[4];
    float gradient[4];
    float intercept[4];
    
    float2 direct[4] =
    {
        { -(scale.x / 2.f), 0 },
        { 0, -(scale.y / 2.f) },
        { (scale.x / 2.f), 0 },
        { 0, (scale.y / 2.f) }
    };
    
    for (uint i = 0; i < 4; ++i)
    {
        vertex[i].x = pos.x + direct[i].x;
        vertex[i].y = pos.y + direct[i].y;
    }
    for (uint i = 0; i < 4; ++i)
    {
        gradient[i] = ((vertex[i].y - vertex[(i + 1) % 4].y) / (vertex[i].x - vertex[(i + 1) % 4].x));
        intercept[i] = vertex[i].y - gradient[i] * vertex[i].x;
    }
    float _y = otherPos.y;
    float _x = otherPos.x;

    if (gradient[0] * _x + intercept[0] < _y
        && gradient[1] * _x + intercept[1] < _y
        && gradient[2] * _x + intercept[2] > _y
        && gradient[3] * _x + intercept[3] > _y)
    {
        return true;
    }
    else
        return false;
}