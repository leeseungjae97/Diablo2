#pragma once
#include "../engine_source/mScript.h"
namespace m
{
    class MoveAbleObject;

    class TeleportScript :
        public Script
    {
    public:
        TeleportScript();
        virtual ~TeleportScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetTeleportOwner(GameObject* owner) { mOwner = owner; }

    private:
        void checkWallIfWallGetNearByCoord();

    private:
        GameObject* mOwner;
    };
}

