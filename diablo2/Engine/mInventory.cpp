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
#include "mFontWrapper.h"
#include "mPlayerManager.h"
#include "mShop.h"

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

		//x 105 y 457

		mMoneyUI = new UI();
        mMoneyUI->SetCamera(camera);
		mMoneyUI->SetState(NoRenderUpdate);
		mMoneyUI->SetTextSize(15.f);
		mMoneyUI->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		SET_MESH(mMoneyUI, L"RectMesh");
		SET_MATERIAL(mMoneyUI, L"noneRect");
        curScene->AddGameObject(eLayerType::UI, mMoneyUI);


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

		//{
		//	InvenItem* hpPotion = new InvenItem(eItem::hpPotion1);

		//	hpPotion->SetCamera(GetCamera());
		//	hpPotion->SetState(GameObject::NoRenderUpdate);
		//	ADD_COMP(hpPotion, ItemScript);
		//	curScene->AddGameObject(eLayerType::Item, hpPotion);
		//	StashManager::AddItem(hpPotion, StashManager::eStashType::Inventory);
		//}
		//{
		//	InvenItem* mpPotion = new InvenItem(eItem::mpPotion1);

		//	mpPotion->SetState(GameObject::RenderUpdate);
		//	mpPotion->SetCamera(GetCamera());
		//	ADD_COMP(mpPotion, ItemScript);
		//	curScene->AddGameObject(eLayerType::Item, mpPotion);
		//	StashManager::AddItem(mpPotion, StashManager::eStashType::Inventory);
		//}
		//{
		//	InvenItem* orb1 = new InvenItem(eItem::jaredsStone);

		//	orb1->SetState(GameObject::NoRenderUpdate);
		//	orb1->SetCamera(GetCamera());
		//	ADD_COMP(orb1, ItemScript);
		//	curScene->AddGameObject(eLayerType::Item, orb1);
		//	StashManager::AddItem(orb1, StashManager::eStashType::Inventory);
		//}
		//{
		//	InvenItem* leaderArmor = new InvenItem(eItem::leaderArmor);

		//	leaderArmor->SetState(GameObject::NoRenderUpdate);
		//	leaderArmor->SetCamera(GetCamera());
		//	ADD_COMP(leaderArmor, ItemScript);
		//	curScene->AddGameObject(eLayerType::Item, leaderArmor);
		//	StashManager::AddItem(leaderArmor, StashManager::eStashType::Inventory);
		//}
		//{
		//	InvenItem* cap = new InvenItem(eItem::cap);

		//	cap->SetState(GameObject::NoRenderUpdate);
		//	cap->SetCamera(GetCamera());
		//	ADD_COMP(cap, ItemScript);
		//	curScene->AddGameObject(eLayerType::Item, cap);
		//	StashManager::AddItem(cap, StashManager::eStashType::Inventory);
		//}

		//{
		//	InvenItem* hpPotion = new InvenItem(eItem::hpPotion1);

		//	hpPotion->SetCamera(GetCamera());
		//	hpPotion->SetState(GameObject::RenderUpdate);
		//	ADD_COMP(hpPotion, ItemScript);
		//	curScene->AddGameObject(eLayerType::Item, hpPotion);
		//	StashManager::AddItem(hpPotion, StashManager::eStashType::PocketInven);
		//}
		//{
		//	InvenItem* hpPotion = new InvenItem(eItem::hpPotion1);

		//	hpPotion->SetCamera(GetCamera());
		//	hpPotion->SetState(GameObject::RenderUpdate);
		//	ADD_COMP(hpPotion, ItemScript);
		//	curScene->AddGameObject(eLayerType::Item, hpPotion);
		//	StashManager::AddItem(hpPotion, StashManager::eStashType::PocketInven);
		//}
		//{
		//	InvenItem* hpPotion = new InvenItem(eItem::mpPotion1);

		//	hpPotion->SetCamera(GetCamera());
		//	hpPotion->SetState(GameObject::RenderUpdate);
		//	ADD_COMP(hpPotion, ItemScript);
		//	curScene->AddGameObject(eLayerType::Item, hpPotion);
		//	StashManager::AddItem(hpPotion, StashManager::eStashType::PocketInven);
		//}
		//{
		//	InvenItem* hpPotion = new InvenItem(eItem::mpPotion1);

		//	hpPotion->SetCamera(GetCamera());
		//	hpPotion->SetState(GameObject::RenderUpdate);
		//	ADD_COMP(hpPotion, ItemScript);
		//	curScene->AddGameObject(eLayerType::Item, hpPotion);
		//	StashManager::AddItem(hpPotion, StashManager::eStashType::PocketInven);
		//}

		StashManager::InitItems(StashManager::eStashType::Inventory);
		StashManager::InitItems(StashManager::eStashType::PocketInven);
		//StashManager::InitItems(StashManager::eStashType::ExPocketInven);
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

		makeMoneyUI();
		if(StashManager::GetShopInventoryState() == RenderUpdate)
		{
			SetState(eState::RenderUpdate);
		}

		if (Input::GetKeyDown(eKeyCode::ESC))
		{
			SetState(eState::NoRenderUpdate);
		}

		if (closeBtn->GetOneClick())
		{
			if(nullptr != StashManager::GetCurRenderShop())
				StashManager::GetCurRenderShop()->SetState(eState::NoRenderUpdate);

			SetState(NoRenderUpdate);
		}
		
		StashManager::SetInventoryVisible(GetState());
		closeBtn->SetState(GetState());
		mMoneyUI->SetState(GetState());
	}
	void Inventory::LateUpdate()
	{
		UI::LateUpdate();
	}
	void Inventory::Render()
	{
		UI::Render();
	}

    void Inventory::makeMoneyUI()
    {
		std::wstring moneyStr = std::to_wstring(PlayerManager::money);
		mMoneyUI->SetText(moneyStr);
		float textSize = mMoneyUI->GetTextSize();
		Vector2 fontSize =FontWrapper::GetTextSize(moneyStr.c_str(), textSize);
		SET_SCALE_XYZ(mMoneyUI, fontSize.x, fontSize.y, 1.f);

		SET_POS_XYZ(mMoneyUI
			, (fontSize.x / 2.f) + 107.f * Texture::GetWidRatio()
			, RESOL_H_HEI - (fontSize.y / 2.f) - 458.f * Texture::GetHeiRatio()
			, 0.f);
    }
}
