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
		, mSkillBuffer(nullptr)
		//, mCamera(nullptr)
	{
	}

	TileComputeShader::~TileComputeShader()
	{
		//mCamera = nullptr;
	}

	void TileComputeShader::Binds()
	{
		if (nullptr != mTileBuffer
			&&
			mTileBuffer->buffer)
		{
			mTileBuffer->BindUAV(0);
		}

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

		if(nullptr != mSkillBuffer
			&&
			mSkillBuffer->buffer)
			mSkillBuffer->BindUAV(5);

		//if (nullptr != mGSkillBuffer
		//	&&
		//	mGSkillBuffer->buffer)
		//	mGSkillBuffer->BindUAV(6);

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

		if (nullptr != mSkillBuffer
			&&
			mSkillBuffer->buffer)
			mSkillBuffer->Clear();

		//if (nullptr != mGSkillBuffer
		//	&&
		//	mGSkillBuffer->buffer)
		//	mGSkillBuffer->Clear();
	}

	void TileComputeShader::OnExcute(ComputedTileCoord** data, int size, ComputedMonsterCoord** data2, int size2
	    , SkillWallCollision** data3, int size3)
	{
		ComputeShader::OnExcute();

		if (nullptr != mTileCoordBuffer
		    && nullptr != mTileCoordBuffer->buffer)
		{
			mTileCoordBuffer->GetData<ComputedTileCoord>(data, size);
		}
		if (nullptr != mMonsterCoordBuffer->buffer
			&& nullptr != mMonsterBuffer->buffer
			&& nullptr != mMonsterCoordBuffer
			&& nullptr != mMonsterBuffer)
		{
			mMonsterCoordBuffer->GetData<ComputedMonsterCoord>(data2, size2);
		}
		//if(nullptr != mGSkillBuffer
		//	&& 
		//	nullptr != mSkillBuffer
		//	&& nullptr != mSkillBuffer->buffer
		//	&& nullptr != mGSkillBuffer->buffer)
		//{
		//	mGSkillBuffer->GetData<SkillWallCollision>(data3, size3);
		//}

		if (
			nullptr != mSkillBuffer
			&& nullptr != mSkillBuffer->buffer)
		{
			mSkillBuffer->GetData<SkillWallCollision>(data3, size3);
		}

		Clear();
		
	}
}
