#pragma once
#include "mButton.h"

#include "../engine_source/SkillLookUpTables.h"

namespace m
{
    class SkillShortCutButton :
        public Button
    {
    public:
        SkillShortCutButton(int skillIndex);
        virtual ~SkillShortCutButton();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        
        int GetSkillIndex() { return mSkillIndex; }
    private:
        eSkillType mSkillType;
        int mSkillIndex;
    };
}

