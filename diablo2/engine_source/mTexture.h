#pragma once
#include "mResources.h"
#include "mGraphics.h"

#include "../External/DirectXTex/Include/DirectXTex.h"
#include "../External/DirectXTex/Include/DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\_Library\\Debug_\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\External\\DirectXTex\\_Library\\Release_\\DirectXTex.lib")
#endif

namespace m::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		~Texture();

        HRESULT MergeTex(std::vector<std::shared_ptr<Texture>> mergeTextures, std::vector<Vector2> texturePosition, UINT perWidth, UINT perHeight, UINT oneLength, UINT addtionCount = 0, const std::wstring& mergedTextureName = L"");
		HRESULT CreateTex(UINT avgFileWidth, UINT avgFileHeight, UINT oneAnimLength, const std::wstring& path);
		bool Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag);
		virtual HRESULT Load(const std::wstring& path) override;

		void BindShaderResource(eShaderStage stage, UINT startSlot);
		void BindUnorderedAccessViews(UINT slot);
		void ClearUnorderedAccessViews(UINT slot);

		void Clear();

		static float GetWidRatio() { return fWidRatio; }
		static float GetHeiRatio() { return fHeiRatio; }

		size_t GetMetaDataWidth() { return mImage.GetMetadata().width; }
		size_t GetMetaDataHeight() { return mImage.GetMetadata().height; }

		ScratchImage& GetScratchImage() { return mImage; }

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>    GetRTV() { return  mRTV; }
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>  GetSRV() { return  mSRV; }
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> GetUAV() { return  mUAV; }
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>    GetDSV() { return  mDSV; }
		Microsoft::WRL::ComPtr<ID3D11Texture2D> GetTexture() { return mTexture; }

		void SetRTV(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv) { mRTV = rtv; }
		void SetDSV(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv) { mDSV = dsv; }
		void SetTexture(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture);

		UINT GetMultiTextureSize() { return mMultiTextureSize; }
		std::vector<Microsoft::WRL::ComPtr<ID3D11Texture2D>> GetTextures() { return mTextures; }
		std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> GetSRVs() { return mSRVs; }
		
	private:

	private:
		static float fWidRatio;
		static float fHeiRatio;
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	mSRV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>      mRTV;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>      mDSV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>   mUAV;


		std::vector<ScratchImage> mImages;
		std::vector<Microsoft::WRL::ComPtr<ID3D11Texture2D>> mTextures;
		std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>	mSRVs;
		UINT mMultiTextureSize;

		UINT mSlot;
		UINT mWidth;
		UINT mHeight;

		UINT mPerWidth;
		UINT mPerHeight;
		D3D11_TEXTURE2D_DESC mDesc;
	};
}

