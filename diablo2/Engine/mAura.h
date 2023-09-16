#pragma once
#include "mSkill.h"
namespace m
{
    class AuraScript;
    class Aura
        : public GameObject
    {
    public:
        Aura(GameObject* owner, eAuraType type, Vector2 centerOffset);
        virtual ~Aura();

        void bottomAuraPosition();
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Initialize() override;
        virtual void Render() override;
    private:
        AuraScript* mAS;
        GameObject* mOwner;
        Vector2 vCenterPosOffset;
    };
}


