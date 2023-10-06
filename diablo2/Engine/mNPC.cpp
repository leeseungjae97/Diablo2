#include "mNPC.h"

#include "../engine_source/mFontWrapper.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/mLight.h"

#include "mButton.h"
#include "mNPCScript.h"
#include "mShop.h"
#include "mInteractUI.h"
#include "mShadowObject.h"

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

		mShadow = new ShadowObject(this);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Shadow, mShadow);

		Light* lightComp = AddComponent<Light>();
		lightComp->SetType(eLightType::Point);
		lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 0.2f));
		lightComp->SetRadiusX(100.0f);
		lightComp->SetRadiusY(50.0f);
	}

	NPC::~NPC()
	{
		if (mShadow)
			mShadow->SetState(eState::Delete);
		if(mInteractUI)
			mInteractUI->SetState(eState::Delete);
	}

	void NPC::Update()
	{
		MoveAbleObject::Update();
		if (mShadow && nullptr == mShadow->GetCamera()) mShadow->SetCamera(GetCamera());
		if (mShadow) mShadow->SetState(GetState());

		if (nullptr == mInteractUI->GetCamera())
		{
			mInteractUI->SetCamera(GetCamera());
		}

		if (GetHover()
			|| mInteractUI->GetHover())
		{
			if (Input::GetKeyDown(eKeyCode::LBUTTON))
			{
				if (mInteractUI->GetState() == eState::NoRenderNoUpdate
					|| mInteractUI->GetState() == eState::NoRenderUpdate)
				{
					remakeUI();
					mInteractUI->SetState(eState::RenderUpdate);
				}
			}
		}
	    if (!GetHover() && !mInteractUI->GetHover())
		{
			if (Input::GetKeyDown(eKeyCode::LBUTTON))
			    mInteractUI->SetState(eState::NoRenderUpdate);
		}

		if(mInteractUI && mInteractUI->GetState() == RenderUpdate)
		    mInteractUI->SetState(GetState());

		if (mInteractUI)
		{
			Vector3 pos = GET_POS(this);
			pos.y += NPCSizes[(int)mNPCType].y * 2.f;
			SET_POS_VEC(mInteractUI, pos);
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

    void NPC::remakeUI()
    {
		if (mInteractUI)
			mInteractUI->ReMakeInteractContents();
    }
}
