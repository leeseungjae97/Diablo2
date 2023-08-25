#include "mPathFinderSystem.h"
namespace m
{
	PathFinderSystem::PathFinderSystem()
	{
		mCS = Resources::Find<PathFinderComputeShader>(L"PathFinderComputeShader");
	}

	PathFinderSystem::~PathFinderSystem()
	{
	}

	void PathFinderSystem::Initialize()
	{
		MeshRenderer::Initialize();
	}

	void PathFinderSystem::Update()
	{
		MeshRenderer::Update();
	}

	void PathFinderSystem::LateUpdate()
	{
		MeshRenderer::LateUpdate();
	}

	void PathFinderSystem::Render()
	{
		MeshRenderer::Render();
	}

	void PathFinderSystem::OpenVectorAdd(Tile* curTile)
	{
		// SetData
		// Tile
		// isWall
		// onMonster
		// inClose
		// G
		// H

		// SharedData
		// IsMonster
		// GetNextMoveCoord
		// GetMonsterNext


		// GetData
		// openVector 
	}
}
