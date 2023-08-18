#include "mTileComputeShader.h"

#include "mRenderer.h"
#include "mMouseManager.h"

#include "../Engine/mPlayerInfo.h"
#include "../Engine/mPlayer.h"


namespace m::graphics
{
	TileComputeShader::TileComputeShader()
		: ComputeShader(128, 1, 1)
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

		mGroupX = mTileBuffer->GetStride() / mThreadGroupCountX + 1;
		mGroupY = 1;
		mGroupZ = 1;
	}

	void TileComputeShader::Clear()
	{
		if(mTileBuffer)
			mTileBuffer->Clear();
		if(mSharedBuffer)
			mSharedBuffer->Clear();
	}

	void TileComputeShader::SetTileBuffer(StructedBuffer* tileBuffer)
	{
		mTileBuffer = tileBuffer;

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Tile];

		renderer::TileDataCB data = {};

		Vector3 mouseV3 = MouseManager::UnprojectionMousePos(1.f, mCamera);
		Vector4 mousePos = Vector4(mouseV3.x, mouseV3.y, mouseV3.z, 0.f);
		data.mousePos = mousePos;
		if(PlayerInfo::player)
		{
			Vector3 posV3 = GET_POS(PlayerInfo::player);
			Vector4 pos = Vector4(posV3.x, posV3.y, posV3.z, 0.f);
			data.playerPos = pos;
		}else
		{
			data.playerPos = Vector4(0.f, 0.f, 1.f, 0.f);
		}
			
		cb->SetData(&data);
		cb->Bind(eShaderStage::CS);
	}

	void TileComputeShader::OnExcute(ComputeTileCoord** data, int size)
	{

		ComputeShader::OnExcute();
		mSharedBuffer->GetData<ComputeTileCoord>(data, size);

		Clear();
	}
}
