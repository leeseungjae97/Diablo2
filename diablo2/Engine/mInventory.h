#pragma once
#include "..\engine_source\mUI.h"
#include "mInvenItem.h"
namespace m
{
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
    private:
        
    };                                  
                                        // x * 10 y * 4
                                        // x + 18 y - 319
    std::vector<InvenItem*> invenItems; // x 28 y 28
    UI* invenWeapon1Left;   // x 60 y 117
    UI* invenWeapon1Right;  // x 60 y 117
    UI* invenRingLeft;      // x 30 y 31
    UI* invenRingRight;     // x 30 y 31
    UI* invenAmulet;        // x 30 y 31
    UI* invenBelt;          // x 60 y 31
    UI* invenHelmet;        // x 60 y 60
    UI* invenShoes;         // x 60 y 61
    UI* invenGlove;         // x 60 y 61
    UI* invenArmor;         // x 62 y 89


    //inline Inventory* GetInventory()
    //{
    //    static Inventory inventory;
    //    return &inventory;
    //}

    // �κ��丮 40ĭ
    // ���� 2ĭ
    // �� 2ĭ
    // �ƹķ�(�����) 1ĭ
    // ��Ʈ 1ĭ
    // ���� 1ĭ
    // ���� 1ĭ
    // �Ź� 1ĭ
    // �尩 1ĭ

    // �Ҽ����� ����

}

