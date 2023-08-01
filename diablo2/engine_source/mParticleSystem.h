#pragma once
#include "mMeshRenderer.h"
#include "mStructedBuffer.h"

namespace m
{
	class ParticleSystem : public MeshRenderer
	{
	public:
		ParticleSystem();
		~ParticleSystem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		graphics::StructedBuffer* mBuffer;

		UINT    mCount;
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float   mLifeTime;
	};
}
