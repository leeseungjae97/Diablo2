#include "mTileSystem.h"

#include "mTileManager.h"
#include "mRenderer.h"
#include "mMouseManager.h"
#include "mMonsterManager.h"
#include "mInput.h"

#include "../Engine/mPlayerInfo.h"
#include "../Engine/mPlayer.h"
#include "../Engine/mMonster.h"

namespace m
{
	TileSystem::TileSystem()
		: mBuffer(nullptr)
		, mSharedBuffer(nullptr)
		, mCoordData(nullptr)
	{
		//mComputedCoords.resize(4);

		std::shared_ptr<Mesh> mesh = RESOURCE_FIND(Mesh, L"PointMesh");
		SetMesh(mesh);
		std::shared_ptr<Material> material = RESOURCE_FIND(Material, L"greenOutlineTileD");
		SetMaterial(material);

		mCS = Resources::Find<TileComputeShader>(L"TileComputeShader");

		ComputeTile computeTiles[10000] = {};
		for(int i = 0 ; i < 10000; ++i)
		{
			Vector3 posV3 = GET_POS(TileManager::pathFindingTiles[i / 100][i % 100]);
			Vector4 pos = Vector4(posV3.x, posV3.y, posV3.z, 0.f);
			computeTiles[i].tilePosition = pos;
			computeTiles[i].tileSize = GET_VEC2_F_VEC3_D(GET_SCALE(TileManager::pathFindingTiles[i / 100][i % 100]));
			computeTiles[i].tileCoord = Vector2(i % 100, i / 100);
		}
		mBuffer = new graphics::StructedBuffer();
		mBuffer->Create(sizeof(ComputeTile), 10000, eViewType::UAV, computeTiles);

		mSharedBuffer = new graphics::StructedBuffer();
		mSharedBuffer->Create(sizeof(ComputeTileSharedData), 1, eViewType::UAV, nullptr, true);

		mTileCoordBuffer = new graphics::StructedBuffer();
		mTileCoordBuffer->Create(sizeof(ComputedTileCoord), 1, eViewType::UAV, nullptr, true);

		mMonsterBuffer = new graphics::StructedBuffer();
		mMonsterCoordBuffer = new graphics::StructedBuffer();
	}

	TileSystem::~TileSystem()
	{
		
		if(mBuffer)
		{
			delete mBuffer;
			mBuffer = nullptr;
		}
		if (mSharedBuffer)
		{
			delete mSharedBuffer;
			mSharedBuffer = nullptr;
		}
		if (mTileCoordBuffer)
		{
			delete mTileCoordBuffer;
			mTileCoordBuffer = nullptr;
		}
		if(mMonsterBuffer)
		{
			delete mMonsterBuffer;
			mMonsterBuffer = nullptr;
		}
		if(mMonsterCoordBuffer)
		{
			delete mMonsterCoordBuffer;
			mMonsterCoordBuffer = nullptr;
		}
		mCoordData = nullptr;
		//mComputedCoords.resize(0);
		//mComputedCoords.clear();
	}

	void TileSystem::Initialize()
	{
		MeshRenderer::Initialize();
	}

	void TileSystem::Update()
	{
		MeshRenderer::Update();

		if(Input::GetKeyDown(eKeyCode::A))
		{
			std::shared_ptr<Material> material = RESOURCE_FIND(Material, L"greenOutlineTileD");
			SetMaterial(material);
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			std::shared_ptr<Material> material = RESOURCE_FIND(Material, L"noneRect");
			SetMaterial(material);
		}
		mCS->SetCamera(GetOwner()->GetCamera());
	}

	void TileSystem::LateUpdate()
	{
		ComputeTileSharedData data = {};
		data.monsterCount = MonsterManager::monsters.size();
		data.tileCount = TileManager::pathFindingTiles.size() * TileManager::pathFindingTiles[0].size();
		data.hoverUI = MouseManager::GetMouseOnUI();

		Vector3 mouseV3 = MouseManager::UnprojectionMousePos(1.f, GetOwner()->GetCamera());
		Vector4 mousePos = Vector4(mouseV3.x, mouseV3.y, 1.f, 0.f);
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


		if (!MonsterManager::monsters.empty())
		{
			std::vector<ComputeMonster> computeMonsters;
			
			for (int i = 0; i < MonsterManager::monsters.size(); ++i)
			{
				ComputeMonster cm;
				cm.monsterCount = MonsterManager::monsters.size();
				Vector3 posV3 = GET_POS(MonsterManager::monsters[i]);
				Vector4 pos = Vector4(posV3.x, posV3.y, posV3.z, 0.f);
				cm.monsterPos = pos;

				computeMonsters.push_back(cm);
			}

			mMonsterBuffer->Clear();
			mMonsterBuffer->Create(sizeof(ComputeMonster), MonsterManager::monsters.size(), eViewType::UAV, computeMonsters.data(), true);

			//if (!MonsterManager::monsters.empty())
			//{
			//	for (int i = 0; i < MonsterManager::monsters.size(); ++i)
			//	{
			//		Vector2 coord = MonsterManager::monsters[i]->GetCoord();
			//		TileManager::pathFindingTiles[coord.y][coord.x]->SetOnMonster(false);
			//	}
			//}

			mMonsterCoordBuffer->Clear();
			mMonsterCoordBuffer->Create(sizeof(ComputedMonsterCoord), MonsterManager::monsters.size(), eViewType::UAV, nullptr, true);

			mCS->SetMonsterBuffer(mMonsterBuffer);
			mCS->SetMonsterCoordBuffer(mMonsterCoordBuffer);
		}
		mCS->SetTileBuffer(mBuffer);
		mCS->SetSharedBuffer(mSharedBuffer);
		mCS->SetTileCoordBuffer(mTileCoordBuffer);


		//mCS->OnExcute(&mCoordData, 1, mComputedCoords.data(), MonsterManager::monsters.size());
		mCS->OnExcute(&mCoordData, 1, &mComputedCoords, MonsterManager::monsters.size());

		SetComputedData();
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
		mSharedBuffer->Clear();
		mTileCoordBuffer->Clear();
		mMonsterBuffer->Clear();
		mMonsterCoordBuffer->Clear();
	}

	void TileSystem::SetComputedData()
	{
		if (!MonsterManager::monsters.empty())
		{
			for (int i = 0; i < MonsterManager::monsters.size(); ++i)
			{
				Vector2 coord = mComputedCoords[i].monsterStandTileCoord;
				if (coord != Vector2(-1.f, -1.f))
				{
					MonsterManager::monsters[i]->SetCoord(coord);
				}
			}
		}

		if (nullptr != mCoordData)
		{
			Vector2 mouseCoord = mCoordData->mouseHoverTileCoord;
			if (mouseCoord != Vector2(-1.f, -1.f))
			{
				TileManager::hoverTile = TileManager::pathFindingTiles[mouseCoord.y][mouseCoord.x];
			}

			Vector2 playerCoord = mCoordData->playerStandTileCoord;
			if (playerCoord != Vector2(-1.f, -1.f))
			{
				TileManager::playerStandTile = TileManager::pathFindingTiles[playerCoord.y][playerCoord.x];
			}
		}
	}
}
