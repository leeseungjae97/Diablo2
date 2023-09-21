#pragma once
#include "../engine_source/mScript.h"
namespace m
{
    class OverlayScript :
        public Script
    {
    public:
        OverlayScript();
        virtual ~OverlayScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void MakeOverlayAnimation(const std::wstring& overlayName, Vector2 size, Vector2 offset,
            Vector2 centerPos, int length, float duration, bool loop);
        void SetDirection(int direction) { mDirection = direction; }
        void SetSyncPlay(Animator* animator);

    private:
        std::wstring wsOLname;
        Animator* mAnimator;
        int mDirection;
        bool mLoop;
    };
}

