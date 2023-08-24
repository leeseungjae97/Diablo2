#include "mPathFinderComputeShader.h"
namespace m::graphics
{
	PathFinderComputeShader::PathFinderComputeShader(int x, int y, int z)
		: ComputeShader(x, y, z)
		, mPathFinderTileBuffer(nullptr)
		, mCamera(nullptr)
	{
	}

	PathFinderComputeShader::PathFinderComputeShader()
		: ComputeShader(1, 1, 1)
		, mPathFinderTileBuffer(nullptr)
		, mCamera(nullptr)
	{
	}

	PathFinderComputeShader::~PathFinderComputeShader()
	{
	}

	void PathFinderComputeShader::Binds()
	{
		//if(nullptr != mPathFinderTileBuffer
		//	&& mPathFinderTileBuffer->buffer)
		//{
		//	mPathFinderTileBuffer->BindUAV(0);
		//}

		//mGroupX;
		//mGroupY;
		//mGroupZ;
	}

	void PathFinderComputeShader::Clear()
	{
		if (nullptr != mPathFinderTileBuffer
			&& mPathFinderTileBuffer->buffer)
		{
			mPathFinderTileBuffer->Clear();
		}
	}

	void PathFinderComputeShader::OnExcute()
	{
		//ComputeShader::OnExcute();

		//Clear();

		// GetData
	}
}
