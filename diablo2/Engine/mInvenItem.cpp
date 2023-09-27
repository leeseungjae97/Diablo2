#include "mInvenItem.h"

#include "../engine_source/mInput.h"
#include "../engine_source/mApplication.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mCollider2D.h"
#include "../engine_source/mStashManager.h"
#include "../engine_source/mFontWrapper.h"
#include "../engine_source/mMouseManager.h"
#include "../engine_source/ItemLookUpTables.h"

#include "mEmptyRect.h"
#include "mInteractUI.h"
#include "mInteractUIManager.h"
#include "mPosionScript.h"


namespace m
{
	InvenItem::InvenItem(eItem item)
		: Item(item)
		, bDoItemFunction(false)
		, bMakeUI(false)
	{
		eItemType type = itemTypeTable[(UINT)item];

		if (type == eItemType::Posion)
		{
			PosionScript* pis = ADD_COMP(this, PosionScript);
			pis->SetOwnerItem(item);
		}

		ADD_COMP(this, Collider2D);
		ADD_COMP(this, MeshRenderer);

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, itemNameTable[(UINT)item]);

		SET_POS_XYZ(this, -10.f, -10.f, -1.f);
		SET_SCALE_XYZ(this, 27.f * itemInvenDisplayScale[(UINT)item][0] * Texture::GetWidRatio()
			, 27.f * itemInvenDisplayScale[(UINT)item][1] * Texture::GetHeiRatio(), 0.f);

		prevPosition = GET_POS(this);
	}
	InvenItem::~InvenItem()
	{
	}
	void InvenItem::Initialize()
	{
		Item::Initialize();
	}
	void InvenItem::Update()
	{
		Item::Update();
		//if (nullptr != mExItemUI && nullptr == mExItemUI->GetCamera()) mExItemUI->SetCamera(GetCamera());
		//if (nullptr != mBuyDcUI && nullptr == mBuyDcUI->GetCamera()) mBuyDcUI->SetCamera(GetCamera());

		if (GetHover())
		{
			if (bShopItem)
			{
				if(InteractUIManager::mCurUIType != InteractUIManager::eInteractUIType::BuyItem)
				{
					InteractUIManager::SetItemUI((int)mItem
						, InteractUIManager::eInteractUIType::ExItem
						, GET_POS(this)
						, true
						, GetCamera()
						, 15.f
					);
				}

				InteractUIManager::bItemHover = true;
			}
			if (Input::GetKeyDownOne(eKeyCode::LBUTTON))
			{
				if (!bShopItem)
					SetMouseFollow(GetMouseFollow() ? false : true);
				else
				{
					InteractUIManager::SetItemUI((int)mItem
						, InteractUIManager::eInteractUIType::BuyItem
						, GET_POS(this)
						, false
					    , GetCamera()
						, 15.f
					);
				}
			}
		}
		if (!bShopItem)
		{
			if (GetMouseFollow())
			{
				MouseManager::SetMouseFollow(this);
			}
			else
			{
				if (this == MouseManager::GetMouseFollow())
					MouseManager::FreeMouseFollow();
			}
		}

		//if (bShopItem)
		//{
		//	if (!bMakeUI)
		//		makeItemExUI();
		//}
	}
	void InvenItem::LateUpdate()
	{
		Item::LateUpdate();
	}
	void InvenItem::Render()
	{
		Item::Render();
	}


	void InvenItem::makeItemExUI()
	{
	//	bMakeUI = true;

	//	Vector3 pos = GET_POS(this);
	//	std::vector<std::wstring> options;
	//	std::wstring valueStr = L"";
	//	Vector2 fontMaxSize = Vector2::Zero;

	//	std::wstring str = itemCostFunctionNames[(int)mItem][0];
	//	Vector2 fontSize = FontWrapper::GetTextSize(str.c_str(), 15.f);
	//	if (fontMaxSize.x < fontSize.x)
	//		fontMaxSize.x = fontSize.x;

	//	fontMaxSize.y += fontSize.y * 2;
	//	options.push_back(str);
	//	for (int i = 1; i < 5; ++i)
	//	{
	//		str = itemCostFunctionNames[(int)mItem][i];
	//		if (str == L"") continue;

	//		valueStr = std::to_wstring(itemFunctionValue[(int)mItem][i - 1]);

	//		str += valueStr;

	//		fontSize = FontWrapper::GetTextSize(str.c_str(), 15.f);

	//		if (fontMaxSize.x < fontSize.x)
	//			fontMaxSize.x = fontSize.x;

	//		fontMaxSize.y += fontSize.y;

	//		options.push_back(str);
	//	}
	//	pos.y += fontMaxSize.y;

	//	mExItemUI = new InteractUI(pos, options, {}, {}, Vector3(fontMaxSize.x, fontMaxSize.y, 1.f), true);

	//	std::vector<std::wstring> wsBuyText;
	//	wsBuyText.push_back(L"구입");
	//	wsBuyText.push_back(itemCostFunctionNames[(int)mItem][0]);
	//	wsBuyText.push_back(L"골드:" + std::to_wstring(itemFunctionValue[(int)mItem][0]));
	//	wsBuyText.push_back(L"네");
	//	wsBuyText.push_back(L"아니오");

	//	pos = GET_POS(this);
	//	fontMaxSize = Vector2::Zero;

	//	for (std::wstring str : wsBuyText)
	//	{
	//		fontSize = FontWrapper::GetTextSize(str.c_str(), 15.f);
	//		if (fontMaxSize.x < fontSize.x)
	//			fontMaxSize.x = fontSize.x;

	//		fontMaxSize.y += fontSize.y;
	//	}
	//	pos.y += fontMaxSize.y;
	//	std::vector<Vector4> vColors = {
	//		Vector4(148.f, 128.f, 100.f,255.f),
	//		Vector4(148.f,128.f,100.f,255.f),
	//		Vector4(148.f,128.f,100.f,255.f),
	//		Vector4(255.f,255.f,255.f,255.f),
	//		Vector4(255.f,255.f,255.f,255.f),
	//	};
	//	std::vector<Vector4> vClickColors = {
	//		Vector4::Zero,
	//		Vector4::Zero,
	//		Vector4::Zero,
	//		Vector4(80.f,80.f,172.f,255.f),
	//		Vector4(80.f,80.f,172.f,255.f),
	//	};

	//	mBuyDcUI = new InteractUI(pos, wsBuyText, vColors, vClickColors, Vector3(fontMaxSize.x, fontMaxSize.y, 1.f));
	//	mBuyDcUI->SetState(NoRenderUpdate);
	//	mBuyDcUI->SetItem(mItem);
	}
}
