#include "mInvenItem.h"
#include "..\engine_source\mInput.h"
#include "..\engine_source\mApplication.h"
#include "..\engine_source\mTransform.h"
#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mCollider2D.h"

#include "mInventory.h"
#include "mInven.h"


namespace m
{
	InvenItem::InvenItem(eItem item, Inventory* inventory)
		: Item(itemTypeTable[(int)item])
		, mInventory(inventory)
		, bSetMouseFollow(false)
		, mItem(item)
	{
		AddComponent<Collider2D>();
		MeshRenderer* mr = AddComponent<MeshRenderer>();

		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(itemNameTable[(int)mItem]));

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(28.f * itemInvenDisplayScale[(int)mItem][0] * Texture::GetWidRatio(), 28.f * itemInvenDisplayScale[(int)mItem][1] * Texture::GetHeiRatio(), 0.f));
		Vector3 scale = tr->GetScale();

		std::vector<Inven*> invens = mInventory->GetInvens();
		
		for (int i = 0; i < invens.size(); ++i)
		{
			int dx = (i % 10) + (int)itemInvenDisplayScale[(int)mItem][0] - 1;
			int dy = (i / 10) + (int)itemInvenDisplayScale[(int)mItem][1] - 1;

			if (dx < 0 || dx > 9 || dy < 0 || dy > 3) continue;

			
			bool deploy = true;
			for (int y = i / 10; y <= dy; ++y)
			{
				for (int x = i % 10; x <= dx; ++x)
				{
					if (invens[y * 10 + x]->GetFill())
					{
						deploy = false;
						break;
					}
				}
				if (!deploy) break;
			}
			if (deploy)
			{
				for (int y = i / 10; y <= dy; ++y)
				{
					for (int x = i % 10; x <= dx; ++x)
					{
						invens[y * 10 + x]->SetFill(true);
					}
				}
				prevPosition = invens[i]->GetComponent<Transform>()->GetPosition();
				curInvenIndex = i;
				GetComponent<Transform>()->SetPosition(prevPosition);
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

				
				std::vector<Inven*> invens = mInventory->GetInvens();
				std::vector<InvenItem*> invenItems = mInventory->GetInvenItems();

				for (int i = 0; i < invens.size(); ++i)
				{
					if (invens[i]->GetHover())
					{
						int dx = (i % 10) + (int)itemInvenDisplayScale[(int)mItem][0] - 1;
						int dy = (i / 10) + (int)itemInvenDisplayScale[(int)mItem][1] - 1;

						if (dx < 0 || dx > 9 || dy < 0 || dy > 3) continue;

						bool deployed = true;

						//for (int y = i / 10; y <= dy; ++y)
						//{
						//	for (int x = i % 10; x <= dx; ++x)
						//	{
						//		if (invens[y * 10 + x]->GetFill())
						//		{
						//			deployed = false;
						//		}
						//	}		
						//}
						if (deployed)
						{
							for (int y = i / 10; y <= dy; ++y)
							{
								for (int x = i % 10; x <= dx; ++x)
								{
									invens[y * 10 + x]->SetFill(true);
								}
							}

							int dx_ = (curInvenIndex % 10) + (int)itemInvenDisplayScale[(int)mItem][0] - 1;
							int dy_ = (curInvenIndex / 10) + (int)itemInvenDisplayScale[(int)mItem][1] - 1;

							for (int y = curInvenIndex / 10; y <= dy_; ++y)
							{
								for (int x = curInvenIndex % 10; x <= dx_; ++x)
								{
									invens[y * 10 + x]->SetFill(false);
								}
							}
							GetComponent<Transform>()->SetPosition(invens[i]->GetComponent<Transform>()->GetPosition());
							prevPosition = invens[i]->GetComponent<Transform>()->GetPosition();
							curInvenIndex = i;
							break;
						}
						else
							GetComponent<Transform>()->SetPosition(prevPosition);
					}
				}
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