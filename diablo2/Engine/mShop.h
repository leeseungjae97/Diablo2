#pragma once
#include "mUI.h"
#include "../engine_source/NPCLookUpTables.h"

namespace m
{
    class Button;
    class Shop :
        public UI
    {
    public:
        Shop(Camera* camera);
        virtual ~Shop();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void ItemInit(eNPCType type);
    private:
        std::vector<Button*> shopTabs;
        Button* mButtonBuy;
        Button* mButtonSell;
    };
}


