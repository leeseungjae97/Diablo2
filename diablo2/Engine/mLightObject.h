#pragma once
#include "mGameObject.h"
namespace m
{
    class LightObject :
        public GameObject
    {
    public:
        LightObject();
        virtual ~LightObject();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Initialize() override;
        virtual void Render() override;

        void SetFollowerObject(GameObject* follower) { mFollower = follower; }
    private:
        GameObject* mFollower;
    };
}


