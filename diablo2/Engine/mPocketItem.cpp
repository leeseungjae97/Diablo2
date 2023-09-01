#include "mPocketItem.h"

#include "mMeshRenderer.h"

#include "../engine_source/mMouseManager.h"

namespace m
{
    PocketItem::PocketItem(eItem item)
        : Item(item)
    {
        ADD_COMP(this, Collider2D);
        ADD_COMP(this, MeshRenderer);

        SET_MESH(this, L"RectMesh");
        SET_MATERIAL(this, itemNameTable[(UINT)item]);

        SET_SCALE_XYZ(this, 27.f * itemInvenDisplayScale[(UINT)item][0] * Texture::GetWidRatio()
            , 27.f * itemInvenDisplayScale[(UINT)item][1] * Texture::GetHeiRatio(), 0.f);
    }

    PocketItem::~PocketItem()
    {
    }

    void PocketItem::Initialize()
    {
        Item::Initialize();
    }

    void PocketItem::Update()
    {
        Item::Update();
        //if (GetHover())
        //{
        //    if (Input::GetKeyDownOne(eKeyCode::LBUTTON))
        //    {
        //        //DeployItem();
        //        SetMouseFollow(GetMouseFollow() ? false : true);
        //    }
        //    if (GetMouseFollow())
        //    {
        //        MouseManager::SetMouseFollow(this);
        //        MAKE_POS(pos, this);

        //        Vector3 unprojMousePos = MouseManager::UnprojectionMousePos(pos.z, GetCamera());
        //        unprojMousePos.z = pos.z;
        //        SET_POS_VEC(this, unprojMousePos);
        //    }
        //    else MouseManager::SetMouseFollow(nullptr);
        //}
    }

    void PocketItem::LateUpdate()
    {
        Item::LateUpdate();
    }

    void PocketItem::Render()
    {
        Item::Render();
    }
}
