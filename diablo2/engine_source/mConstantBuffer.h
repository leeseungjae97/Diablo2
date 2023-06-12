#pragma once
#include "mGraphics.h"
namespace m::graphics
{
	class ConstantBuffer : public GpuBuffer
	{
	public:
		ConstantBuffer(const eCBType type);
		~ConstantBuffer();

		bool Create(size_t size);
		void SetData(void* data);
		void Bind(eShaderStage stage);

		void SetProjectionMatrix(XMMATRIX matrix) { mProjectionMatrix = matrix; }
		void SetView(XMMATRIX view, Vector3 pos) { 
			mView = view;
			mView *= Matrix::CreateTranslation(-pos);
		}
	private:
		const eCBType mType;
		XMMATRIX mProjectionMatrix;
		XMMATRIX mView;

	};

}


