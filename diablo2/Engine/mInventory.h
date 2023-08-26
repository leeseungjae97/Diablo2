#pragma once
#include "../engine_source/mUI.h"
#include "mInvenItem.h"
#include "mInven.h"
namespace m
{
    class Button;
    class Inventory :
        public UI
    {
    public:
        Inventory(Camera* camera);
        virtual ~Inventory();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        std::vector<Inven*>& GetInvens() { return invens; }
        std::vector<Inven*>& GetEquiments() { return equiments; }
        std::vector<InvenItem*>& GetInvenItems() { return invenItems; }
        Inven* GetInvensCollider() { return invensCollider; }

    private:
        Inven* invensCollider;
        std::vector<Inven*> invens;
        std::vector<Inven*> equiments;
        std::vector<InvenItem*> invenItems; // x 28 y 28
        Inven* invenWeapon1Left;   // x 60 y 117
        Inven* invenWeapon1Right;  // x 60 y 117
        Inven* invenRingLeft;      // x 30 y 31
        Inven* invenRingRight;     // x 30 y 31
        Inven* invenAmulet;        // x 30 y 31
        Inven* invenBelt;          // x 60 y 31
        Inven* invenHelmet;        // x 60 y 60
        Inven* invenShoes;         // x 60 y 61
        Inven* invenGlove;         // x 60 y 61
        Inven* invenArmor;         // x 62 y 89
        Button* closeBtn;

    };
}

