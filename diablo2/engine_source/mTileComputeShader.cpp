#include "mTileComputeShader.h"

#include "mRenderer.h"
#include "mMouseManager.h"

#include "../Engine/mPlayerInfo.h"
#include "../Engine/mPlayer.h"


namespace m::graphics
{
	TileComputeShader::TileComputeShader()
		: ComputeShader(1024, 1, 1)
		, mTileBuffer(nullptr)
		, mSharedBuffer(nullptr)
		, mCamera(nullptr)
	{
	}

	TileComputeShader::~TileComputeShader()
	{
	}

	void TileComputeShader::Binds()
	{
		if (mTileBuffer)
			mTileBuffer->BindUAV(0);
		if (mSharedBuffer)
			mSharedBuffer->BindUAV(1);
		if (mTileCoordBuffer)
			mTileCoordBuffer->BindUAV(2);
		if (mMonsterBuffer)
			mMonsterBuffer->BindUAV(3);

		mGroupX = 1024;
		mGroupY = 1;
		mGroupZ = 1;
	}

	void TileComputeShader::Clear()
	{
		if(mTileBuffer)
			mTileBuffer->Clear();
		if(mSharedBuffer)
			mSharedBuffer->Clear();
		if (mTileCoordBuffer)
			mTileCoordBuffer->Clear();
		if (mMonsterBuffer)
			mMonsterBuffer->Clear();
	}

	void TileComputeShader::OnExcute(ComputeTileCoord** data, int size)
	{
		ComputeShader::OnExcute();
		mTileCoordBuffer->GetData<ComputeTileCoord>(data, size);

		Clear();
	}
}
