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
        void skillChangeShortCut();
        void setMaCamera();
        void makeMa();
        void specifyShortcut();
        void eraseSkillOverlap(int index);
        void makeIndividualSkillImages();
        void updateIndividualSkillImages(bool right);
        void applySkillOutputState();
        void setIndividualSkillCamera();

    private:
        eSkillType mSkillType;
        int mSkillIndex;
        
        UI* skillImages;
        std::vector<UI*> individualSkillImages;


        UI* mF5;
        UI* mF4;
        UI* mF3;
        UI* mF2;
        UI* mF1;

        std::vector<Vector2> skillMatPos;
        std::vector<std::shared_ptr<Texture>> skillTexs;
        std::vector<eSkillType> skillTypes;

        std::vector<eSkillType> saveShortCutSkillTypes;
        std::vector<UI*> macroButtons;
        std::vector<bool> bOverlaps;
        int prevSkillPoint;
        bool mbSkillOutputOpen;
        bool mbUseIndividualSkillOutput;
    };
}


