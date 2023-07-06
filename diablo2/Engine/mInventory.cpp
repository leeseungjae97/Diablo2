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
		tr->SetPosition(Vector3(0.0f, 450.0f, -1.0f));


		Scene* curScene = SceneManager::GetActiveScene();
		curScene->AddGameObject(eLayerType::UI, this);

		Transform* invenTr = GetComponent<Transform>();
		{
			InvenItem* hpPosion = new InvenItem(Item::eItemType::Posion);
			hpPosion->SetState(GameObject::Invisible);
			hpPosion->SetCamera(GetCamera());
			MeshRenderer* mr = hpPosion->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"hpPosion1"));

			Transform* tr = hpPosion->GetComponent<Transform>();
			tr->SetScale(Vector3(28.f * Texture::GetWidRatio(), 28.f * Texture::GetHeiRatio(), 0.f));
			tr->SetPosition(Vector3(17.f, 0.f, -0.9f));

			curScene->AddGameObject(eLayerType::UI, hpPosion);
			invenItems.push_back(hpPosion);
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