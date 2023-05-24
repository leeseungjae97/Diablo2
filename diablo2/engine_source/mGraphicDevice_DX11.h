#pragma once
#include "_Engine.h"
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace m::graphics
{
	class GraphicDevice_DX11
	{
	public:
		GraphicDevice_DX11();
		~GraphicDevice_DX11();

		bool CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd);
		bool CreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data);
		bool CreateShader();

		bool CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data);
		void Draw();

	private:
		Microsoft::WRL::ComPtr<ID3D11Device>			mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>		mContext;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			mRenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	mRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			mDepthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	mDepthStencilView;
		Microsoft::WRL::ComPtr<IDXGISwapChain>			mSwapChain;
	};

	inline GraphicDevice_DX11*& GetDevice()
	{
		static GraphicDevice_DX11* device = nullptr;
		return device;
	}
}
