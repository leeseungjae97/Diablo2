#pragma once
#include "..\engine_source\mGameObject.h"
#include "..\engine_source\mCamera.h"
namespace m
{
    class Player :
        public GameObject
    {
    public:
        Player(Vector3 iniPos);
        virtual ~Player();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();
    private:
        Vector3 prevPosition;
        Vector3 destPosition;
        Vector3 vDirection;
        Vector3 vS;
        float fRemainDistance;
        float fStartDistance;
        float fSpeed;
    };
}

