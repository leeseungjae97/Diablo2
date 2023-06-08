#include "mConstantBuffer.h"
#include "mGraphicDevice_DX11.h"

namespace m::graphics
{
	ConstantBuffer::ConstantBuffer(const eCBType type)
		: GpuBuffer()
		, mType(type)
	{

	}

	ConstantBuffer::~ConstantBuffer()
	{}

	bool ConstantBuffer::Create(size_t size)
	{
		desc.ByteWidth = size;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		m::graphics::GetDevice()->CreateBuffer(buffer.GetAddressOf(), &desc, nullptr);

		return false;
	}

	void ConstantBuffer::SetData(void* data)
	{
		m::graphics::GetDevice()->SetConstantBuffer(buffer.Get(), data, desc.ByteWidth);
	}

	void ConstantBuffer::Bind(eShaderStage stage)
	{
		m::graphics::GetDevice()->BindConstantBuffer(stage, mType, buffer.Get());
	}
}