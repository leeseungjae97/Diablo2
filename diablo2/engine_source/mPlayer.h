#pragma once
#include "mGameObject.h"
namespace m
{
    class Player :
        public GameObject
    {
    public:
        Player();
        virtual ~Player();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

    private:
    };
}

