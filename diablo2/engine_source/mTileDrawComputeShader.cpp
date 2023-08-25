#include "mTileDrawComputeShader.h"
namespace m
{
	graphics::TileDrawComputeShader::TileDrawComputeShader()
		: ComputeShader()
		, mPathTileBuffer(nullptr)
	{
	}

	graphics::TileDrawComputeShader::TileDrawComputeShader(int x, int y, int z)
		: ComputeShader(x, y, z)
		, mPathTileBuffer(nullptr)
	{
	}

	graphics::TileDrawComputeShader::~TileDrawComputeShader()
	{
	}

	void graphics::TileDrawComputeShader::Binds()
	{
		ComputeShader::Binds();
		if(mPathTileBuffer
			&& mPathTileBuffer->buffer)
		{
			mPathTileBuffer->BindSRV(eShaderStage::PS, 0);
		}
	}

	void graphics::TileDrawComputeShader::Clear()
	{
		ComputeShader::Clear();
		if (mPathTileBuffer
			&& mPathTileBuffer->buffer)
			mPathTileBuffer->Clear();
	}

	void graphics::TileDrawComputeShader::OnExcute()
	{
		ComputeShader::OnExcute();
	}
}
