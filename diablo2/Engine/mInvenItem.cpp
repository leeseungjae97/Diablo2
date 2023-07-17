#include "mInvenItem.h"
#include "..\engine_source\mInput.h"
#include "..\engine_source\mApplication.h"
#include "..\engine_source\mTransform.h"
#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mCollider2D.h"

#include "mItemPlaced.h"
#include "mInven.h"


namespace m
{
	InvenItem::InvenItem(eItem item, ItemPlaced* inventory)
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
		tr->SetScale(Vector3(27.f * itemInvenDisplayScale[(int)mItem][0] * Texture::GetWidRatio(), 27.f * itemInvenDisplayScale[(int)mItem][1] * Texture::GetHeiRatio(), 0.f));
		Vector3 scale = tr->GetScale();

		std::vector<Inven*> invens = mInventory->GetInvens();
		//GameObject* inC = mInventory->GetInvensCollider();
		for (int i = 0; i < invens.size(); ++i)
		{
			int dx = (i % 10) + (int)itemInvenDisplayScale[(int)mItem][0] - 1;
			int dy = (i / 10) + (int)itemInvenDisplayScale[(int)mItem][1] - 1;

			if (dx < 0 || dx > 9 || dy < 0 || dy > 3) continue;
			
			bool deploy = true;

			for (int y = i; y <= dy; ++y)
			{
				for (int x = i; x <= dx; ++x)
				{
					if (invens[y * 10 + x]->GetFill()
/*						|| inC->GetComponent<Collider2D>()->GetOnStay()
						|| inC->GetComponent<Collider2D>()->GetOnEnter()*/ )
					{
						deploy = false;
						break;
					}
				}
				if (!deploy) break;
			}
			if (deploy)
			{
				prevPosition = invens[i]->GetComponent<Transform>()->GetPosition();
				curInvenIndex = i;
				GetComponent<Transform>()->SetPosition(prevPosition);
				for (int y = 0; y < 4; ++y)
				{
					for (int x = 0; x < 10; ++x)
					{
						Vector3 invenPos = invens[y * 10 + x]->GetComponent<Transform>()->GetPosition();
						Vector3 invenScale = invens[y * 10 + x]->GetComponent<Transform>()->GetScale();
						Vector3 thisPos = GetComponent<Transform>()->GetPosition();
						Vector3 thisScale = GetComponent<Transform>()->GetScale();

						if (Vector3::Vector2RectIntersectRect(invenPos, invenScale, thisPos, thisScale))
						{
							invens[y * 10 + x]->SetFill(true);
						}
					}
				}
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
				std::vector<Inven*> invens = mInventory->GetInvens();
				std::vector<InvenItem*> invenItems = mInventory->GetInvenItems();
				//GameObject* inC = mInventory->GetInvensCollider();

				for (int i = 0; i < invens.size(); ++i)
				{
					if (invens[i]->GetHover())
					{
						//int dx = (i % 10) + (int)itemInvenDisplayScale[(int)mItem][0] - 1;
						//int dy = (i / 10) + (int)itemInvenDisplayScale[(int)mItem][1] - 1;

						//if (dx < 0 || dx > 9 || dy < 0 || dy > 3) continue;

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
						//if (inC->GetComponent<Collider2D>()->GetOnStay()
						//	|| inC->GetComponent<Collider2D>()->GetOnEnter())
						//{
						//	deployed = false;
						//}
						int intersectItemCnt = 0;
						for (InvenItem* item : invenItems)
						{
							if (item->GetComponent<Collider2D>()->GetOnStay()
								|| item->GetComponent<Collider2D>()->GetOnEnter())
							{
								intersectItemCnt++;
							}
							if (intersectItemCnt > 2)
							{
								deployed = false;
								break;
							}
						}
						if (deployed)
						{
							for (int y = 0; y < 4; ++y)
							{
								for (int x = 0; x < 10; ++x)
								{
									Vector3 invenPos = invens[y * 10 + x]->GetComponent<Transform>()->GetPosition();
									Vector3 invenScale = invens[y * 10 + x]->GetComponent<Transform>()->GetScale();
									Vector3 prevPos = prevPosition;
									Vector3 thisScale = GetComponent<Transform>()->GetScale();

									if (Vector3::Vector2RectIntersectRect(invenPos, invenScale, prevPos, thisScale))
									{
										invens[y * 10 + x]->SetFill(false);
									}
								}
							}
							GetComponent<Transform>()->SetPosition(invens[i]->GetComponent<Transform>()->GetPosition());
							prevPosition = invens[i]->GetComponent<Transform>()->GetPosition();
							curInvenIndex = i;

							for (int y = 0; y < 4; ++y)
							{
								for (int x = 0; x < 10; ++x)
								{
									Vector3 invenPos = invens[y * 10 + x]->GetComponent<Transform>()->GetPosition();
									Vector3 invenScale = invens[y * 10 + x]->GetComponent<Transform>()->GetScale();
									Vector3 thisPos = GetComponent<Transform>()->GetScale();
									Vector3 thisScale = GetComponent<Transform>()->GetScale();

									if (Vector3::Vector2RectIntersectRect(invenPos, invenScale, thisPos, thisScale))
									{
										invens[y * 10 + x]->SetFill(true);
									}
								}
							}
							break;

						}
						else
						{
							GetComponent<Transform>()->SetPosition(prevPosition);
						}
					}
					else
						GetComponent<Transform>()->SetPosition(prevPosition);
				}
				bSetMouseFollow = bSetMouseFollow ? false : true;
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