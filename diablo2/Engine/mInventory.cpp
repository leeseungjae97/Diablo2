#include "mInventory.h"
#include "..\engine_source\mComponent.h"
#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mTransform.h"
#include "..\engine_source\mMaterial.h"
#include "..\engine_source\mResources.h"
#include "..\engine_source\mTexture.h"
#include "..\engine_source\mSceneManager.h"

#include "mInvenItem.h"
#include "mItem.h"

#define INVEN_X_SIZE 30
#define INVEN_Y_SIZE 30

namespace m
{
	Inventory::Inventory(Camera* camera)
	{
		SetCamera(camera);
		SetName(L"Inventory");
		MeshRenderer* mr = AddComponent<MeshRenderer>();

		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"inventoryPanel"));

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(400.f * Texture::GetWidRatio()
		, 555.f * Texture::GetHeiRatio(), 0.f));
		tr->SetPosition(Vector3(0.0f + 400.f * Texture::GetWidRatio() / 2.f
			, 450.f - 555.f * Texture::GetHeiRatio() / 2.f, -1.0f));

		Scene* curScene = SceneManager::GetActiveScene();
		curScene->AddGameObject(eLayerType::UI, this);

		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				UI* inven = new UI();
				Transform* invenTr = inven->GetComponent<Transform>();
				invenTr->SetPosition(Vector3(63.f + ((291.f / 10.f) * Texture::GetWidRatio() * x)
					, -180.f + ((117.f / 4.f) * Texture::GetHeiRatio() * y), tr->GetPosition().z));

				invenTr->SetScale(Vector3((291.f / 10.f) * Texture::GetWidRatio()
					, (117.f / 4.f) * Texture::GetHeiRatio(), 0.f));

				MeshRenderer* invenMr = inven->AddComponent<MeshRenderer>();
				invenMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				invenMr->SetMaterial(Resources::Find<Material>(L"testDebugRect"));

				curScene->AddGameObject(eLayerType::UI, inven);

				invens.push_back(inven);
			}
		}

		{
			InvenItem* hpPosion = new InvenItem(Item::eItemType::Posion, this
				, invens[0]->GetComponent<Transform>()->GetPosition());
			hpPosion->SetState(GameObject::Active);
			hpPosion->SetCamera(GetCamera());
			hpPosion->SetName(L"hpPosion");
			MeshRenderer* mr = hpPosion->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"hpPosion1"));

			Transform* oTr = hpPosion->GetComponent<Transform>();
			oTr->SetScale(Vector3(28.f * Texture::GetWidRatio(), 28.f* Texture::GetHeiRatio(), 0.f));

			curScene->AddGameObject(eLayerType::Item, hpPosion);
			invenItems.push_back(hpPosion);
		}
		{
			InvenItem* mpPosion = new InvenItem(Item::eItemType::Posion, this
				, invens[1]->GetComponent<Transform>()->GetPosition());
			mpPosion->SetState(GameObject::Active);
			mpPosion->SetCamera(GetCamera());
			mpPosion->SetName(L"mpPosion");
			MeshRenderer* mr = mpPosion->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"mpPosion1"));

			Transform* oTr = mpPosion->GetComponent<Transform>();
			oTr->SetScale(Vector3(28.f * Texture::GetWidRatio(), 28.f * Texture::GetHeiRatio(), 0.f));

			curScene->AddGameObject(eLayerType::Item, mpPosion);
			invenItems.push_back(mpPosion);
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
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			for (InvenItem* ii : invenItems)
			{
				if (ii->GetHover() && !ii->MouseFollow())
				{
					ii->OrderClickItem();
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