#include "mTileSystem.h"

#include "mTileManager.h"
#include "mRenderer.h"
#include "mMouseManager.h"
#include "mMonsterManager.h"
#include "mInput.h"
#include "mSkillManager.h"

#include "..\Engine\mPlayerManager.h"
#include "../Engine/mPlayer.h"
#include "../Engine/mMonster.h"
#include "../Engine/mSkillWall.h"

namespace m
{
	TileSystem::TileSystem()
		: mTileBuffer(nullptr)
		, mTileSharedBuffer(nullptr)
		, mCoordData(nullptr)
	{
		std::shared_ptr<Mesh> mesh = RESOURCE_FIND(Mesh, L"PointMesh");
		SetMesh(mesh);
		std::shared_ptr<Material> material = RESOURCE_FIND(Material, L"greenOutlineTileD");
		SetMaterial(material);

		mCS = Resources::Find<TileComputeShader>(L"TileComputeShader");

		std::shared_ptr<Material> greenTile = RESOURCE_FIND(Material, L"greenTileD");
		std::shared_ptr<Material> redTile = Resources::Find<Material>(L"redTileD");
		
		AddMaterial(greenTile);
		AddMaterial(redTile);
		
		for(int i = 0 ; i < 10000; ++i)
		{
			ComputeTile ct;
			Vector3 posV3 = TileManager::pathFindingTiles[i / 100][i % 100]->GetPos();
			Vector4 pos = Vector4(posV3.x, posV3.y, posV3.z, 0.f);
			ct.tilePosition = pos;
			ct.tileSize = GET_VEC2_F_VEC3_D(TileManager::pathFindingTiles[i / 100][i % 100]->GetScale());
			ct.tileCoord = Vector2(i % 100, i / 100);

			ct.isWall = TileManager::pathFindingTiles[i / 100][i % 100]->GetIsWall();
		ct.isThrough = TileManager::pathFindingTiles[i / 100][i % 100]->GetIsThrough();

			mTiles.push_back(ct);
		}
		mTileBuffer = new graphics::StructuredBuffer();
		mTileBuffer->Create(sizeof(ComputeTile), 10000, eViewType::UAV, mTiles.data(), true);

		mTileSharedBuffer = new graphics::StructuredBuffer();
		mTileSharedBuffer->Create(sizeof(ComputeTileSharedData), 1, eViewType::UAV, nullptr, true);

		mComputedTileCoordBuffer = new graphics::StructuredBuffer();
		mComputedTileCoordBuffer->Create(sizeof(ComputedTileCoord), 1, eViewType::UAV, nullptr, true);

		mMonsterBuffer = new graphics::StructuredBuffer();
		mGetMonsterComputedCoordBuffer = new graphics::StructuredBuffer();
		mSkillBuffer = new graphics::StructuredBuffer();
	}

	TileSystem::~TileSystem()
	{
		
		if(mTileBuffer)
		{
			delete mTileBuffer;
			mTileBuffer = nullptr;
		}
		if (mTileSharedBuffer)
		{
			delete mTileSharedBuffer;
			mTileSharedBuffer = nullptr;
		}
		if (mComputedTileCoordBuffer)
		{
			delete mComputedTileCoordBuffer;
			mComputedTileCoordBuffer = nullptr;
		}
		if(mMonsterBuffer)
		{
			delete mMonsterBuffer;
			mMonsterBuffer = nullptr;
		}
		if(mGetMonsterComputedCoordBuffer)
		{
			delete mGetMonsterComputedCoordBuffer;
			mGetMonsterComputedCoordBuffer = nullptr;
		}
		if(mSkillBuffer)
		{
			delete mSkillBuffer;
			mSkillBuffer = nullptr;
		}
		mCoordData = nullptr;
		materials.clear();
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
		//mCS->SetCamera(GetOwner()->GetCamera());
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

		if (PlayerManager::player)
		{
			Vector3 posV3 = GET_POS(PlayerManager::player);
			Vector4 pos = Vector4(posV3.x, posV3.y, posV3.z, 0.f);
			data.playerPos = pos;
		}
		else
		{
			data.playerPos = Vector4(0.f, 0.f, 1.f, 0.f);
		}
		mTileSharedBuffer->SetData(&data, 1);


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
				cm.monsterSize = GET_SCALE(MonsterManager::monsters[i]);

				computeMonsters.push_back(cm);
			}

			mMonsterBuffer->Clear();
			mMonsterBuffer->Create(sizeof(ComputeMonster), MonsterManager::monsters.size(), eViewType::UAV, computeMonsters.data(), true);
			//mMonsterBuffer->SetData(computeMonsters.data(), 1);

			mGetMonsterComputedCoordBuffer->Clear();
			mGetMonsterComputedCoordBuffer->Create(sizeof(ComputedMonsterCoord), MonsterManager::monsters.size(), eViewType::UAV, nullptr, true);
			//mGetMonsterComputedCoordBuffer->SetData(&MonsterManager::monsters, 1);

			mCS->SetMonsterBuffer(mMonsterBuffer);
			mCS->SetMonsterCoordBuffer(mGetMonsterComputedCoordBuffer);
		}
		if(!SkillManager::skills.empty())
		{
			std::vector<SkillWallCollision> mSkills;

			for(Skill* skill : SkillManager::skills)
			{
				SkillWallCollision swc;
				swc.skillPosition = GET_POS(skill);
				swc.skillId = skill->GetSkillId();
				swc.size = SkillManager::skills.size();
				swc.crash = false;

				mSkills.push_back(swc);
			}

			mSkillBuffer->Clear();
			mSkillBuffer->Create(sizeof(SkillWallCollision), mSkills.size(), eViewType::UAV, mSkills.data(), true);

			mCS->SetSkillBuffer(mSkillBuffer);
		}
		mCS->SetTileBuffer(mTileBuffer);
		mCS->SetSharedBuffer(mTileSharedBuffer);
		mCS->SetTileCoordBuffer(mComputedTileCoordBuffer);
		
		mCS->OnExcute(&mCoordData, 1, &mComputedCoords, MonsterManager::monsters.size());

		SetComputedData();
	}

	void TileSystem::Render()
	{
		//MeshRenderer::Render();
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		mTileBuffer->BindSRV(eShaderStage::VS, 11);        
		mTileBuffer->BindSRV(eShaderStage::GS, 11);
		mTileBuffer->BindSRV(eShaderStage::PS, 11);

		BindsMaterials();
		GetMaterial()->Binds();
		GetMesh()->RenderInstanced(100000);

		mTileBuffer->Clear();
		mTileSharedBuffer->Clear();
		mComputedTileCoordBuffer->Clear();
		mMonsterBuffer->Clear();
		mGetMonsterComputedCoordBuffer->Clear();
		mSkillBuffer->Clear();
		//ClearMaterials();
	}
	void TileSystem::BindsMaterials()
	{
		for(int i = 0 ; i < materials.size() ; ++i)
		{
			materials[i]->Binds(i + 1);
		}
	}
	void TileSystem::ClearMaterials()
	{
		for (int i = 0; i < materials.size(); ++i)
		{
			materials[i]->Clear();
		}
	}
	void TileSystem::AddMaterial(std::shared_ptr<Material> mat)
	{
		materials.push_back(mat);
	}

	void TileSystem::SetComputedData()
	{

		
		if(!SkillManager::skills.empty())
		{
			SkillWallCollision* mData = nullptr;
			
			mSkillBuffer->GetData(&mData, SkillManager::skills.size());

		    for(int i = 0 ; i < SkillManager::skills.size(); ++i)
		    {
				SkillWallCollision swc = mData[i];
				//if(swc.crash == true)
				if(swc.crash != 0)
				{
					SkillManager::SkillCrash(swc.skillId);
				}
		    }
		}
		//ComputeTile* tile = nullptr;
		//mTileBuffer->GetData(&tile, 10000);
		//for(int i = 0 ; i < 10000; ++i)
		//{
		//    if(tile[i].isWall == TRUE)
		//    {
		//		int b = 0;
		//    }
		//}
		if (!MonsterManager::monsters.empty())
		{
			for (int i = 0; i < MonsterManager::monsters.size(); ++i)
			{
				Vector2 coord = MonsterManager::monsters[i]->GetCoord();
				if (coord != Vector2(-1.f, -1.f)
					&& coord.x < TileManager::tileXLen
					&& coord.y < TileManager::tileYLen)
				{
					TileManager::pathFindingTiles[coord.y][coord.x]->SetOnMonster(false);
				}
			}
		}

		if (!MonsterManager::monsters.empty())
		{
			for (int i = 0; i < MonsterManager::monsters.size(); ++i)
			{
				Vector2 coord = mComputedCoords[i].monsterStandTileCoord;
				if (coord != Vector2(-1.f, -1.f)
					&& coord.x < TileManager::tileXLen
					&& coord.y < TileManager::tileYLen)
				{
					MonsterManager::monsters[i]->SetCoord(coord);
					TileManager::pathFindingTiles[coord.y][coord.x]->SetOnMonster(true);
				}
			}
		}

		if (nullptr != mCoordData)
		{
			
			Vector2 mouseCoord = mCoordData->mouseHoverTileCoord;
			if (mouseCoord != Vector2(-1.f, -1.f)
				&& mouseCoord.x < TileManager::tileXLen
				&& mouseCoord.y < TileManager::tileYLen)
			{
				TileManager::hoverTile = TileManager::pathFindingTiles[mouseCoord.y][mouseCoord.x];
			}

			Vector2 playerCoord = mCoordData->playerStandTileCoord;
			if (playerCoord != Vector2(-1.f, -1.f)
				&& playerCoord.x < TileManager::tileXLen
				&& playerCoord.y < TileManager::tileYLen)
			{
				TileManager::playerStandTile = TileManager::pathFindingTiles[playerCoord.y][playerCoord.x];
			}

		 //   int id = mCoordData->hoverMonsterId;
			//if(id != -1)
			//{
			//	MouseManager::SetMouseHoverMonsterId(id);
			//	Vector2 coord = MonsterManager::monsters[id]->GetCoord();
			//	if (coord != Vector2(-1.f, -1.f)
			//		&& coord.x < TileManager::tileXLen
			//		&& coord.y < TileManager::tileYLen)
			//	{
			//		MouseManager::SetMouseHoverMonsterTileCoord(coord);
			//	}
			//}
		}
	}

    void TileSystem::WallChange()
    {
		for (int i = 0; i < 10000; ++i)
		{
			mTiles[i].isWall = TileManager::pathFindingTiles[i / 100][i % 100]->GetIsWall();
			mTiles[i].isThrough = TileManager::pathFindingTiles[i / 100][i % 100]->GetIsThrough();
			//mTiles[i].isWall = true;
		}
		mTileBuffer->Clear();
		mTileBuffer->Create(sizeof(ComputeTile), 10000, eViewType::UAV, mTiles.data(), true);

		mCS->SetTileBuffer(mTileBuffer);
    }
}
