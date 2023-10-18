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

        void AuraActive();
        void SetAura(eAuraType type, eLayerType layerType = eLayerType::End, float duration = -1);
        void FrontAura() { bFront = true; }
    private:
        bool bFront;
        AuraScript* mAS;
        Collider2D* mCol;
        GameObject* mOwner;
        Vector2 vCenterPosOffset;
    };
}


