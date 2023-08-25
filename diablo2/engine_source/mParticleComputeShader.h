#pragma once
#include "mComputeShader.h"

namespace m::graphics
{
    class ParticleComputeShader :
        public ComputeShader
    {
	public:
		ParticleComputeShader();
		virtual ~ParticleComputeShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetParticleBuffer(StructuredBuffer* particleBuffer);
		void SetSharedBuffer(StructuredBuffer* sharedBuffer) { mSharedBuffer = sharedBuffer; }
	private:
		StructuredBuffer* mParticleBuffer;
		StructuredBuffer* mSharedBuffer;
    };
}

