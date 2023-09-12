#pragma once
#include "mMoveAbleObject.h"

#include "../engine_source/AffectOverlayLookUpTable.h"

namespace m
{
    class AffectOverlayScript;

    class TileAffectOverlay :
        public MoveAbleObject
    {
    public:
        TileAffectOverlay(Vector3 initPos, eAffectOverlayType type, eLayerType mOwnerType);
        virtual ~TileAffectOverlay();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        virtual void Hit(int damage);
    private:
        AffectOverlayScript* mAOS;
    };
}

