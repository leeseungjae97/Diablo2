#include "mTileComputeShader.h"

#include "mRenderer.h"

#include "../Engine/mPlayer.h"


namespace m::graphics
{
	TileComputeShader::TileComputeShader()
		: ComputeShader(1000, 1, 1)
		, mTileBuffer(nullptr)
		, mSharedBuffer(nullptr)
		, mTileCoordBuffer(nullptr)
		, mMonsterBuffer(nullptr)
		, mMonsterCoordBuffer(nullptr)
		, mCamera(nullptr)
	{
	}

	TileComputeShader::~TileComputeShader()
	{
		mCamera = nullptr;
	}

	void TileComputeShader::Binds()
	{
		if (nullptr != mTileBuffer
			&&
			mTileBuffer->buffer)
			mTileBuffer->BindUAV(0);

		if (nullptr != mSharedBuffer
			&&
			mSharedBuffer->buffer)
			mSharedBuffer->BindUAV(1);

		if (nullptr != mTileCoordBuffer
			&&
			mTileCoordBuffer->buffer)
			mTileCoordBuffer->BindUAV(2);

		if (nullptr != mMonsterBuffer
			&&
			mMonsterBuffer->buffer)
			mMonsterBuffer->BindUAV(3);

		if (nullptr != mMonsterCoordBuffer
			&&
			mMonsterCoordBuffer->buffer)
			mMonsterCoordBuffer->BindUAV(4);

		mGroupX = 1000;
		mGroupY = 1;
		mGroupZ = 1;
	}

	void TileComputeShader::Clear()
	{
		if (nullptr != mTileBuffer
			&&
			mTileBuffer->buffer)
			mTileBuffer->Clear();

		if (nullptr != mSharedBuffer
			&&
			mSharedBuffer->buffer)
			mSharedBuffer->Clear();

		if (nullptr != mTileCoordBuffer
			&&
			mTileCoordBuffer->buffer)
			mTileCoordBuffer->Clear();

		if (nullptr != mMonsterBuffer
			&&
			mMonsterBuffer->buffer)
			mMonsterBuffer->Clear();

		if (nullptr != mMonsterCoordBuffer
			&&
			mMonsterCoordBuffer->buffer)
			mMonsterCoordBuffer->Clear();
	}

	//void TileComputeShader::OnExcute(ComputedTileCoord** data, int size, ComputedMonsterCoord* data2, int size2)
	void TileComputeShader::OnExcute(ComputedTileCoord** data, int size, ComputedMonsterCoord** data2, int size2)
	{
		ComputeShader::OnExcute();

		Clear();


		mTileCoordBuffer->GetData<ComputedTileCoord>(data, size);
		//if (nullptr != mGetMonsterComputedCoordBuffer && nullptr != mMonsterBuffer)
		//	mGetMonsterComputedCoordBuffer->GetData<ComputedMonsterCoord>(data2, size2);
		if(nullptr != mMonsterCoordBuffer && nullptr != mMonsterBuffer)
			mMonsterCoordBuffer->GetData<ComputedMonsterCoord>(data2, size2);
		
	}
}
