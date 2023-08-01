#pragma once
#include "mComputeShader.h"
namespace m::graphics
{
    class PaintShader :
        public ComputeShader
    {
	public:
		virtual void Binds() override;
		virtual void Clear() override;

		void SetTarget(std::shared_ptr<class Texture> target) { mTarget = target; }

	private:
		std::shared_ptr<class Texture> mTarget;
	};
}

