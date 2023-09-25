#include "mTalkUI.h"

#include "../engine_source/mMeshRenderer.h"

namespace m
{
    TalkUI::TalkUI(Vector3 initPos, eNPCType type)
        : mMenus(NPCMenus[(int)type])
    {
        //std::wstring* menus;
        SET_MESH(this, L"RectMesh");
        SET_MATERIAL(this, L"talkUI");
        initPos.z -= 0.0001f;
        SET_SCALE_XYZ(this, 100.f, 100.f, 1.f);
        SET_POS_VEC(this, initPos);
    }

    TalkUI::~TalkUI()
    {
    }

    void TalkUI::Initialize()
    {
        UI::Initialize();
    }

    void TalkUI::Update()
    {
        UI::Update();
        if(GetHover())
        {
            
        }else
        {
            if (Input::GetKeyDown(eKeyCode::LBUTTON)
                || Input::GetKeyDown(eKeyCode::RBUTTON))
            {
                SetState(eState::NoRenderNoUpdate);
            }
        }
    }

    void TalkUI::LateUpdate()
    {
        UI::LateUpdate();
    }

    void TalkUI::Render()
    {
        UI::Render();
    }
    void TalkUI::makePositionToUICamera()
    {
        //Vector3 pp = GetComponent<Transform>()->ProjectionCetnerPosition(fontSize);
    }
}
