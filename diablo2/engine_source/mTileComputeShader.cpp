#include "mTileComputeShader.h"

#include "mRenderer.h"

namespace m::graphics
{
	TileComputeShader::TileComputeShader()
		: ComputeShader(100, 100, 1)
		, mTileBuffer(nullptr)
		, mSharedBuffer(nullptr)
	{
	}

	TileComputeShader::~TileComputeShader()
	{
		mTileBuffer->BindUAV(0);
		mSharedBuffer->BindUAV(1);

		mGroupX = mTileBuffer->GetStride() / mThreadGroupCountX;
		mGroupY = 100;
		mGroupZ = 1;
	}

	void TileComputeShader::Binds()
	{
	}

	void TileComputeShader::Clear()
	{
		mTileBuffer->Clear();
		mSharedBuffer->Clear();

	}

	void TileComputeShader::SetTileBuffer(StructedBuffer* tileBuffer)
	{
		mTileBuffer = tileBuffer;

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Tile];

		//renderer::Tile
		
	}
}
