#include "mTileDrawSystem.h"
namespace m
{
	TileDrawSystem::TileDrawSystem()
		: mPathTileBuffer(nullptr)
		, mSharedBuffer(nullptr)
		, mTileSize(0)
	{
		std::shared_ptr<Mesh> mesh = RESOURCE_FIND(Mesh, L"PointMesh");

		//std::shared_ptr<Material> nonMaterial = RESOURCE_FIND(Material, L"noneRectTileDrawShader");
		std::shared_ptr<Material> material = RESOURCE_FIND(Material, L"greenTileDTileDrawShader");
		
		SetMesh(mesh);
		SetMaterial(material);

		mPathTileBuffer = new graphics::StructuredBuffer();

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

	void TileDrawSystem::Update()
	{
		MeshRenderer::Update();
		//mCS->SetCamera(GetOwner()->GetCamera());
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
		ComputeTile* computeTiles = new ComputeTile[pathtiles.size()];
		for (int i = 0; i < pathtiles.size(); ++i)
		{
			Vector3 posV3 = GET_POS(pathtiles[i]);
			Vector4 pos = Vector4(posV3.x, posV3.y, posV3.z, 0.f);
			computeTiles[i].tilePosition = pos;
			computeTiles[i].tileSize = GET_VEC2_F_VEC3_D(GET_SCALE(pathtiles[i]));
			computeTiles[i].isWall = false;
			computeTiles[i].tileCoord = pathtiles[i]->GetCoord();
		}
		
		mPathTileBuffer->Create(sizeof(ComputeTile), pathtiles.size(), eViewType::UAV, computeTiles, true);
		
		delete[] computeTiles;

		//mCS->SetPathTileBuffer(mPathTileBuffer);
		//mCS->OnExcute();
	}
}
