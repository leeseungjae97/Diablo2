#include "mNPC.h"

#include "mNPCScript.h"
#include "mSceneManager.h"
#include "mTalkUI.h"

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

		initPos.y += NPCSizes[(int)type].y;



		mTalkUI = new TalkUI(initPos, type);
		mTalkUI->SetCamera(SceneManager::GetActiveScene()->GetSceneUICamera());
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, mTalkUI);
	}

	NPC::~NPC()
	{
	}

	void NPC::Update()
	{
		MoveAbleObject::Update();
		//if (nullptr == mTalkUI->GetCamera()) mTalkUI->SetCamera(GetCamera());

		if (GetHover())
		{
			if (Input::GetKeyDown(eKeyCode::LBUTTON))
			{
				mTalkUI->SetState(eState::RenderUpdate);
			}
		}else
		{
			if (Input::GetKeyDown(eKeyCode::LBUTTON))
			{
				mTalkUI->SetState(eState::NoRenderUpdate);
			}
		}
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
}
