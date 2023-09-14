#pragma once
#include "../engine_source/mGameObject.h"
#include "../engine_source/mMonsterManager.h"


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
        void Hit(int damage, bool attackStun =true);
        Collider2D* GetSightCollider() { return sightCollider; }

        int GetMonsterId() { return monsterId; }
        void SetMonsterId(int id) { monsterId = id; }

        void SetMonsterClass(eMonsterClass _class) { mMonsterClass = _class; }
        eMonsterClass GetMonsterClass() { return mMonsterClass; }

        bool Arrival() { return bPathChange == false ? true : false; }

        void SetNextMoveCoord(Vector2 coord) { mNextMoveCoord = coord; }
        Vector2 GetNextMoveCoord() { return mNextMoveCoord; }

        Vector2 GetPrevCurCoord() { return prevCurCoord; }
        Vector2 GetTargetCoord() { return prevTargetCoord; }

        void PathChange(bool pc) { bPathChange = pc; }
        bool GetPathChange() { return bPathChange; }

        void Addiction() { bAddiction = true; }

    private:
        Collider2D* sightCollider;
        eMonsterClass mMonsterClass;

    	Vector2 mNextMoveCoord;

        Vector2 prevCurCoord;
        Vector2 prevTargetCoord;

        bool bPathChange;
        bool bAddiction;

        int monsterId;
        float hp;
        float hpCapacity;
        float hpPercent;
    };
}

