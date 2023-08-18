#include "mTileSystem.h"

#include "mTileManager.h"
#include "mRenderer.h"
#include "mMouseManager.h"

#include "../Engine/mPlayerInfo.h"
#include "../Engine/mPlayer.h"
namespace m
{
	TileSystem::TileSystem()
		: mBuffer(nullptr)
		, mSharedBuffer(nullptr)
		, mCoordData(new ComputeTileCoord())
	{
		std::shared_ptr<Mesh> mesh = RESOURCE_FIND(Mesh, L"PointMesh");
		SetMesh(mesh);
		std::shared_ptr<Material> material = RESOURCE_FIND(Material, L"greenOutlineTileD");
		SetMaterial(material);

		mCS = Resources::Find<TileComputeShader>(L"TileComputeShader");

		ComputeTile computeTiles[100][100] = {};
		for (int y = 0; y < 100; ++y)
		{
			for (int x = 0; x < 100; ++x)
			{
				Vector3 posV3 = GET_POS(TileManager::pathFindingTiles[y][x]);
				Vector4 pos = Vector4(posV3.x, posV3.y, posV3.z, 0.f);
				//if(posV3.x == -591.f && posV3.y == -203.f)
				//{
				//	int a = 0;
				//}
				computeTiles[y][x].tilePosition = pos;
				computeTiles[y][x].tileSize = GET_VEC2_F_VEC3_D(GET_SCALE(TileManager::pathFindingTiles[y][x]));
				computeTiles[y][x].tileCoord = Vector2(x, y);
			}
		}
		//ComputeTile llo[2] = {};
		//llo[0].tilePosition = Vector4(0.f, 0.f, 1.f, 0.f);
		//llo[0].tileSize = Vector2(0.f, 0.f);
		//llo[1].tilePosition = Vector4(2.f, 2.f, 1.f, 0.f);
		//llo[1].tileSize = Vector2(0.f, 0.f);
		//tile.size
		mBuffer = new graphics::StructedBuffer();
		//mBuffer->Create(sizeof(ComputeTile), 10000, eViewType::UAV, computeTiles, true);
		mBuffer->Create(sizeof(ComputeTile), 10000, eViewType::UAV, computeTiles);

		mSharedBuffer = new graphics::StructedBuffer();
		mSharedBuffer->Create(sizeof(ComputeTileSharedData), 1, eViewType::UAV, nullptr, true);


	}

	TileSystem::~TileSystem()
	{
		if(mBuffer)
			delete mBuffer;
		if (mSharedBuffer)
			delete mSharedBuffer;
	}

	void TileSystem::Initialize()
	{
		MeshRenderer::Initialize();
	}

	void TileSystem::Update()
	{
		MeshRenderer::Update();
		if(mCoordData->mouseHoverTileCoord != Vector2(0.f, 0.f)
		   && mCoordData->mouseHoverTileCoord != Vector2(-1.f, -1.f))
		{
			Vector2 coord = mCoordData->mouseHoverTileCoord;
			//TileManager::hoverTile = TileManager::pathFindingTiles[coord.y][coord.x];
			//std::shared_ptr<Material> material = RESOURCE_FIND(Material, L"greenTileD");
			//SetMaterial(material);
		}
		mCS->SetCamera(GetOwner()->GetCamera());
	}

	void TileSystem::LateUpdate()
	{
		MeshRenderer::LateUpdate();
		// 여기서는 공통적으로 사용되는 constantbuffer가 있음
		// playerstandtile, mousehovertile
		// monsterstandtile은 따로 structedbuffer로 되어 건내주어야할듯. 한마리가 아님.
		renderer::TileDataCB data = {};

		Vector3 mouseV3 = MouseManager::UnprojectionMousePos(1.f, GetOwner()->GetCamera());
		Vector4 mousePos = Vector4(mouseV3.x, mouseV3.y, mouseV3.z, 0.f);
		data.mousePos = mousePos;
		if (PlayerInfo::player)
		{
			Vector3 posV3 = GET_POS(PlayerInfo::player);
			Vector4 pos = Vector4(posV3.x, posV3.y, posV3.z, 0.f);
			data.playerPos = pos;
		}
		else
		{
			data.playerPos = Vector4(0.f, 0.f, 1.f, 0.f);
		}
		mSharedBuffer->SetData(&data, 1);

		mCS->SetTileBuffer(mBuffer);
		mCS->SetSharedBuffer(mSharedBuffer);
		mCS->OnExcute(&mCoordData,1);
	}

	void TileSystem::Render()
	{
		MeshRenderer::Render();
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		mBuffer->BindSRV(eShaderStage::VS, 11);
		mBuffer->BindSRV(eShaderStage::GS, 11);
		mBuffer->BindSRV(eShaderStage::PS, 11);

		GetMaterial()->Binds();
		GetMesh()->RenderInstanced(10000);

		mBuffer->Clear();
	}
}
