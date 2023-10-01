#include "mPortal.h"

#include "mFontWrapper.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mSceneManager.h"

#include "mPortalScript.h"
#include "mUI.h"

namespace m
{
    Portal::Portal()
    {
        ADD_COMP(this, MeshRenderer);
        ADD_COMP(this, Animator);
        SET_MESH(this, L"RectMesh");
        SET_MATERIAL(this, L"AnimationMaterial");
        SET_SCALE_XYZ(this, 204.f, 204.f, 1.f);
        AddComponent<PortalScript>();

        mHoverUI = new UI();
        SET_MESH(mHoverUI, L"RectMesh");
        SET_MATERIAL(mHoverUI, L"itemExBack");
        mHoverUI->SetTextSize(15.f);
        mHoverUI->SetText(L"다음 스테이지로 이동");
        mHoverUI->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));

        Vector2 fontSize = FontWrapper::GetTextSize(mHoverUI->GetText().c_str(), 15.f);

        SET_SCALE_XYZ(mHoverUI, fontSize.x, fontSize.y, 1.f);
        mHoverUI->SetState(eState::NoRenderUpdate);
        SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, mHoverUI);
    }

    Portal::~Portal()
    {
        if (mHoverUI)
            mHoverUI->SetState(eState::Delete);
    }

    void Portal::Initialize()
    {
        GameObject::Initialize();
    }

    void Portal::Update()
    {
        GameObject::Update();
        if (mHoverUI && nullptr == mHoverUI->GetCamera()) { mHoverUI->SetCamera(GetCamera()); }

        Vector3 pos = GET_POS(this);
        pos.y += 204.f / 2.f;
        SET_POS_VEC(mHoverUI, pos);
        if(GetState() == RenderUpdate())
        {
            if(GetHover())
            {
                mHoverUI->SetState(GetState());
                if(Input::GetKeyDown(eKeyCode::LBUTTON))
                {
                    if (mHoverUI)
                        mHoverUI->SetState(NoRenderNoUpdate);
                    fClickPortal();
                }
            }
            else
            {
                if (mHoverUI)
                    mHoverUI->SetState(NoRenderNoUpdate);
            }
        }
    }

    void Portal::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void Portal::Render()
    {
        GameObject::Render();
    }

    void Portal::ActivePortal()
    {
        PortalScript* ps = GetComponent<PortalScript>();

        if (ps)
            ps->Portal();
    }

    void Portal::ResetPortal()
    {
        PortalScript* ps = GetComponent<PortalScript>();
        if(ps)
            ps->ResetPortal();
    }
}
