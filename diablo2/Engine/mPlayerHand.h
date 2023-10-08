#pragma once
#include "mHand.h"
namespace m
{
    class PlayerHand :
        public Hand
    {
    public:
        PlayerHand(GameObject* parent, bool fh);
        virtual ~PlayerHand();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void ChangeWeapon();

    private:
    };
}

