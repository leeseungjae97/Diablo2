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

		void SetParticleBuffer(StructedBuffer* particleBuffer);
		void SetSharedBuffer(StructedBuffer* sharedBuffer) { mSharedBuffer = sharedBuffer; }
	private:
		StructedBuffer* mParticleBuffer;
		StructedBuffer* mSharedBuffer;
    };
}

