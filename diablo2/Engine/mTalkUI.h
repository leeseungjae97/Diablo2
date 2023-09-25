#pragma once
#include "mUI.h"
#include "NPCLookUpTables.h"

namespace m
{
    class TalkUI :
        public UI
    {
    public:
        TalkUI(Vector3 initPos, eNPCType type);
        virtual ~TalkUI();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
        void makePositionToUICamera();
    private:
        std::wstring* mMenus;
    };
}

