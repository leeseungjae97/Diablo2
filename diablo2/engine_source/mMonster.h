#pragma once
#include "mGameObject.h"
namespace m
{
    class Monster :
        public GameObject
    {
    public:
        Monster(Vector3 iniPos);
        virtual ~Monster();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();
    private:

    };
}

