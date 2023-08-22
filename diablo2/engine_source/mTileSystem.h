#pragma once
#include "mMeshRenderer.h"
#include "mStructedBuffer.h"
#include "mTileComputeShader.h"

namespace m
{
	class TileSystem :
		public MeshRenderer
	{
	public:
		TileSystem();
		virtual ~TileSystem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetComputedData();

		ComputedMonsterCoord* GetComputedMonsterCoord() { return mComputedCoords; }
	private:

		graphics::StructedBuffer* mBuffer;
		graphics::StructedBuffer* mSharedBuffer;
		graphics::StructedBuffer* mTileCoordBuffer;
		graphics::StructedBuffer* mMonsterBuffer;
		graphics::StructedBuffer* mMonsterCoordBuffer;

		std::shared_ptr<TileComputeShader> mCS;

		ComputedTileCoord* mCoordData;
		//std::vector<ComputedMonsterCoord> mComputedCoords;
		ComputedMonsterCoord* mComputedCoords;
	};
}

