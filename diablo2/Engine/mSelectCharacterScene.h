#pragma once
#include "../engine_source/mScene.h"
namespace m
{
    class Button;
    class TextInputUI;
    class UI;
    class Camera;
    class SelectCharacterScene :
        public Scene
    {
    public:
        SelectCharacterScene();
        ~SelectCharacterScene();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
        void makeUI();
    private:
        UI* mTextClass;
        UI* mTextClassEx;
        Button* mGameStart;
        TextInputUI* mTIU;
    };
}
