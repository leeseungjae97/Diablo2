#include "mInvenItem.h"
#include "..\engine_source\mInput.h"
#include "..\engine_source\mApplication.h"
#include "..\engine_source\mTransform.h"
#include "..\engine_source\mMeshRenderer.h"

#include "mInventory.h"
#include "mInven.h"


namespace m
{
	InvenItem::InvenItem(eItem item, Inventory* inventory)
		: Item(itemTypeTable[item])
		, mInventory(inventory)
		, bSetMouseFollow(false)
		, mItem(item)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();

		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(itemNameTable[item]));

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(28.f * itemInvenDisplayScale[item][0] * Texture::GetWidRatio(), 28.f * itemInvenDisplayScale[item][1] * Texture::GetHeiRatio(), 0.f));

		std::vector<Inven*> invens = mInventory->GetInvens();
		bool deploy = true;

		for (int i = 0; i < invens.size(); ++i)
		{
			int dx = (i % 10) + (int)itemInvenDisplayScale[mItem][0] - 1;
			int dy = (i / 10) + (int)itemInvenDisplayScale[mItem][1] - 1;

			if (dx < 0 || dx > 9 || dy < 0 || dy > 4) continue;

			for (int y = i / 10; y <= dy; ++y)
			{
				for (int x = i % 10; x <= dx; ++x)
				{
					if (invens[y + x]->GetFill())
					{
						deploy = false;
					}
				}
			}
			if (deploy)
			{
				for (int y = i / 10; y <= dy; ++y)
				{
					for (int x = i % 10; x <= dx; ++x)
					{
						invens[y + x]->SetFill(true);
					}
				}
				GetComponent<Transform>()->SetPosition(invens[i]->GetComponent<Transform>()->GetPosition());
				prevPosition = invens[i]->GetComponent<Transform>()->GetPosition();
				break;
			}
		}
	}
	InvenItem::~InvenItem()
	{}
	void InvenItem::Initialize()
	{
		Item::Initialize();
	}
	void InvenItem::Update()
	{
		Item::Update();
		if (GetHover())
		{
			if (Input::GetKeyDown(eKeyCode::LBUTTON))
			{
				bSetMouseFollow = bSetMouseFollow ? false : true;

				bool deployed = false;
				std::vector<Inven*> invens = mInventory->GetInvens();
				std::vector<InvenItem*> invenItems = mInventory->GetInvenItems();

				for (int i = 0; i < invens.size(); ++i)
				{
					if (invens[i]->GetHover())
					{
						int dx = (i % 10) + (int)itemInvenDisplayScale[mItem][0] - 1;
						int dy = (i / 10) + (int)itemInvenDisplayScale[mItem][1] - 1;

						if (dx < 0 || dx > 9 || dy < 0 || dy > 4) continue;

						for (int y = i / 10; y <= dy; ++y)
						{
							for (int x = i % 10; x <= dx; ++x)
							{
								if (!invens[y + x]->GetFill())
								{
									deployed = true;
								}
							}		
						}
						if (deployed)
						{
							for (int y = i / 10; y <= dy; ++y)
							{
								for (int x = i % 10; x <= dx; ++x)
								{
									invens[y + x]->SetFill(true);
								}
							}
							GetComponent<Transform>()->SetPosition(invens[i]->GetComponent<Transform>()->GetPosition());
							prevPosition = invens[i]->GetComponent<Transform>()->GetPosition();
							break;
						}						
					}
				}
				if (!deployed)
					GetComponent<Transform>()->SetPosition(prevPosition);
			}
			if (bSetMouseFollow)
			{
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				Vector3 unprojMousePos = Input::GetUnprojectionMousePos(pos.z
					, GetCamera()->GetPrivateProjectionMatrix(), GetCamera()->GetPrivateViewMatrix());
				unprojMousePos.z = pos.z;
				GetComponent<Transform>()->SetPosition(Vector3(unprojMousePos));
			}
		}
	}
	void InvenItem::LateUpdate()
	{
		Item::LateUpdate();
	}
	void InvenItem::Render()
	{
		Item::Render();
	}
}