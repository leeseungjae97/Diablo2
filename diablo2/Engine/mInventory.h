#pragma once
#include "..\engine_source\mUI.h"
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

        std::vector<Inven*> GetInvens() { return invens; }
        std::vector<InvenItem*> GetInvenItems() { return invenItems; }
        GameObject* GetInvensCollider() { return invensCollider; }
    private:
                                            // x * 10 y * 4
                                            // x + 18 y - 319
        GameObject* invensCollider;
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


    //inline Inventory* GetInventory()
    //{
    //    static Inventory inventory;
    //    return &inventory;
    //}

    // ÀÎº¥Åä¸® 40Ä­
    // ¹«±â 2Ä­
    // ¸µ 2Ä­
    // ¾Æ¹Ä·¿(¸ñ°ÉÀÌ) 1Ä­
    // º§Æ® 1Ä­
    // Åõ±¸ 1Ä­
    // °©¿Ê 1Ä­
    // ½Å¹ß 1Ä­
    // Àå°© 1Ä­

    // ¼Ò¼­¸®½º ¿Àºê

}

