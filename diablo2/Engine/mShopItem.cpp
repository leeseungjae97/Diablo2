#include "mShopItem.h"

#include "mMeshRenderer.h"

namespace m
{
    ShopItem::ShopItem(eItem item)
        : Item(item)
    {
        ADD_COMP(this, Collider2D);
        ADD_COMP(this, MeshRenderer);

        SET_MESH(this, L"RectMesh");
        SET_MATERIAL(this, itemNameTable[(UINT)item]);

        SET_SCALE_XYZ(this, 27.f * itemInvenDisplayScale[(UINT)item][0] * Texture::GetWidRatio()
            , 27.f * itemInvenDisplayScale[(UINT)item][1] * Texture::GetHeiRatio(), 0.f);
    }

    ShopItem::~ShopItem()
    {
    }

    void ShopItem::Initialize()
    {
        Item::Initialize();
    }

    void ShopItem::Update()
    {
        Item::Update();
    }

    void ShopItem::LateUpdate()
    {
        Item::LateUpdate();
    }

    void ShopItem::Render()
    {
        Item::Render();
    }
}
