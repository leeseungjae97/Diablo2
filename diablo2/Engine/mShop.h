#pragma once
#include "mUI.h"
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
    private:
        std::vector<Button*> shopTabs;
        Button* mButtonBuy;
        Button* mButtonSell;
    };
}


