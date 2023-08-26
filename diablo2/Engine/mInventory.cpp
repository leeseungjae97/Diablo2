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

		float invenZ = GET_POS(this).z;
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				EmptyRect* invenRect = new EmptyRect();
				invenRect->SetPos(Vector2(65.f + ((288.f / 10.f) * Texture::GetWidRatio() * x)
					, -51.f + (-(114.f / 4.f) * Texture::GetHeiRatio() * y)));
				invenRect->SetSize(Vector2((288.f / 10.f) * Texture::GetWidRatio()
					, (114.f / 4.f) * Texture::GetHeiRatio()));
				invens.push_back(invenRect);
			}
		}

		invenWeapon1Left = new EmptyRect();
		invenWeapon1Left->SetSize(60.f * Texture::GetWidRatio()
			, 115.f * Texture::GetHeiRatio());
		invenWeapon1Right = new EmptyRect();
		invenWeapon1Right->SetSize(60.f * Texture::GetWidRatio()
			, 116.f * Texture::GetHeiRatio());
		invenRingLeft = new EmptyRect();
		invenRingLeft->SetSize(30.f * Texture::GetWidRatio()
			, 31.f * Texture::GetHeiRatio());
		invenRingRight = new EmptyRect();
		invenRingRight->SetSize(30.f * Texture::GetWidRatio()
			, 31.f * Texture::GetHeiRatio());
		invenAmulet = new EmptyRect();
		invenAmulet->SetSize(30.f * Texture::GetWidRatio()
			, 31.f * Texture::GetHeiRatio());
		invenBelt = new EmptyRect();
		invenBelt->SetSize(60.f * Texture::GetWidRatio()
			, 31.f * Texture::GetHeiRatio());
		invenHelmet = new EmptyRect();
		invenHelmet->SetSize(60.f * Texture::GetWidRatio()
			, 60.f * Texture::GetHeiRatio());
		invenShoes = new EmptyRect();
		invenShoes->SetSize(60.f * Texture::GetWidRatio()
			, 61.f * Texture::GetHeiRatio());
		invenGlove = new EmptyRect();
		invenGlove->SetSize(60.f * Texture::GetWidRatio()
			, 61.f * Texture::GetHeiRatio());
		invenArmor = new EmptyRect();
		invenArmor->SetSize(62.f * Texture::GetWidRatio()
			, 89.f * Texture::GetHeiRatio());

		invenWeapon1Left->SetPos((17.f * Texture::GetWidRatio())
			+ invenWeapon1Left->GetSize().x / 2.f, (RESOL_H_HEI - 110.f * Texture::GetHeiRatio()) - invenWeapon1Left->GetSize().y / 2.f);

		invenWeapon1Right->SetPos((248.f * Texture::GetWidRatio())
			+ invenWeapon1Right->GetSize().x / 2.f, (RESOL_H_HEI - 110.f * Texture::GetHeiRatio()) - invenWeapon1Right->GetSize().y / 2.f);

		invenRingLeft->SetPos((91.f * Texture::GetWidRatio())
			+ invenRingLeft->GetSize().x / 2.f, (RESOL_H_HEI - 240.f * Texture::GetHeiRatio()) - invenRingLeft->GetSize().y / 2.f);

		invenRingRight->SetPos((205.f * Texture::GetWidRatio())
			+ invenRingRight->GetSize().x / 2.f, (RESOL_H_HEI - 239.f * Texture::GetHeiRatio()) - invenRingRight->GetSize().y / 2.f);

		invenAmulet->SetPos((205.f * Texture::GetWidRatio())
			+ invenAmulet->GetSize().x / 2.f, (RESOL_H_HEI - 95.f * Texture::GetHeiRatio()) - invenAmulet->GetSize().y / 2.f);

		invenBelt->SetPos((133.f * Texture::GetWidRatio())
			+ invenBelt->GetSize().x / 2.f, (RESOL_H_HEI - 240.f * Texture::GetHeiRatio()) - invenBelt->GetSize().y / 2.f);

		invenHelmet->SetPos((132.f * Texture::GetWidRatio())
			+ invenHelmet->GetSize().x / 2.f, (RESOL_H_HEI - 65.0f * Texture::GetHeiRatio()) - invenHelmet->GetSize().y / 2.f);

		invenShoes->SetPos((248.f * Texture::GetWidRatio())
			+ invenShoes->GetSize().x / 2.f, (RESOL_H_HEI - 240.f * Texture::GetHeiRatio()) - invenShoes->GetSize().y / 2.f);

		invenGlove->SetPos((17.f * Texture::GetWidRatio())
			+ invenGlove->GetSize().x / 2.f, (RESOL_H_HEI - 240.f * Texture::GetHeiRatio()) - invenGlove->GetSize().y / 2.f);

		invenArmor->SetPos((132.f * Texture::GetWidRatio())
			+ invenArmor->GetSize().x / 2.f, (RESOL_H_HEI - 138.f * Texture::GetHeiRatio()) - invenArmor->GetSize().y / 2.f);

		equiments.push_back(invenWeapon1Left);
		equiments.push_back(invenWeapon1Right);
		equiments.push_back(invenRingLeft);
		equiments.push_back(invenRingRight);
		equiments.push_back(invenAmulet);
		equiments.push_back(invenBelt);
		equiments.push_back(invenHelmet);
		equiments.push_back(invenShoes);
		equiments.push_back(invenGlove);
		equiments.push_back(invenArmor);

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


		invensCollider = new EmptyRect();
		invensCollider->SetSize(300.f * Texture::GetWidRatio(), 120.f * Texture::GetHeiRatio());
		invensCollider->SetPos((15.f + (300.f / 2.f)) * Texture::GetWidRatio(), (-15.f + (-120.f / 2.f)) * Texture::GetHeiRatio());

		{
			InvenItem* hpPosion = new InvenItem(eItem::hpPosion1, this);

			hpPosion->SetCamera(GetCamera());
			hpPosion->SetName(L"1");
			hpPosion->SetState(GameObject::NoRenderUpdate);
			ADD_COMP(hpPosion, ItemScript);
			curScene->AddGameObject(eLayerType::Item, hpPosion);
			invenItems.push_back(hpPosion);
		}
		{
			InvenItem* mpPosion = new InvenItem(eItem::mpPosion1, this);

			mpPosion->SetState(GameObject::NoRenderUpdate);
			mpPosion->SetName(L"2");
			mpPosion->SetCamera(GetCamera());
			ADD_COMP(mpPosion, ItemScript);
			curScene->AddGameObject(eLayerType::Item, mpPosion);
			invenItems.push_back(mpPosion);
		}
		{
			InvenItem* orb1 = new InvenItem(eItem::jaredsStone, this);

			orb1->SetState(GameObject::NoRenderUpdate);
			orb1->SetName(L"3");
			orb1->SetCamera(GetCamera());
			ADD_COMP(orb1, ItemScript);
			curScene->AddGameObject(eLayerType::Item, orb1);
			invenItems.push_back(orb1);
		}
		{
			InvenItem* leaderArmor = new InvenItem(eItem::leaderArmor, this);

			leaderArmor->SetState(GameObject::NoRenderUpdate);
			leaderArmor->SetCamera(GetCamera());
			ADD_COMP(leaderArmor, ItemScript);
			curScene->AddGameObject(eLayerType::Item, leaderArmor);
			invenItems.push_back(leaderArmor);
		}
		{
			InvenItem* cap = new InvenItem(eItem::cap, this);

			cap->SetState(GameObject::NoRenderUpdate);
			cap->SetCamera(GetCamera());
			ADD_COMP(cap, ItemScript);
			curScene->AddGameObject(eLayerType::Item, cap);
			invenItems.push_back(cap);
		}


	}
	Inventory::~Inventory()
	{
		for(EmptyRect* inven : invens)
		{
			if (inven)
			{
				delete inven;
				inven = nullptr;
			}
		}
		for(EmptyRect* eq : equiments)
		{
			if(eq)
			{
				delete eq;
				eq = nullptr;
			}
		}
		if(invensCollider)
			delete invensCollider;
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

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			for (InvenItem* ii : invenItems)
			{
				if (ii->GetHover() && !ii->GetMouseFollow())
					ii->SetClickFunction();
			}
		}

		if (GetState() != invenItems[0]->GetState())
		{
			closeBtn->SetState(GetState());
			for (InvenItem* ii : invenItems)
				ii->SetState(GetState());
		}
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