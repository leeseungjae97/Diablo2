#pragma once
#include "mGameObject.h"
namespace m
{
    class UI;

    class Portal :
        public GameObject
    {
    public:
        Portal();
        virtual ~Portal();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        void ActivePortal();
        void ResetPortal();
        void SetClickPortal(const std::function<void()>& click) { fClickPortal = click; }
    private:
        UI* mHoverUI;
        std::function<void()> fClickPortal;
    };
}


