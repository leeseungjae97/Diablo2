#include "mInteractUI.h"

#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/mFontWrapper.h"
#include "../engine_source/mStashManager.h"

#include "mButton.h"
#include "mInteractUIManager.h"
#include "mInvenItem.h"
#include "mItemScript.h"
#include "mPlayerManager.h"
#include "mShop.h"

namespace m
{
	InteractUI::InteractUI(Vector3 initPos
		, std::vector<std::wstring> menus
		, std::vector<Vector4> colors
		, std::vector<Vector4> clickColors
		, Vector3 size
		, bool exBack
		, float fontSize
	)
		: mMenus(menus)
	    , fFontSize(fontSize)
	    , mColors(colors)
	    , mClickColors(clickColors)
	    , mMenuCount(0)
	{
		SET_MESH(this, L"RectMesh");
		if(!exBack)
		    SET_MATERIAL(this, L"talkUI");
		else
			SET_MATERIAL(this, L"itemExBack");

		initPos.z -= 0.1f;
		SET_SCALE_VEC(this, size);
		SET_POS_VEC(this, initPos);

		SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, this);
		if(!menus.empty())
		    MakeInteractContents();
	}

	InteractUI::~InteractUI()
	{
	}

	void InteractUI::Initialize()
	{
		UI::Initialize();
	}

	void InteractUI::Update()
	{
		UI::Update();
		if (!textes.empty() && nullptr == textes[0]->GetCamera())
		{
			for (UI* ui : textes) ui->SetCamera(GetCamera());
		}
		for (Button* button : textes)
		{
			if (button->GetOneClick())
			{
				std::wstring text = button->GetText();
				if (text.compare(L"거래") == 0)
				{
					mShop->SetState(eState::RenderUpdate);
				}
				if (text.compare(L"네") == 0)
				{
					if (PlayerManager::BuyItem(itemFunctionValue[(int)mBuyItem][0]))
					{
						InvenItem* item = new InvenItem(mBuyItem);
						item->SetCamera(GetCamera());
						item->SetState(GameObject::RenderUpdate);
						ADD_COMP(item, ItemScript);
						SceneManager::GetActiveScene()->AddGameObject(eLayerType::Item, item);
						StashManager::AddItem(item, StashManager::eStashType::Inventory);
						StashManager::AddItemTetris(item, StashManager::eStashType::Inventory);
					}
					SetState(eState::NoRenderUpdate);
				}
				if (text.compare(L"취소") == 0
					|| text.compare(L"아니오") == 0
					|| text.compare(L"계속") == 0)
				{
					SetState(eState::NoRenderUpdate);
					//InteractUIManager::
				}
			}
		}
	
		for (int i = 0 ; i < textes.size(); ++i)
		{
			if(i >= mMenuCount)
				textes[i]->SetState(NoRenderUpdate);
			else
			    textes[i]->SetState(GetState());
		}
	}

	void InteractUI::LateUpdate()
	{
		UI::LateUpdate();
	}

	void InteractUI::Render()
	{
		UI::Render();
	}

    void InteractUI::ExText()
    {
		SET_MATERIAL(this, L"itemExBack");
    }

    void InteractUI::ClickText()
    {
		SET_MATERIAL(this, L"talkUI");
    }


    void InteractUI::SetScale(Vector3 size)
    {
		SET_SCALE_VEC(this, size);
    }

    void InteractUI::SetPos(Vector3 pos)
    {
		SET_POS_VEC(this, pos);
    }
	void InteractUI::ReMakeInteractContents()
	{
		float indent = 5.f;
		Vector3 initPos = GET_POS(this);
		Vector3 uiPos = GET_POS(this);
		uiPos.y += GET_SCALE(this).y / 2.f;
		for (Button* b : textes) b->SetState(eState::NoRenderUpdate);

		mMenuCount = 0;
		for (int i = 0; i < mMenus.size(); ++i)
		{
			std::wstring menuName = mMenus[i];
			if (menuName == L"") continue;

			if(textes.size() <= mMenuCount)
			{
				Button* _menu = new Button();
				SET_MESH(_menu, L"RectMesh");
				SET_MATERIAL(_menu, L"noneRect");
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, _menu);
				textes.push_back(_menu);
			}
			
			Button* menu = textes[mMenuCount];
			menu->SetText(menuName);
			menu->SetState(eState::NoRenderUpdate);
			menu->SetTextSize(fFontSize);
			++mMenuCount;

			if (!mColors.empty())
			{
				menu->SetTextNormalColor(mColors[i]);
			}
			else
			{
				menu->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
			}

			if (!mClickColors.empty())
			{
				if (mClickColors[i] != Vector4::Zero)
					menu->SetTextClickColor(mClickColors[i]);
			}

			Vector2 fontSize = FontWrapper::GetTextSize(menuName.c_str(), 10.f);

			uiPos.y -= fontSize.y;
			uiPos.y -= indent;

			SET_SCALE_XYZ(menu, fontSize.x, fontSize.y, 1.f);
			SET_POS_XYZ(menu, initPos.x, uiPos.y, initPos.z - 0.1f);
		}
	}
	void InteractUI::MakeInteractContents()
	{
		float indent = 5.f;
		Vector3 initPos = GET_POS(this);
		Vector3 uiPos = GET_POS(this);
		uiPos.y += GET_SCALE(this).y / 2.f;

		mMenuCount = 0;
		for (int i = 0; i < mMenus.size(); ++i)
		{
			
			std::wstring menuName = mMenus[i];
			if (menuName == L"") continue;

			++mMenuCount;

			Button* menu = new Button();
			menu->SetText(menuName);
			menu->SetState(eState::NoRenderUpdate);
			menu->SetTextSize(fFontSize);
			if (!mColors.empty())
			{
				menu->SetTextNormalColor(mColors[i]);
			}
			else
			{
				menu->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
			}

			if (!mClickColors.empty())
			{
				if (mClickColors[i] != Vector4::Zero)
					menu->SetTextClickColor(mClickColors[i]);
			}

			SET_MESH(menu, L"RectMesh");
			SET_MATERIAL(menu, L"noneRect");

			Vector2 fontSize = FontWrapper::GetTextSize(menuName.c_str(), 10.f);

			uiPos.y -= fontSize.y;
			uiPos.y -= indent;

			SET_SCALE_XYZ(menu, fontSize.x, fontSize.y, 1.f);
			SET_POS_XYZ(menu, initPos.x, uiPos.y, initPos.z - 0.1f);

			SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, menu);
			textes.push_back(menu);
		}
	}
}
