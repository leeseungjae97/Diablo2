#pragma once
#include "..\engine_source\mGameObject.h"
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

        Vector3 GetPrevPosition() { return prevPosition; }
        Vector3 GetDestPosition() { return destPosition; }

        bool Stop() { return fRemainDistance < fStartDistance ? false : true; }

    private:
        Collider2D* rangeCollider;
        Vector3 prevPosition;
        Vector3 destPosition;
        Vector3 vDirection;
        Vector3 vS;

        float fRemainDistance;
        float fStartDistance;
        float fSpeed;
    };
}

