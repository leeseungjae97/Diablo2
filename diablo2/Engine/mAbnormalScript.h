#pragma once
#include "mScript.h"
namespace m
{
    class AbnormalScript :
        public Script
    {
    public:
        AbnormalScript();
        virtual ~AbnormalScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetAbnormalCollider(Collider2D* col) { mAbnormalCollider = col; }
    private:
        void abnormalAttack();

    private:
        Collider2D* mAbnormalCollider;
    };
}

