#pragma once
#include "../engine_source/mUI.h"
namespace m
{
    class EmptyRect;
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
        //std::vector<EmptyRect*> pockets;
        //std::vector<EmptyRect*> exPockets;
        //EmptyRect* mPocketUI;
        UI* mExPocketUI;
        UI* mLifeDisplay;
        UI* mManaDisplay;
        bool bBelt;
    };
}

