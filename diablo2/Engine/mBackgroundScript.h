#pragma once
#include "mScript.h"
namespace m
{
    class BackgroundScript :
        public Script
    {
    public:
        BackgroundScript();
        virtual ~BackgroundScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        void SetAnimString(const std::wstring& str);

    private:
        Animator* mAnimator;
        std::wstring mAnimString;
    };
}

