#pragma once
#include "mSkillOverlay.h"
namespace m
{
    class SkillBuff :
        public SkillOverlay
    {
    public:
        SkillBuff(GameObject* mOwner, int index, eSkillType type);
        virtual ~SkillBuff();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void ActiveOverlay() override;
    private:
    };
}

