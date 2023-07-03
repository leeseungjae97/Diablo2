#pragma once
#include "mResources.h"
#include "mGraphics.h"

#include "../External/DirectXTex/Include/DirectXTex.h"
#include "../External/DirectXTex/Include/DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\Library\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\External\\DirectXTex\\Library\\Release\\DirectXTex.lib")
#endif

namespace m::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		~Texture();

		virtual HRESULT Load(const std::wstring& path) override;
		void BindShader(eShaderStage stage, UINT startSlot);
		void Clear();

		static float GetWidRatio() { return fWidRatio; }
		static float GetHeiRatio() { return fHeiRatio; }

	private:
		static float fWidRatio;
		static float fHeiRatio;
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	mSRV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>      mRTV;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>      mDSV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>   mUAV;
		D3D11_TEXTURE2D_DESC mDesc;
	};
}

