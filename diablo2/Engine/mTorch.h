#pragma once
#include "../engine_source/mGameObject.h"
#include "../engine_source/TorchLookUpTables.h"

namespace m
{
    class ShadowObject;

    class Torch :
        public GameObject
    {
    public:
        Torch(Vector3 initPos, Vector2 coord, Camera* camera, eTorchType type);
        virtual ~Torch();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
    private:
        ShadowObject* mShadow;
        Vector2 mCoord;
    };
}

