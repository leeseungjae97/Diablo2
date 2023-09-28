#include "mNPC.h"

#include "../engine_source/mFontWrapper.h"
#include "../engine_source/mSceneManager.h"

#include "mButton.h"
#include "mNPCScript.h"
#include "mShop.h"
#include "mInteractUI.h"

namespace m
{
	NPC::NPC(Vector3 initPos, eNPCType type)
		:MoveAbleObject(
			initPos,
			0.f,
			false,
			false,
			false,
			false)
		, mNPCType(type)
	{
		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");

		ADD_COMP(this, Animator);

		AddComponent<NPCScript>(mNPCType);

		makeUI();
	}

	NPC::~NPC()
	{
	}

	void NPC::Update()
	{
		MoveAbleObject::Update();
		if (nullptr == mInteractUI->GetCamera())
		{
			mInteractUI->SetCamera(GetCamera());
		}

		if (GetHover()
			|| mInteractUI->GetHover())
		{
			if (Input::GetKeyDown(eKeyCode::LBUTTON))
			{
				if (mInteractUI->GetState() == eState::NoRenderUpdate)
				{
					mInteractUI->SetState(eState::RenderUpdate);
				}
			}
		}else
		{
			if (Input::GetKeyDown(eKeyCode::LBUTTON))
			    mInteractUI->SetState(eState::NoRenderUpdate);
		}

		//for (Button* button : textes) button->SetState(mInteractUI->GetState());
	
	}

	void NPC::LateUpdate()
	{
		MoveAbleObject::LateUpdate();
	}

	void NPC::Initialize()
	{
		MoveAbleObject::Initialize();
	}

	void NPC::Render()
	{
		MoveAbleObject::Render();
	}

	void NPC::Hit(int damage, bool attackStun)
	{
	}

    void NPC::SetShop(Shop* shop)
    {
		mShop = shop;
		if (mInteractUI)
			mInteractUI->SetShop(shop);
    }

    void NPC::makeUI()
	{
		std::vector<std::wstring> texts;
		texts.push_back(NPCNames[(int)mNPCType]);
		texts.push_back(NPCMenus[(int)mNPCType][0]);
		texts.push_back(NPCMenus[(int)mNPCType][1]);
		texts.push_back(NPCMenus[(int)mNPCType][2]);
		texts.push_back(NPCMenus[(int)mNPCType][3]);

		//Camera* camera =SceneManager::GetActiveScene()->GetSceneUICamera();
		//Camera* camera = SceneManager::GetActiveScene()->GetSceneMainCamera();
		//Vector3 uiPos = GET_COMP(this, Transform)->TransPositionOtherCamera(camera);;
		Vector3 uiPos = GET_POS(this);
		//Vector3 uiPos = Vector3(0, 0, 0);

		uiPos.y += NPCSizes[(int)mNPCType].y * 2.f;

		std::vector<Vector4> vClickColors = {
	        Vector4::Zero,
			Vector4(80.f,80.f,172.f,255.f),
			Vector4(80.f,80.f,172.f,255.f),
			Vector4::Zero,
			Vector4::Zero,
		};
		std::vector<Vector4> vColors = {
	        Vector4(148.f, 128.f, 100.f,255.f),
	        Vector4(255.f,255.f,255.f,255.f),
	        Vector4(255.f,255.f,255.f,255.f),
	        Vector4(255.f,255.f,255.f,255.f),
	        Vector4::Zero,
		};

		mInteractUI = new InteractUI(uiPos, texts, vColors, vClickColors);
		mInteractUI->SetState(eState::NoRenderUpdate);
	}
}
