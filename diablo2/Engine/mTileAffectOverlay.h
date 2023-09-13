#pragma once
#include "mGameObject.h"

#include "../engine_source/AffectOverlayLookUpTable.h"

namespace m
{
    class AffectOverlayScript;

    class TileAffectOverlay :
        public GameObject
    {
    public:
        TileAffectOverlay(Vector3 initPos, eAffectOverlayType type, eLayerType mOwnerType);
        virtual ~TileAffectOverlay();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        void ActiveOverlay();
    private:
        void addZWeight();
    private:
        AffectOverlayScript* mAOS;
    };
}

