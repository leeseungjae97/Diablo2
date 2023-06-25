#pragma once
#include "mResources.h"
#include "mGraphics.h"

#include "../External/DirectXTex/Include/DirectXTex.h"
#include "../External/DirectXTex/Include/DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Release\\DirectXTex.lib")
#endif

namespace m::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		~Texture();

		bool Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag);
		virtual HRESULT Load(const std::wstring& path) override;
		void BindShader(eShaderStage stage, UINT startSlot);
		void Clear();

	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	mSRV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>      mRTV;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>      mDSV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>   mUAV;
		D3D11_TEXTURE2D_DESC mDesc;
	};
}

