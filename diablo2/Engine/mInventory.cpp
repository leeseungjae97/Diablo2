#include "mInventory.h"
#include "../engine_source/mComponent.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mMaterial.h"
#include "../engine_source/mResources.h"
#include "../engine_source/mTexture.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/ItemLookUpTables.h"

#include "mInvenItem.h"
#include "mItem.h"
#include "mItemScript.h"
#include "mButton.h"

#define INVEN_X_SIZE 30
#define INVEN_Y_SIZE 30

namespace m
{
	Inventory::Inventory(Camera* camera)
	{
		SetCamera(camera);
		SetName(L"Inventory");

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"inventoryPanel");


		MAKE_GET_TEX(this, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(this, tex, 0.f);
		SET_POS_XYZ(this, tex->GetMetaDataWidth() * Texture::GetWidRatio() / 2.f
			, RESOL_H_HEI - tex->GetMetaDataHeight() * Texture::GetHeiRatio() / 2.f, -1.0f);

		Scene* curScene = SceneManager::GetActiveScene();
		curScene->AddGameObject(eLayerType::UI, this);

		closeBtn = new Button();
		curScene->AddGameObject(eLayerType::UI, closeBtn);
		closeBtn->SetCamera(GetCamera());
		closeBtn->SetState(NoRenderUpdate);
		SET_MESH(closeBtn, L"RectMesh");
		SET_MATERIAL(closeBtn, L"closeBtn");
		closeBtn->SetClickMaterial(RESOURCE_FIND(Material, L"closeBtnClick"));
		closeBtn->SetNormalMaterial(RESOURCE_FIND(Material, L"closeBtn"));
		GET_TEX(closeBtn, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(closeBtn, tex, 0.0f);
		SET_POS_XYZ(closeBtn, 18.f * Texture::GetWidRatio() + tex->GetMetaDataWidth(), (-RESOL_H_HEI + 124.f * Texture::GetHeiRatio() + tex->GetMetaDataHeight() / 2.f), 0.f);


		//invensCollider = new EmptyRect();
		//invensCollider->SetSize(300.f * Texture::GetWidRatio(), 120.f * Texture::GetHeiRatio());
		//invensCollider->SetPos((15.f + (300.f / 2.f)) * Texture::GetWidRatio(), (-15.f + (-120.f / 2.f)) * Texture::GetHeiRatio());

		{
			InvenItem* hpPosion = new InvenItem(eItem::hpPosion1);

			hpPosion->SetCamera(GetCamera());
			hpPosion->SetState(GameObject::NoRenderUpdate);
			ADD_COMP(hpPosion, ItemScript);
			curScene->AddGameObject(eLayerType::Item, hpPosion);
			//invenItems.push_back(hpPosion);
			StashManager::AddItem(hpPosion, StashManager::eStashType::Inventory);
		}
		{
			InvenItem* mpPosion = new InvenItem(eItem::mpPosion1);

			mpPosion->SetState(GameObject::NoRenderUpdate);
			mpPosion->SetCamera(GetCamera());
			ADD_COMP(mpPosion, ItemScript);
			curScene->AddGameObject(eLayerType::Item, mpPosion);
			//invenItems.push_back(mpPosion);
			StashManager::AddItem(mpPosion, StashManager::eStashType::Inventory);
		}
		{
			InvenItem* orb1 = new InvenItem(eItem::jaredsStone);

			orb1->SetState(GameObject::NoRenderUpdate);
			orb1->SetCamera(GetCamera());
			ADD_COMP(orb1, ItemScript);
			curScene->AddGameObject(eLayerType::Item, orb1);
			//invenItems.push_back(orb1);
			StashManager::AddItem(orb1, StashManager::eStashType::Inventory);
		}
		{
			InvenItem* leaderArmor = new InvenItem(eItem::leaderArmor);

			leaderArmor->SetState(GameObject::NoRenderUpdate);
			leaderArmor->SetCamera(GetCamera());
			ADD_COMP(leaderArmor, ItemScript);
			curScene->AddGameObject(eLayerType::Item, leaderArmor);
			//invenItems.push_back(leaderArmor);
			StashManager::AddItem(leaderArmor, StashManager::eStashType::Inventory);
		}
		{
			InvenItem* cap = new InvenItem(eItem::cap);

			cap->SetState(GameObject::NoRenderUpdate);
			cap->SetCamera(GetCamera());
			ADD_COMP(cap, ItemScript);
			curScene->AddGameObject(eLayerType::Item, cap);
			StashManager::AddItem(cap, StashManager::eStashType::Inventory);
		}

		StashManager::InitItems(StashManager::eStashType::Inventory);
	}
	Inventory::~Inventory()
	{

	}
	void Inventory::Initialize()
	{
		UI::Initialize();
	}
	void Inventory::Update()
	{
		UI::Update();
		if (closeBtn->GetOneClick())
			SetState(NoRenderUpdate);

		StashManager::SetInventoryVisible(GetState());
		closeBtn->SetState(GetState());
	}
	void Inventory::LateUpdate()
	{
		UI::LateUpdate();
	}
	void Inventory::Render()
	{
		UI::Render();
	}
}
