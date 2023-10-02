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

		void BindsMaterials();
		void ClearMaterials();
		void AddMaterial(std::shared_ptr<Material> mat);
		void SetComputedData();
		void WallChange();

		ComputedMonsterCoord* GetComputedMonsterCoord() { return mComputedCoords; }
	private:

		graphics::StructuredBuffer* mTileBuffer;
		graphics::StructuredBuffer* mTileSharedBuffer;
		graphics::StructuredBuffer* mComputedTileCoordBuffer;
		graphics::StructuredBuffer* mMonsterBuffer;
		graphics::StructuredBuffer* mGetMonsterComputedCoordBuffer;

		std::vector<ComputeTile> mTiles;
		std::shared_ptr<TileComputeShader> mCS;
		std::vector<std::shared_ptr<Material>> materials;

		ComputedTileCoord* mCoordData;
		ComputedMonsterCoord* mComputedCoords;
	};
}

