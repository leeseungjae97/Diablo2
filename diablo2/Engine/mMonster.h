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

        void SetHpCapacity(int cap) { hp = hpCapacity = cap; }
        void Hit(int damage);
        bool Stop() { return fRemainDistance < fStartDistance ? false : true; }
        bool GetHit() { return bGetHit; }
        void SetHit(bool hit) { bGetHit = hit; }
        Collider2D* GetRangeCollider() { return rangeCollider; }
    private:
        Collider2D* rangeCollider;
        Collider2D* sightCollider;
        Vector3 prevPosition;
        Vector3 destPosition;
        Vector3 vDirection;
        Vector3 vS;

        bool bGetHit;

        float hp;
        float hpCapacity;
        float hpPercent;

        float fRemainDistance;
        float fStartDistance;
        float fSpeed;
    };
}

