#include "mTextInputUI.h"

#include "mFontWrapper.h"
#include "../engine_source/mMeshRenderer.h"
namespace m
{
    TextInputUI::TextInputUI()
        : mInputText(L"")
    {
        SET_MESH(this, L"RectMesh");
        SET_MATERIAL(this, L"characterNameInput");
        MAKE_GET_TEX(this, tex);
        SET_SCALE_TEX_SIZE_WITH_RAT(this, tex, 1.f);
    }

    TextInputUI::~TextInputUI()
    {
    }

    void TextInputUI::Initialize()
    {
        UI::Initialize();
    }

    void TextInputUI::Update()
    {
        UI::Update();

        textInput();
    }

    void TextInputUI::LateUpdate()
    {
        UI::LateUpdate();
    }

    void TextInputUI::Render()
    {
        UI::Render();
    }

    int TextInputUI::GetTextLen()
    {
        return mInputText.size();
    }
    void TextInputUI::textInput()
    {
        int iInput = Input::GetInputKey();

        if (iInput == -1) return;

        if(iInput == VK_BACK)
        {
            mInputText = mInputText.substr(0, mInputText.size() - 1);
        }else{
            wchar_t wideChar = static_cast<wchar_t>(iInput);
            std::wstring wideStr(1, wideChar);

            mInputText += wideStr;
        }
        
        SetText(mInputText);
        Vector2 size = FontWrapper::GetTextSize(mInputText.c_str(), 15.f);
        Vector3 scale = GET_SCALE(this);
        SetTextOffset(Vector2(((- scale.x / 2.f) + size.x / 2.f) + 5.f, 5.f));
        SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
        SetTextSize(15.f);
    }
}
