#include "mInteractUI.h"

#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/mFontWrapper.h"

#include "mButton.h"
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
		, bExText(exBack)
	    , fFontSize(fontSize)
	    , mColors(colors)
	    , mClickColors(clickColors)
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
		makeInteractContents();
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
		if (nullptr == textes[0]->GetCamera())
		{
			for (UI* ui : textes) ui->SetCamera(GetCamera());
		}
		if (!bExText)
		{
			for (Button* button : textes)
			{

				if (button->GetClick())
				{
					std::wstring text = button->GetText();
					if (text == L"°Å·¡")
					{
						mShop->SetState(eState::RenderUpdate);
					}
					SetState(eState::NoRenderUpdate);
				}
			}
		}
		

		for (Button* button : textes) button->SetState(GetState());
	}

	void InteractUI::LateUpdate()
	{
		UI::LateUpdate();
	}

	void InteractUI::Render()
	{
		UI::Render();
	}
	void InteractUI::makeInteractContents()
	{
		float indent = 5.f;
		Vector3 initPos = GET_POS(this);
		Vector3 uiPos = GET_POS(this);
		uiPos.y += GET_SCALE(this).y / 2.f;

		int iInitValue = 0;
		if(!bExText)
		{
			iInitValue = 1;
			Button* npcName = new Button();
			npcName->SetText(mMenus[0]);
			npcName->SetTextSize(fFontSize);

			if(!mColors.empty())
			{
				if(mColors[0] != Vector4::Zero)
				    npcName->SetTextNormalColor(mColors[0]);
			}else
			{
				npcName->SetTextNormalColor(Vector4(148.f, 128.f, 100.f, 255.f));
			}
			if(!mClickColors.empty())
			{
				if (mClickColors[0] != Vector4::Zero)
					npcName->SetTextClickColor(mClickColors[0]);
			}
			

			SET_MESH(npcName, L"RectMesh");
			SET_MATERIAL(npcName, L"noneRect");

			Vector2 fontSize = FontWrapper::GetTextSize(mMenus[0].c_str(), 10.f);

			uiPos.y -= fontSize.y;
			uiPos.y -= indent;

			SET_SCALE_XYZ(npcName, fontSize.x, fontSize.y, 1.f);
			SET_POS_XYZ(npcName, initPos.x, uiPos.y, initPos.z - 0.1f);

			SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, npcName);
			textes.push_back(npcName);
		}

		for (int i = iInitValue; i < mMenus.size(); ++i)
		{
			std::wstring menuName = mMenus[i];
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
