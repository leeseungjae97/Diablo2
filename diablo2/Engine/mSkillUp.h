#pragma once
#include "..\engine_source\mUI.h"
namespace m
{
    class SkillUp :
        public UI
    {
    public:
        SkillUp();
        virtual ~SkillUp();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
    private:

    };
}

