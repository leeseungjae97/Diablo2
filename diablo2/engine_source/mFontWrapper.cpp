#include "mFontWrapper.h"
#include "mGraphicDevice_DX11.h"
#include "mRenderer.h"

namespace m
{
	IFW1Factory* FontWrapper::mFW1Factory = nullptr;
	IFW1FontWrapper* FontWrapper::mFontWrapper = nullptr;

	bool FontWrapper::Initialize()
	{
		if (FAILED(FW1CreateFactory(FW1_VERSION, &mFW1Factory)))
			return false;

		ID3D11Device* pDevice = graphics::GetDevice()->GetID3D11Device();
		HRESULT hr = S_OK;
		hr = (mFW1Factory->CreateFontWrapper(pDevice, L"HYGothic", &mFontWrapper));
		//if(FAILED(hr)) hr = (mFW1Factory->CreateFontWrapper(pDevice, L"Arial", &mFontWrapper));


		return true;
	}

	void FontWrapper::DrawFont(const wchar_t* str, float x, float y, float size, UINT rgb)
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
			= renderer::depthStencilStates[(UINT)eDSType::None];
		GetDevice()->BindDepthStencilState(nullptr);
		//RGB();
		ID3D11DeviceContext* pContext = graphics::GetDevice()->GetID3D11DeviceContext();
		mFontWrapper->DrawString(
			pContext,
			str, // String
			size,// Font size
			x,// X position
			y,// Y position
			rgb,// Text color, 0xAaBbGgRr
			FW1_RESTORESTATE
		);
		dsState = renderer::depthStencilStates[(UINT)eDSType::LessEqua];
		GetDevice()->BindDepthStencilState(dsState.Get());
	}

    Vector2 FontWrapper::GetTextSize(const wchar_t* str, float size)
    {
		FW1_RECTF measuredSize(0, 0, 0, 0);

		FW1_RECTF mSize = mFontWrapper->MeasureString(str, L"HYGothic", size, &measuredSize, FW1_NOWORDWRAP);
		FLOAT width = mSize.Right - mSize.Left;
		FLOAT height = mSize.Bottom - mSize.Top;
		height += 5.f;
		width += 5.f;
		return Vector2(width, height);
    }

    void FontWrapper::Release()
	{
		mFW1Factory->Release();
		mFW1Factory = nullptr;

		mFontWrapper->Release();
		mFontWrapper = nullptr;
	}
}
