#pragma once
#include "mMeshRenderer.h"
#include "mStructedBuffer.h"
#include "mParticleComputeShader.h"

namespace m
{
	class ParticleSystem : public MeshRenderer
	{
	public:
		ParticleSystem();
		virtual ~ParticleSystem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		graphics::StructuredBuffer* mBuffer;
		graphics::StructuredBuffer* mSharedBuffer;
		std::shared_ptr<ParticleComputeShader> mCS;

		UINT    mCount;
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float   mLifeTime;
		float	mFrequency;

		float mTime;
	};
}
