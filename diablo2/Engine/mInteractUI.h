#pragma once
#include "ItemLookUpTables.h"
#include "mUI.h"

#include "../engine_source/NPCLookUpTables.h"

namespace m
{
    class Shop;
    class Button;

    class InteractUI :
        public UI
    {
    public:
        InteractUI(Vector3 initPos, std::vector<std::wstring> menus
            , std::vector<Vector4> colors = {}
            , std::vector<Vector4> clickColors = {}
            , Vector3 size = Vector3(100.f, 100.f, 1.f)
            , bool exBack = false, float fontSize = 15.f);
        virtual ~InteractUI();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetItem(eItem item) { mBuyItem = item; }
        void SetItem(int item) { mBuyItem = (eItem)item; }

        eItem GetItem() { return mBuyItem; }

        void SetShop(Shop* shop) { mShop = shop; }
        void ExText();
        void ClickText();
        void SetTextes(std::vector<std::wstring> text) { mMenus = text; }
        void SetNormalColors(const std::vector<m::math::Vector4>& vector) { mColors = vector; }
        void SetClickColors(const std::vector<m::math::Vector4>& vector) { mClickColors = vector; }
        void SetScale(Vector3 size);
        void SetFontSize(float font_size) { fFontSize = font_size; }
        void SetPos(Vector3 pos);
        void ReMakeInteractContents();
        void MakeInteractContents();

    private:
        std::vector<std::wstring> mMenus;
        std::vector<Vector4> mColors;
        std::vector<Vector4> mClickColors;
        std::vector<Button*> textes;
        int mMenuCount;

        Shop* mShop;

        float fFontSize;

        eItem mBuyItem;

    };
}

