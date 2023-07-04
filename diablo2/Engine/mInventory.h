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
    std::vector<InvenItem*> invenItems;
    //inline Inventory* GetInventory()
    //{
    //    static Inventory inventory;
    //    return &inventory;
    //}
}

