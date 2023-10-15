#pragma once
#include "mUI.h"
namespace m
{
    class TextInputUI :
        public UI
    {
    public:
        TextInputUI();
        virtual ~TextInputUI();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        int GetTextLen();
        void textInput();
    private:
        std::wstring mInputText;
    };
}

