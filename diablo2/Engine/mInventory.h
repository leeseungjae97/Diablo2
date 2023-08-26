#pragma once
#include "../engine_source/mUI.h"
#include "mInvenItem.h"
#include "mEmptyRect.h"
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

        std::vector<EmptyRect*>& GetInvens() { return invens; }
        std::vector<EmptyRect*>& GetEquiments() { return equiments; }
        std::vector<InvenItem*>& GetInvenItems() { return invenItems; }
        EmptyRect* GetInvensCollider() { return invensCollider; }

    private:
        EmptyRect* invensCollider;
        std::vector<EmptyRect*> invens;
        std::vector<EmptyRect*> equiments;
        std::vector<InvenItem*> invenItems; // x 28 y 28
        EmptyRect* invenWeapon1Left;   // x 60 y 117
        EmptyRect* invenWeapon1Right;  // x 60 y 117
        EmptyRect* invenRingLeft;      // x 30 y 31
        EmptyRect* invenRingRight;     // x 30 y 31
        EmptyRect* invenAmulet;        // x 30 y 31
        EmptyRect* invenBelt;          // x 60 y 31
        EmptyRect* invenHelmet;        // x 60 y 60
        EmptyRect* invenShoes;         // x 60 y 61
        EmptyRect* invenGlove;         // x 60 y 61
        EmptyRect* invenArmor;         // x 62 y 89
        Button* closeBtn;

    };
}

