#include "global.hlsli"
RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);

[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    //if (elementCount <= DTid.x)
    //    return;
    
    //particles[DTid.x].speed = 0.f;
    //albedoTexture.GetDimensions();
    //uint2 texDimensions = albedoTexture.GetDimensions();
        //uint2 pixelPos = uint2(DTid.x, DTid.y);
        //float4 texel = atlasTexture.Load(int3(pixelPos, 0));
        //texel.a = 0.5;
        //atlasTexture[pixelPos] = texel;

    float4 vRandom = (float4) 0.f;
    if (ParticleBuffer[DTid.x].active == 0)
    {
        while (0 < ParticleSharedBuffer[0].ActiveSharedCount)
        {
            
            int origin = ParticleSharedBuffer[0].ActiveSharedCount;
            int exchange = origin - 1;
            
            // 쓰레드 동기화 Interlock 관련 함수
            //InterlockedExchange(ParticleSharedBuffer[0].ActiveSharedCount
            //    , exchange, exchange);
            InterlockedCompareExchange(ParticleSharedBuffer[0].ActiveSharedCount
                , origin, exchange, exchange);
            
            if (origin == exchange)
            {
                ParticleBuffer[DTid.x].active = 1;
                break;
            }
            
        }
        if (ParticleBuffer[DTid.x].active == 1)
        {
            // 랜덤값으로 위치와 방향을 설정한다.
            // 샘플링을 시도할 UV 를 계산한다.
            float2 vUV = float2((float) DTid.x / elementCount, 0.5f);


            vUV.y += sin((vUV.x + deltaTime) * 3.141592f + 2.f * 10.f) * 0.5f;
            //vRandom = float4
            //(
            //      GaussianBlur(vUV + float2(0.f, 0.f)).x
            //    , GaussianBlur(vUV + float2(-deltaTime * 10.f, 0.f)).x
            //    , GaussianBlur(vUV + float2(-deltaTime * 20.f, 0.f)).x
            //    , GaussianBlur(vUV + float2(-deltaTime * 30.f, 0.f)).x
            //);
            float fTheta = cos(ParticleBuffer[DTid.x].alpha) * 3.14f;
            float fThetay = sin(ParticleBuffer[DTid.x].alpha2) * 3.14f;
            //vUV.x += vRandom.y;
            //vUV.y += vRandom.z;
            //ParticleBuffer[DTid.x].position.x = ParticleBuffer[DTid.x].alpha;
            
            //ParticleBuffer[DTid.x].position.y = 0.f;
            
            ParticleBuffer[DTid.x].position.x = ParticleBuffer[DTid.x].alpha2 * ParticleBuffer[DTid.x].alpha3;
            ParticleBuffer[DTid.x].position.y = ParticleBuffer[DTid.x].alpha * ParticleBuffer[DTid.x].alpha3;
            
            ParticleBuffer[DTid.x].direction.x = ParticleBuffer[DTid.x].alpha;
            ParticleBuffer[DTid.x].direction.y = ParticleBuffer[DTid.x].alpha2;
            ParticleBuffer[DTid.x].speed = vRandom.x * 1000.f;
            //ParticleBuffer[DTid.x].direction.x -= ParticleBuffer[DTid.x].alpha;
            //ParticleBuffer[DTid.x].direction.y -= ParticleBuffer[DTid.x].alpha;
            //ParticleBuffer[DTid.x].position.xyz =0.f;
            
            //ParticleBuffer[DTid.x].position.x -= 0.65f;
            //ParticleBuffer[DTid.x].position.y -= 1.4f;
            ParticleBuffer[DTid.x].position.z = 0.0f;
        }
    }
    else
    {
        //ParticleBuffer[DTid.x].alpha = 0.0f;
        float2 vUV = float2((float) DTid.x / elementCount, 0.5f);
        //vRandom = float4
        //(
        //      GaussianBlur(vUV + float2(elapsedTime, elapsedTime)).x
        //    , GaussianBlur(vUV + float2(elapsedTime, elapsedTime)).x
        //    , GaussianBlur(vUV + float2(elapsedTime, elapsedTime)).x
        //    , GaussianBlur(vUV + float2(elapsedTime, elapsedTime)).x
        //);
        //ParticleSharedBuffer[0].
        //ParticleBuffer[DTid.x].
        //ParticleBuffer[DTid.x].direction = float4(vRandom.x, 0.f, 1.f, 1.f);

        ParticleBuffer[DTid.x].position += ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * deltaTime;

        //ParticleBuffer[DTid.x].position.xyz += vRandom.xyz;
        //ParticleBuffer[DTid.xy] = float4(1.f, 0.f, 0.f, 1.f);
    }
}