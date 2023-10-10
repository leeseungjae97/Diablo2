#pragma once
#include "mUI.h"
namespace m
{
    class Button;

    class CharacterStatus :
        public UI
    {
    public:
        CharacterStatus(Camera* camera);
        virtual ~CharacterStatus();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
        UI* mTextName;
        UI* mTextClass;
        UI* mLevel;
        UI* mExp;
        UI* mNextLevelExp;

        UI* mStr;
        UI* mDex;
        UI* mVit;
        UI* mEng;

        UI* mTextStr;
        UI* mTextDex;
        UI* mTextVit;
        UI* mTextEng;
        UI* mTextRemainPoint;

        UI* mRemainPoint;

        UI* mLife;
        UI* mMana;

        Button* mClose;

        Button* mStrBtn;
        Button* mDexBtn;
        Button* mVitBtn;
        Button* mEngBtn;
    };
}

