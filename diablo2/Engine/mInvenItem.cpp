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
		: Item(itemTypeTable[(UINT)item])
		, mInventory(inventory)
		, bSetMouseFollow(false)
		, mItem(item)
	{
		AddComponent<Collider2D>();
		MeshRenderer* mr = AddComponent<MeshRenderer>();

		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(itemNameTable[(UINT)mItem]));

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(27.f * itemInvenDisplayScale[(UINT)mItem][0] * Texture::GetWidRatio(), 27.f * itemInvenDisplayScale[(UINT)mItem][1] * Texture::GetHeiRatio(), 0.f));

		Vector2 thisPosV2 = Vector2(tr->GetPosition().x, tr->GetPosition().y);
		Vector2 thisScaleV2 = Vector2(tr->GetScale().x, tr->GetScale().y);

		std::vector<Inven*> invens = mInventory->GetInvens();

		GameObject* inC = mInventory->GetInvensCollider();
		std::vector<InvenItem*> invenItems = mInventory->GetInvenItems();

		Transform* incTr = inC->GetComponent<Transform>();
		inventoryOutLinePos = Vector2(incTr->GetPosition().x, incTr->GetPosition().y);
		inventoryOutLineScale = Vector2(incTr->GetScale().x, incTr->GetScale().y);

		for (int i = 0; i < invens.size(); ++i)
		{
			bool deploy = true;
			Vector3 invenV3 = invens[i]->GetComponent<Transform>()->GetPosition();
			thisPosV2 = Vector2(invenV3.x , invenV3.y);

			if (invens[i]->GetFill())
			{
				deploy = false;
			}
			if (itemInvenDisplayScale[(UINT)mItem][0] > 1.f
				|| itemInvenDisplayScale[(UINT)mItem][1] > 1.f)
			{
				if (Vector2::RectIndexesIntersectRectIndexes(inventoryOutLinePos, inventoryOutLineScale, thisPosV2, thisScaleV2))
				{
					deploy = false;
				}
				for (InvenItem* item : invenItems)
				{
					Vector2 itemPosV2 = Vector2(item->GetComponent<Transform>()->GetPosition().x,
											 item->GetComponent<Transform>()->GetPosition().y);
					Vector2 itemScaleV2 = Vector2(item->GetComponent<Transform>()->GetScale().x,
											 item->GetComponent<Transform>()->GetScale().y);

					if (Vector2::RectIntersectRect(itemPosV2, itemScaleV2, thisPosV2, thisScaleV2))
					{
						deploy = false;
						break;
					}
				}

			}
			if (deploy)
			{
				prevPosition = invens[i]->GetComponent<Transform>()->GetPosition();
				GetComponent<Transform>()->SetPosition(prevPosition);
				for (int y = 0; y < 4; ++y)
				{
					for (int x = 0; x < 10; ++x)
					{
						Vector3 invenPos = invens[y * 10 + x]->GetComponent<Transform>()->GetPosition();
						Vector3 invenScale = invens[y * 10 + x]->GetComponent<Transform>()->GetScale();
						Vector3 thisPos = GetComponent<Transform>()->GetPosition();
						Vector3 thisScale = GetComponent<Transform>()->GetScale();

						if (Vector3::RectIntersectRect(invenPos, invenScale, thisPos, thisScale))
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
				Vector2 thisPosV2 = Vector2(GetComponent<Transform>()->GetPosition().x,
									GetComponent<Transform>()->GetPosition().y);
				Vector2 thisScaleV2 = Vector2(GetComponent<Transform>()->GetScale().x,
											GetComponent<Transform>()->GetScale().y);

				for (int i = 0; i < invens.size(); ++i)
				{
					if (invens[i]->GetHover())
					{
						
						bool deployed = true;

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
							}
						}
						if (itemInvenDisplayScale[(UINT)mItem][0] > 1.f
							|| itemInvenDisplayScale[(UINT)mItem][1] > 1.f)
						{
							if (Vector2::RectIndexesIntersectRectIndexes(inventoryOutLinePos, inventoryOutLineScale, thisPosV2, thisScaleV2))
							{
								deployed = false;
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

									if (Vector3::RectIntersectRect(invenPos, invenScale, prevPos, thisScale))
									{
										invens[y * 10 + x]->SetFill(false);
									}
								}
							}
							GetComponent<Transform>()->SetPosition(invens[i]->GetComponent<Transform>()->GetPosition());
							prevPosition = invens[i]->GetComponent<Transform>()->GetPosition();

							for (int y = 0; y < 4; ++y)
							{
								for (int x = 0; x < 10; ++x)
								{
									Vector3 invenPos = invens[y * 10 + x]->GetComponent<Transform>()->GetPosition();
									Vector3 invenScale = invens[y * 10 + x]->GetComponent<Transform>()->GetScale();
									Vector3 thisPos = GetComponent<Transform>()->GetScale();
									Vector3 thisScale = GetComponent<Transform>()->GetScale();

									if (Vector3::RectIntersectRect(invenPos, invenScale, thisPos, thisScale))
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
							break;
						}
					}
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