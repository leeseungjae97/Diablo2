#pragma once
#include "mButton.h"

#include "../engine_source/mDrawMaterials.h"
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

        void SetSkillBtnPos();
        int GetSkillIndex() { return mSkillIndex; }
    private:
        eSkillType mSkillType;
        int mSkillIndex;

        std::vector<std::shared_ptr<Texture>> skillTexs;
        std::vector<Vector2> skillMatPos;
    };
}

