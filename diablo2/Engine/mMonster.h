#pragma once
#include "..\engine_source\mGameObject.h"

#include "mMoveAbleObject.h"
namespace m
{
    class Monster :
        public MoveAbleObject
    {
    public:
        Monster(Vector3 iniPos, float speed);
        virtual ~Monster();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        void SetHpCapacity(int cap) { hp = hpCapacity = cap; }
        void Hit(int damage);
        Collider2D* GetSightCollider() { return sightCollider; }
    private:
        Collider2D* sightCollider;


        float hp;
        float hpCapacity;
        float hpPercent;
    };
}

