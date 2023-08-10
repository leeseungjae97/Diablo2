#pragma once
#include "mSkillScript.h"

namespace m
{
    class FallScript :
        public SkillScript
    {
    public:
        FallScript(eAccessorySkillType type = eAccessorySkillType::END);
        virtual ~FallScript();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        virtual void Initialize() override;

    private:
        eAccessorySkillType mType;
    };
}