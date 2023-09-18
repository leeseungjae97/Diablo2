#pragma once
#include "mUVUI.h"
namespace m
{
    class EnemyHpUI :
        public UVUI
    {
    public:
        EnemyHpUI(Vector3 initPos);
        virtual ~EnemyHpUI();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetFontSize(float size) { fFontSize = size; }
    private:
        void getHoveredMonsterInformation();
        void makeEnemyHpUI();
    private:
        Monster* mHoverMonster;
        float fFontSize;
    };
}

