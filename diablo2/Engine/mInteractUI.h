#pragma once
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

        void SetOwnerScale(Vector2 scale) { mOwnerScale = scale; }

        void SetShop(Shop* shop) { mShop = shop; }
        void ExText() { bExText = true; }
    private:
        void makeInteractContents();
    private:
        std::vector<std::wstring> mMenus;
        std::vector<Vector4> mColors;
        std::vector<Vector4> mClickColors;
        std::vector<Button*> textes;
        Shop* mShop;
        Vector2 mOwnerScale;

        float fFontSize;
        bool bExText;
    };
}

