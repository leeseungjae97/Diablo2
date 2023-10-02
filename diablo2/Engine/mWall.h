#pragma once
#include "mGameObject.h"
namespace m
{
    class Wall :
        public GameObject
    {
    public:
        Wall(Camera* camera, Vector2 coord);
        virtual ~Wall();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
    private:
        Vector2 mCoord;
    };
}

