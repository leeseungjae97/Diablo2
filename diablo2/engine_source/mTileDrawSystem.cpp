#include "mTileDrawSystem.h"

#include "mTileDrawManager.h"

namespace m
{
	TileDrawSystem::TileDrawSystem()
		: mPathTileBuffer(nullptr)
		, mSharedBuffer(nullptr)
		, mTileSize(10000)
	{
		std::shared_ptr<Mesh> mesh = RESOURCE_FIND(Mesh, L"PointMesh");

		//std::shared_ptr<Material> nonMaterial = RESOURCE_FIND(Material, L"noneRectTileDrawShader");
		std::shared_ptr<Material> material = RESOURCE_FIND(Material, L"greenTileDTileDrawShader");
		
		SetMesh(mesh);
		SetMaterial(material);

		mPathTileBuffer = new graphics::StructuredBuffer();
		mPathTileBuffer->Create(sizeof(ComputeTile), 1, eViewType::UAV, nullptr, true);
		//mCS = Resources::Find<TileDrawComputeShader>(L"TileDrawComputeShader");
		//mSharedBuffer;
	}

	TileDrawSystem::~TileDrawSystem()
	{
		if(mPathTileBuffer)
		{
			delete mPathTileBuffer;
			mPathTileBuffer = nullptr;
		}
	}

	void TileDrawSystem::Initialize()
	{
		MeshRenderer::Initialize();
	}
	void TileDrawSystem::Release()
	{
		std::shared_ptr<Material> nonMaterial = RESOURCE_FIND(Material, L"noneRectTileDrawShader");
		SetMaterial(nonMaterial);
	}
	void TileDrawSystem::Update()
	{
		MeshRenderer::Update();
		if (TileDrawManager::bDrawTile)
		{
			std::shared_ptr<Material> material = RESOURCE_FIND(Material, L"greenTileDTileDrawShader");
			SetMaterial(material);
		}else
		{
			std::shared_ptr<Material> nonMaterial = RESOURCE_FIND(Material, L"noneRectTileDrawShader");
			SetMaterial(nonMaterial);
		}
	}

	void TileDrawSystem::LateUpdate()
	{
		MeshRenderer::LateUpdate();
	}

	void TileDrawSystem::Render()
	{
		//MeshRenderer::Render();

		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		mPathTileBuffer->BindSRV(eShaderStage::VS, 16);
		mPathTileBuffer->BindSRV(eShaderStage::GS, 16);
		mPathTileBuffer->BindSRV(eShaderStage::PS, 16);

		GetMesh()->BindBuffer();
		GetMaterial()->Binds();
		GetMesh()->RenderInstanced(mTileSize);

		mPathTileBuffer->Clear();
	}

	void TileDrawSystem::MakePathTileBuffer(std::vector<Tile*> pathtiles)
	{
		//Update call

		mTileSize = pathtiles.size();
		std::vector<ComputeTile> computeTiles;
		//ComputeTile* computeTiles = new ComputeTile[pathtiles.size()];
		for (int i = 0; i < pathtiles.size(); ++i)
		{
			ComputeTile tile;
			Vector3 posV3 = pathtiles[i]->GetPos();
			Vector4 pos = Vector4(posV3.x, posV3.y, posV3.z, 0.f);
			tile.tilePosition = pos;
			tile.tileSize = GET_VEC2_F_VEC3_D(pathtiles[i]->GetScale());
			tile.isWall = false;
			tile.tileCoord = pathtiles[i]->GetCoord();

			computeTiles.push_back(tile);
		}
		
		//mPathTileBuffer->Create(sizeof(ComputeTile), pathtiles.size(), eViewType::UAV, computeTiles.data(), true);
		mPathTileBuffer->SetData(computeTiles.data(), computeTiles.size());
		
		//delete[] computeTiles;

		//mCS->SetPathTileBuffer(mPathTileBuffer);
		//mCS->OnExcute();
	}
}
