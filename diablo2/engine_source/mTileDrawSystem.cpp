#include "mTileDrawSystem.h"
namespace m
{
	TileDrawSystem::TileDrawSystem()
		:mBuffer(nullptr)
		, mSharedBuffer(nullptr)
	{
		std::shared_ptr<Mesh> mesh = RESOURCE_FIND(Mesh, L"PointMesh");
		std::shared_ptr<Material> material = RESOURCE_FIND(Material, L"noneRect");
		SetMesh(mesh);
		SetMaterial(material);
	}

	TileDrawSystem::~TileDrawSystem()
	{
	}

	void TileDrawSystem::Initialize()
	{
		MeshRenderer::Initialize();
	}

	void TileDrawSystem::Update()
	{
		MeshRenderer::Update();
	}

	void TileDrawSystem::LateUpdate()
	{
		MeshRenderer::LateUpdate();
	}

	void TileDrawSystem::Render()
	{
		MeshRenderer::Render();
	}
}
