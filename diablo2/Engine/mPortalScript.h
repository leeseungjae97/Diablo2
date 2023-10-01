#pragma once
#include "mScript.h"
namespace m
{
    class PortalScript :
        public Script
    {
    public:
        PortalScript();
        virtual ~PortalScript();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Initialize() override;
        virtual void Render() override;

        void Portal() { bPortal = true; }
        void ResetPortal()
        {
            bStartAnim = true;
            bPortal = false;
        }
    private:
        Animator* mAnimator;
        bool bStartAnim;

        bool bPortal;
    };

}

