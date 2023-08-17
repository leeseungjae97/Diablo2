#include "mTileSystem.h"
#include "mRenderer.h"
namespace m
{
	TileSystem::TileSystem()
	{
		std::shared_ptr<Mesh> mesh = RESOURCE_FIND(Mesh, L"RectMesh");
		std::shared_ptr<Material> material = RESOURCE_FIND(Material, L"greenOutlineTile");
		mCS = Resources::Find<TileComputeShader>(L"TileComputeShader");
	}

	TileSystem::~TileSystem()
	{
	}

	void TileSystem::Initialize()
	{
		
	}

	void TileSystem::Update()
	{
		MeshRenderer::Update();
	}

	void TileSystem::LateUpdate()
	{
		MeshRenderer::LateUpdate();
	}

	void TileSystem::Render()
	{
		MeshRenderer::Render();
	}
}
