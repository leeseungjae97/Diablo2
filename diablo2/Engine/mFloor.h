#pragma once
#include "../engine_source/mGameObject.h"
#include "../engine_source/FloorLookUpTables.h"
namespace m
{
    class Floor :
        public GameObject
    {
    public:
        Floor(Vector3 initPos);
        virtual ~Floor();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        void SetFloor();
    private:
        float fAcc;
        int iMatIndex;
    };
}

