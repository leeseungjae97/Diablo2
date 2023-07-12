#pragma once
#include "..\engine_source\mUI.h"
#include "..\engine_source\SkillLookUpTables.h"

namespace m
{
    class SkillButton;
    class Button;
    class SkillUp :
        public UI
    {
    public:
        SkillUp(Camera* camera);
        virtual ~SkillUp();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void GetSkillTree(int(* _skillTree)[10]);

        std::shared_ptr<Material> GetSkillP1() { return skillP1; }
        std::shared_ptr<Material> GetSkillP2() { return skillP2; }
        std::shared_ptr<Material> GetSkillP3() { return skillP3; }

    private:
        std::shared_ptr<Material> skillP1;
        std::shared_ptr<Material> skillP2;
        std::shared_ptr<Material> skillP3;
        Button* coldBtn;
        Button* fireBtn;
        Button* lightBtn;
        std::vector<Button*> buttons;

        UI* remainPointer;
        int iRemainPointer;

        std::vector<SkillButton*> coldSkills;
        std::vector<SkillButton*> fireSkills;
        std::vector<SkillButton*> lightSkills;
        std::vector<SkillButton*> skills;
        
        std::vector<UI*> nums;

        int skillSetNum;
        int skillTree[10][10];
    };
}

