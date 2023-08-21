#pragma once
#include "mHand.h"

namespace m
{
    class MonsterHand :
        public Hand
    {
    public:
        MonsterHand(Monster* parent, eMonsterType type, bool fh);
        virtual ~MonsterHand();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        virtual void Initialize() override;
        void SetDirection(int direction);
        void SetAniType(int aniType);
    private:
        eMonsterType mMonsterType;
        Monster* mOwner;
    };
}
