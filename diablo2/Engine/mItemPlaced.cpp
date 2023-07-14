#include "mItemPlaced.h"
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

#define INVEN_X_SIZE 30
#define INVEN_Y_SIZE 30

namespace m
{
	ItemPlaced::ItemPlaced(Camera* camera)
	{
		SetCamera(camera);
		SetName(L"Inventory");
		MeshRenderer* mr = GetComponent<MeshRenderer>();

		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"inventoryPanel"));

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(400.f * Texture::GetWidRatio()
		, 555.f * Texture::GetHeiRatio(), 0.f));
		tr->SetPosition(Vector3(400.f * Texture::GetWidRatio() / 2.f
			, 450.f - 555.f * Texture::GetHeiRatio() / 2.f, -1.0f));

		Scene* curScene = SceneManager::GetActiveScene();
		curScene->AddGameObject(eLayerType::UI, this);

		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				Inven* inven = new Inven();
				inven->SetState(eState::Invisible);

				Transform* invenTr = inven->GetComponent<Transform>();
				invenTr->SetPosition(Vector3(65.f + ((288.f / 10.f) * Texture::GetWidRatio() * x)
					, -51.f + (-(114.f / 4.f) * Texture::GetHeiRatio() * y), tr->GetPosition().z));

				invenTr->SetScale(Vector3((288.f / 10.f) * Texture::GetWidRatio()
					, (114.f / 4.f) * Texture::GetHeiRatio(), 0.f));

				curScene->AddGameObject(eLayerType::UI, inven);

				invens.push_back(inven);
			}
		}

		{
			InvenItem* hpPosion = new InvenItem(eItem::hpPosion1, this);

			hpPosion->SetCamera(GetCamera());
			hpPosion->SetState(GameObject::Invisible);
			curScene->AddGameObject(eLayerType::Item, hpPosion);
			invenItems.push_back(hpPosion);
		}
		{
			InvenItem* mpPosion = new InvenItem(eItem::mpPosion1, this);

			mpPosion->SetState(GameObject::Invisible);
			mpPosion->SetCamera(GetCamera());

			curScene->AddGameObject(eLayerType::Item, mpPosion);
			invenItems.push_back(mpPosion);
		}
		{
			InvenItem* orb1 = new InvenItem(eItem::jaredsStone, this);

			orb1->SetState(GameObject::Invisible);
			orb1->SetCamera(GetCamera());

			curScene->AddGameObject(eLayerType::Item, orb1);
			invenItems.push_back(orb1);
		}

		
	}
	ItemPlaced::~ItemPlaced()
	{}
	void ItemPlaced::Initialize()
	{
		UI::Initialize();
	}
	void ItemPlaced::Update()
	{
		UI::Update();
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			for (InvenItem* ii : invenItems)
			{
				if (ii->GetHover() && !ii->MouseFollow())
				{
					ii->SetClickFunction();
				}
			}
		}

		if (GetState() != invenItems[0]->GetState())
		{
			for (InvenItem* ii : invenItems)
			{
				ii->SetState(GetState());
			}
		}
		if (GetState() != invens[0]->GetState())
		{
			for (Inven* ii : invens)
			{
				ii->SetState(GetState());
			}
		}
	}
	void ItemPlaced::LateUpdate()
	{
		UI::LateUpdate();
	}
	void ItemPlaced::Render()
	{
		UI::Render();
	}
}