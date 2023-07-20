#include "mInventory.h"
#include "..\engine_source\mComponent.h"
#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mTransform.h"
#include "..\engine_source\mMaterial.h"
#include "..\engine_source\mResources.h"
#include "..\engine_source\mTexture.h"
#include "..\engine_source\mSceneManager.h"
#include "..\engine_source\ItemLookUpTables.h"

#include "mInvenItem.h"
#include "mItem.h"
#include "mPlayerScript.h"
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

		
		MAKE_TEX(this, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(this, tex, 0.f);
		SET_POS_XYZ(this, tex->GetWidth() * Texture::GetWidRatio() / 2.f
					  , RESOL_H_HEI - tex->GetHeight()* Texture::GetHeiRatio() / 2.f, -1.0f);

		Scene* curScene = SceneManager::GetActiveScene();
		curScene->AddGameObject(eLayerType::UI, this);

		float invenZ = GET_POS(this).z;
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				Inven* inven = new Inven();
				inven->SetState(eState::Invisible);
				inven->SetCamera(GetCamera());
				SET_POS_XYZ(inven, 65.f + ((288.f / 10.f) * Texture::GetWidRatio() * x)
						, -51.f + (-(114.f / 4.f) * Texture::GetHeiRatio() * y), invenZ);
				SET_SCALE_XYZ(inven, (288.f / 10.f) * Texture::GetWidRatio()
							  , (114.f / 4.f) * Texture::GetHeiRatio(), 0.f);

				curScene->AddGameObject(eLayerType::UI, inven);

				invens.push_back(inven);
			}
		}

		invenWeapon1Left = new Inven();
		SET_SCALE_XYZ(invenWeapon1Left, 60.f * Texture::GetWidRatio()
					  , 115.f * Texture::GetHeiRatio(), 0.f);
		invenWeapon1Right = new Inven();
		SET_SCALE_XYZ(invenWeapon1Right, 60.f * Texture::GetWidRatio()
					  , 116.f * Texture::GetHeiRatio(), 0.f);
		invenRingLeft = new Inven();
		SET_SCALE_XYZ(invenRingLeft, 30.f* Texture::GetWidRatio()
					  , 31.f* Texture::GetHeiRatio(), 0.f);
		invenRingRight = new Inven();
		SET_SCALE_XYZ(invenRingRight, 30.f * Texture::GetWidRatio()
					  , 31.f * Texture::GetHeiRatio(), 0.f);
		invenAmulet = new Inven();
		SET_SCALE_XYZ(invenAmulet, 30.f * Texture::GetWidRatio()
					  , 31.f * Texture::GetHeiRatio(), 0.f);
		invenBelt = new Inven();
		SET_SCALE_XYZ(invenBelt, 60.f * Texture::GetWidRatio()
					  , 31.f * Texture::GetHeiRatio(), 0.f);
		invenHelmet = new Inven();
		SET_SCALE_XYZ(invenHelmet, 60.f * Texture::GetWidRatio()
					  , 60.f * Texture::GetHeiRatio(), 0.f);
		invenShoes = new Inven();
		SET_SCALE_XYZ(invenShoes, 60.f * Texture::GetWidRatio()
					  , 61.f * Texture::GetHeiRatio(), 0.f);
		invenGlove = new Inven();
		SET_SCALE_XYZ(invenGlove, 60.f * Texture::GetWidRatio()
					  , 61.f * Texture::GetHeiRatio(), 0.f);
		invenArmor = new Inven();
		SET_SCALE_XYZ(invenArmor, 62.f * Texture::GetWidRatio()
					  , 89.f * Texture::GetHeiRatio(), 0.f);

		SET_POS_XYZ(invenWeapon1Left, (17.f * Texture::GetWidRatio()) + GET_SCALE(invenWeapon1Left).x / 2.f, (RESOL_H_HEI - 110.f * Texture::GetHeiRatio()) - GET_SCALE(invenWeapon1Left).y / 2.f, 0.0f);
		SET_POS_XYZ(invenWeapon1Right, (248.f * Texture::GetWidRatio()) + GET_SCALE(invenWeapon1Right).x / 2.f, (RESOL_H_HEI - 110.f * Texture::GetHeiRatio()) - GET_SCALE(invenWeapon1Right).y / 2.f, 0.0f);
		SET_POS_XYZ(invenRingLeft, (91.f * Texture::GetWidRatio()) + GET_SCALE(invenRingLeft).x / 2.f, (RESOL_H_HEI - 240.f * Texture::GetHeiRatio()) - GET_SCALE(invenRingLeft).y / 2.f, 0.0f);
		SET_POS_XYZ(invenRingRight, (205.f * Texture::GetWidRatio()) + GET_SCALE(invenRingRight).x / 2.f, (RESOL_H_HEI - 239.f * Texture::GetHeiRatio()) - GET_SCALE(invenRingRight).y / 2.f, 0.0f);
		SET_POS_XYZ(invenAmulet, (205.f * Texture::GetWidRatio()) + GET_SCALE(invenAmulet).x / 2.f, (RESOL_H_HEI - 95.f * Texture::GetHeiRatio()) - GET_SCALE(invenAmulet).y / 2.f, 0.0f);
		SET_POS_XYZ(invenBelt, (133.f * Texture::GetWidRatio()) + GET_SCALE(invenBelt).x / 2.f, (RESOL_H_HEI - 240.f * Texture::GetHeiRatio()) - GET_SCALE(invenBelt).y / 2.f, 0.0f);
		SET_POS_XYZ(invenHelmet, (132.f * Texture::GetWidRatio())+ GET_SCALE(invenHelmet).x / 2.f, (RESOL_H_HEI - 65.0f * Texture::GetHeiRatio()) - GET_SCALE(invenHelmet).y / 2.f, 0.0f);
		SET_POS_XYZ(invenShoes, (248.f * Texture::GetWidRatio())+ GET_SCALE(invenShoes).x / 2.f, (RESOL_H_HEI - 240.f * Texture::GetHeiRatio()) - GET_SCALE(invenShoes).y / 2.f, 0.0f);
		SET_POS_XYZ(invenGlove, (17.f * Texture::GetWidRatio()) + GET_SCALE(invenGlove).x / 2.f, (RESOL_H_HEI - 240.f * Texture::GetHeiRatio()) - GET_SCALE(invenGlove).y / 2.f, 0.0f);
		SET_POS_XYZ(invenArmor, (132.f * Texture::GetWidRatio()) + GET_SCALE(invenArmor).x / 2.f, (RESOL_H_HEI - 138.f * Texture::GetHeiRatio()) - GET_SCALE(invenArmor).y / 2.f, 0.0f);

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

		for (Inven* eq : equiments)
		{
			eq->SetCamera(GetCamera());
			eq->SetState(Invisible);
			//ADD_COMP(eq, Collider2D);
			curScene->AddGameObject(eLayerType::UI, eq);
		}

		closeBtn = new Button();
		curScene->AddGameObject(eLayerType::UI, closeBtn);
		closeBtn->SetCamera(GetCamera());
		closeBtn->SetName(L"closeButton");
		closeBtn->SetState(Invisible);
		SET_MESH(closeBtn, L"RectMesh");
		SET_MATERIAL(closeBtn, L"closeBtn");
		closeBtn->SetClickMaterial(RESOURCE_FIND(Material, L"closeBtnClick"));
		closeBtn->SetNormalMaterial(RESOURCE_FIND(Material, L"closeBtn"));
		GET_TEX(closeBtn, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(closeBtn, tex, 0.0f);
		SET_POS_XYZ(closeBtn, 18.f * Texture::GetWidRatio() + tex->GetWidth(), (-RESOL_H_HEI + 124.f * Texture::GetHeiRatio() + tex->GetHeight() / 2.f), 0.f);

		invensCollider = new GameObject();
		invensCollider->SetCamera(GetCamera());
		invensCollider->SetState(GameObject::Invisible);
		//ADD_COMP(invensCollider, Collider2D);
		SET_SCALE_XYZ(invensCollider, 300.f * Texture::GetWidRatio(), 120.f * Texture::GetHeiRatio(), 1.f);
		SET_POS_XYZ(invensCollider, (15.f + (300.f / 2.f)) * Texture::GetWidRatio(), (-15.f + (-120.f / 2.f)) * Texture::GetHeiRatio(), invenZ);
		curScene->AddGameObject(eLayerType::Item, invensCollider);

		{
			InvenItem* hpPosion = new InvenItem(eItem::hpPosion1, this);

			hpPosion->SetCamera(GetCamera());
			hpPosion->SetName(L"1");
			hpPosion->SetState(GameObject::Invisible);
			ADD_COMP(hpPosion, PlayerScript);
			curScene->AddGameObject(eLayerType::Item, hpPosion);
			invenItems.push_back(hpPosion);
		}
		{
			InvenItem* mpPosion = new InvenItem(eItem::mpPosion1, this);

			mpPosion->SetState(GameObject::Invisible);
			mpPosion->SetName(L"2");
			mpPosion->SetCamera(GetCamera());
			ADD_COMP(mpPosion, PlayerScript);
			curScene->AddGameObject(eLayerType::Item, mpPosion);
			invenItems.push_back(mpPosion);
		}
		{
			InvenItem* orb1 = new InvenItem(eItem::jaredsStone, this);

			orb1->SetState(GameObject::Invisible);
			orb1->SetName(L"3");
			orb1->SetCamera(GetCamera());
			ADD_COMP(orb1, PlayerScript);
			curScene->AddGameObject(eLayerType::Item, orb1);
			invenItems.push_back(orb1);
		}
		{
			InvenItem* leaderArmor = new InvenItem(eItem::leaderArmor, this);

			leaderArmor->SetState(GameObject::Invisible);
			leaderArmor->SetCamera(GetCamera());
			ADD_COMP(leaderArmor, PlayerScript);
			curScene->AddGameObject(eLayerType::Item, leaderArmor);
			invenItems.push_back(leaderArmor);
		}

		
	}
	Inventory::~Inventory()
	{}
	void Inventory::Initialize()
	{
		UI::Initialize();
	}
	void Inventory::Update()
	{
		UI::Update();
		if (closeBtn->GetOneClick())
			SetState(Invisible);

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
			invensCollider->SetState(GetState());
			closeBtn->SetState(GetState());

			for (InvenItem* ii : invenItems)
				ii->SetState(GetState());
			for (Inven* ii : equiments)
				ii->SetState(GetState());
		}
		if (GetState() != invens[0]->GetState())
		{
			for (Inven* ii : invens)
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