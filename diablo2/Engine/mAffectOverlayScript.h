#pragma once
#include "mSkillScript.h"

#include "AffectOverlayLookUpTable.h"
namespace m
{
    class AffectOverlayScript :
        public SkillScript
    {
    public:
        AffectOverlayScript(eAffectOverlayType type);
        virtual ~AffectOverlayScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* other) override;
        //virtual void OnCollisionExit(Collider2D* other) override;
        //virtual void OnCollisionStay(Collider2D* other) override;

        void SetLoopCount(int count) { iMaxLoopCount = count; }

    private:
        Collider2D* mCol;
        int iCurLoopCount;
        int iMaxLoopCount;
        bool bCauseDamage;
        float fDamageInterval;
        eAffectOverlayType mOverlayType;
    };
}

