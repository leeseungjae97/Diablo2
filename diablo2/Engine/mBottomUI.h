#pragma once
#include "../engine_source/mUI.h"
namespace m
{
    class Inven;
    class BottomUI :
        public UI
    {
    public:
        BottomUI(Camera* camera);
        virtual ~BottomUI();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
        std::vector<Inven*> pockets;
        std::vector<Inven*> exPockets;
        Inven* mPocketUI;
        UI* mExPocketUI;
        bool bBelt;
    };
}

