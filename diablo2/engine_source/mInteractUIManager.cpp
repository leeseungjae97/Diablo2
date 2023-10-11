#include "mInteractUIManager.h"

#include "mFontWrapper.h"
#include "mMouseManager.h"
#include "../Engine/mInteractUI.h"
namespace m
{
	InteractUI* InteractUIManager::mShopInteractUI = nullptr;
	InteractUIManager::eInteractUIType InteractUIManager::mCurUIType = InteractUIManager::eInteractUIType::End;
	bool InteractUIManager::bItemHover = false;
	bool InteractUIManager::bItemDrag = false;
	m::math::Vector3 InteractUIManager::mInitPos = Vector3(0.f,0.f,0.f);

    void InteractUIManager::Update()
    {
		if(MouseManager::GetMouseFollow())
		{
			SetInteractUIState(GameObject::NoRenderUpdate);
			return;
		}
		if(mCurUIType != eInteractUIType::ExItem
			&& mCurUIType != eInteractUIType::InvenEx
			&& mCurUIType != eInteractUIType::InvenSellEx)
		{
			if (GetInteractUIState() != GameObject::eState::RenderUpdate) mCurUIType = eInteractUIType::End;
		}
		if (!bItemHover && mCurUIType == eInteractUIType::ExItem)
		{
			SetInteractUIState(GameObject::NoRenderUpdate);
		}
		if (bItemHover && mCurUIType == eInteractUIType::ExItem)
		{
			SetInteractUIState(GameObject::RenderUpdate);
			bItemHover = false;
		}
		if (!bItemHover && mCurUIType == eInteractUIType::InvenSellEx)
		{
			SetInteractUIState(GameObject::NoRenderUpdate);
		}
		if (bItemHover && mCurUIType == eInteractUIType::InvenSellEx)
		{
			SetInteractUIState(GameObject::RenderUpdate);
			bItemHover = false;
		}
		if (!bItemHover && mCurUIType == eInteractUIType::InvenEx)
		{
			SetInteractUIState(GameObject::NoRenderUpdate);
		}
		if (bItemHover && mCurUIType == eInteractUIType::InvenEx)
		{
			SetInteractUIState(GameObject::RenderUpdate);
			bItemHover = false;
		}
    }
	GameObject::eState InteractUIManager::GetInteractUIState()
	{
		if (mShopInteractUI)
			return mShopInteractUI->GetState();
		else return GameObject::eState::NoRenderUpdate;
	}
    void InteractUIManager::SetInteractUIState(GameObject::eState state)
    {
		if(mShopInteractUI)
		    mShopInteractUI->SetState(state);
    }

	void InteractUIManager::SetItemUI(int itemType
                                      , eInteractUIType type
                                      , m::math::Vector3 pos
                                      , bool exBack
                                      , Camera* camera
                                      , float fFontSize
    )
	{
		if (mShopInteractUI
			&& (int)mShopInteractUI->GetItem() == itemType
			&& mCurUIType == type
			&& mInitPos == pos)
			return;

		if (type == eInteractUIType::ExItem && mCurUIType == eInteractUIType::BuyItem) return;

		mCurUIType = type;
		mInitPos = pos;

		if (nullptr == mShopInteractUI)
		{
			mShopInteractUI = new InteractUI(Vector3::Zero, {}, {}, {}, {}, exBack);
			if (nullptr == mShopInteractUI->GetCamera()) mShopInteractUI->SetCamera(camera);
		}

		//SetInteractUIState(GameObject::eState::NoRenderUpdate);

		std::vector<std::wstring> text;
		Vector2 fontMaxSize = Vector2::Zero;
		std::wstring valueStr = L"";
		std::vector<Vector4> vColors = {};
		std::vector<Vector4> vClickColors = {};


		switch (type)
		{
		case eInteractUIType::ExItem:
		{
			std::wstring str = itemCostFunctionNames[itemType][0];

			Vector2 fontSize = FontWrapper::GetTextSize(str.c_str(), fFontSize);
			if (fontMaxSize.x < fontSize.x)
				fontMaxSize.x = fontSize.x;

			fontMaxSize.y += fontSize.y * 2;

			text.push_back(str);
			for (int i = 1; i < 5; ++i)
			{
				str = itemCostFunctionNames[itemType][i];
				if (str == L"") continue;

				valueStr = std::to_wstring(itemFunctionValue[itemType][i - 1]);

				str += valueStr;

				fontSize = FontWrapper::GetTextSize(str.c_str(), fFontSize);

				if (fontMaxSize.x < fontSize.x)
					fontMaxSize.x = fontSize.x;

				fontMaxSize.y += fontSize.y;

				text.push_back(str);
			}
			pos.y += fontMaxSize.y;
		}
		break;
		case eInteractUIType::BuyItem:
		{
			text.push_back(L"구입");
			text.push_back(itemCostFunctionNames[itemType][0]);
			text.push_back(L"골드:" + std::to_wstring(itemFunctionValue[itemType][0]));
			text.push_back(L"네");
			text.push_back(L"아니오");

			Vector2 fontSize = FontWrapper::GetTextSize(text[0].c_str(), fFontSize);
			if (fontMaxSize.x < fontSize.x)
				fontMaxSize.x = fontSize.x;

			fontMaxSize.y += fontSize.y;

			for (std::wstring str : text)
			{
				Vector2 fontSize = FontWrapper::GetTextSize(str.c_str(), fFontSize);
				if (fontMaxSize.x < fontSize.x)
					fontMaxSize.x = fontSize.x;

				fontMaxSize.y += fontSize.y;
			}
			pos.y += fontMaxSize.y;
			vColors = {
				Vector4(148.f, 128.f, 100.f,255.f),
				Vector4(148.f,128.f,100.f,255.f),
				Vector4(148.f,128.f,100.f,255.f),
				Vector4(255.f,255.f,255.f,255.f),
				Vector4(255.f,255.f,255.f,255.f),
			};
			vClickColors = {
				Vector4::Zero,
				Vector4::Zero,
				Vector4::Zero,
				Vector4(80.f,80.f,172.f,255.f),
				Vector4(80.f,80.f,172.f,255.f),
			};
		}
		break;
		case eInteractUIType::BuyFail:
		{

			vColors = {
				Vector4(176.f, 68.f, 52.f,255.f),
				Vector4(255.f,255.f,255.f,255.f),
			};
			vClickColors = {
				Vector4::Zero,
				Vector4(80.f,80.f,172.f,255.f),
			};
			text.push_back(L"거래하기에 충분한 골드를 가지고 있지 않습니다.");
			text.push_back(L"계속");

			Vector2 fontSize = FontWrapper::GetTextSize(text[0].c_str(), fFontSize);
			if (fontMaxSize.x < fontSize.x)
				fontMaxSize.x = fontSize.x;

			fontMaxSize.y += fontSize.y;

			for (std::wstring str : text)
			{
				Vector2 fontSize = FontWrapper::GetTextSize(str.c_str(), fFontSize);
				if (fontMaxSize.x < fontSize.x)
					fontMaxSize.x = fontSize.x;

				fontMaxSize.y += fontSize.y;
			}
			pos = Vector3(0.f, 0.f, pos.z);
		}
		break;
		case eInteractUIType::InvenEx:
		{
			std::wstring str = itemCostFunctionNames[itemType][0];

			Vector2 fontSize = FontWrapper::GetTextSize(str.c_str(), fFontSize);
			if (fontMaxSize.x < fontSize.x)
				fontMaxSize.x = fontSize.x;

			fontMaxSize.y += fontSize.y * 2;

			text.push_back(str);
			for (int i = 2; i < 5; ++i)
			{
				str = itemCostFunctionNames[itemType][i];
				if (str == L"") continue;

				valueStr = std::to_wstring(itemFunctionValue[itemType][i - 1]);

				str += valueStr;

				fontSize = FontWrapper::GetTextSize(str.c_str(), fFontSize);

				if (fontMaxSize.x < fontSize.x)
					fontMaxSize.x = fontSize.x;

				fontMaxSize.y += fontSize.y;

				text.push_back(str);
			}
			pos.y += fontMaxSize.y;
		}break;
		case eInteractUIType::InvenSellEx:
		{
			std::wstring str = itemCostFunctionNames[itemType][0];

			Vector2 fontSize = FontWrapper::GetTextSize(str.c_str(), fFontSize);
			if (fontMaxSize.x < fontSize.x)
				fontMaxSize.x = fontSize.x;

			fontMaxSize.y += fontSize.y * 2;

			text.push_back(str);
			for (int i = 1; i < 5; ++i)
			{
				if(i == 1)
				{
					str = L"판매 가격:";
				}else{
					str = itemCostFunctionNames[itemType][i];
				}
				
				if (str == L"") continue;

				valueStr = std::to_wstring(itemFunctionValue[itemType][i - 1]);

				str += valueStr;

				fontSize = FontWrapper::GetTextSize(str.c_str(), fFontSize);

				if (fontMaxSize.x < fontSize.x)
					fontMaxSize.x = fontSize.x;

				fontMaxSize.y += fontSize.y;

				text.push_back(str);
			}
			pos.y += fontMaxSize.y;
		}break;
		}
		if (nullptr == mShopInteractUI) return;

		mShopInteractUI->SetItem(itemType);
		mShopInteractUI->SetPos(pos);
		mShopInteractUI->SetTextes(text);
		mShopInteractUI->SetNormalColors(vColors);
		mShopInteractUI->SetClickColors(vClickColors);
		mShopInteractUI->SetScale(Vector3(fontMaxSize.x, fontMaxSize.y, 1.f));

		if (exBack)
			mShopInteractUI->ExText();
		else 
			mShopInteractUI->ClickText();

		mShopInteractUI->SetFontSize(fFontSize);

		mShopInteractUI->ReMakeInteractContents();
	}
}
