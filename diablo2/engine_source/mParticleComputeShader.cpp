#include "mParticleComputeShader.h"
#include "mRenderer.h"
#include "mTime.h"

namespace m::graphics
{
	ParticleComputeShader::ParticleComputeShader()
		: ComputeShader(128, 1, 1)
		, mParticleBuffer(nullptr)
	{
	}

	ParticleComputeShader::~ParticleComputeShader()
	{
	}

	void ParticleComputeShader::Binds()
	{
		mParticleBuffer->BindUAV(0);
		mSharedBuffer->BindUAV(1);

		mGroupX = mParticleBuffer->GetStride() / mThreadGroupCountX + 1;
		mGroupY = 1;
		mGroupZ = 1;
	}

	void ParticleComputeShader::Clear()
	{
		mParticleBuffer->Clear();
		mSharedBuffer->Clear();
	}

	void ParticleComputeShader::SetParticleBuffer(StructedBuffer* particleBuffer)
	{
		mParticleBuffer = particleBuffer;

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Particle];

		static float elapsedTime = 0.0f;
		elapsedTime += Time::fDeltaTime();

		renderer::ParticleSystemCB data = {};
		data.elementCount = mParticleBuffer->GetStride();
		data.elpasedTime = elapsedTime;
		data.deltaTime = Time::fDeltaTime();
		data.alpha = 1.f;

		cb->SetData(&data);
		cb->Bind(eShaderStage::CS);
	}
}