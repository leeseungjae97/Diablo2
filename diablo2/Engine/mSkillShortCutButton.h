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

        void MakeSkillShortCutImage();
        void SetSkillBtnPos(bool right);

        eSkillType GetHoverClickSkill();
        int GetSkillIndex() { return mSkillIndex; }

    private:
        void makeMa();

    private:
        eSkillType mSkillType;
        int mSkillIndex;
        
        UI* skillImages;

        UI* mF5;
        UI* mF4;
        UI* mF3;
        UI* mF2;
        UI* mF1;

        std::vector<Vector2> skillMatPos;
        std::vector<std::shared_ptr<Texture>> skillTexs;
        std::vector<eSkillType> skillTypes;

        int prevSkillPoint;
    };
}

