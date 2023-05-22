#include "mGraphicsDevice_DX11.h"
#include "mApplication.h"
extern m::Application application;
namespace m::graphics {
	GraphicsDevice_DX11::GraphicsDevice_DX11() {
		// Device, Context ����

		UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;

		// GPU�� device, context�� �ּ� �Ҵ�
		HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
			, deviceFlag, nullptr, 0
			, D3D11_SDK_VERSION
			, mDevice.GetAddressOf() // ComPtr�� �ּҸ� �������� �Լ� (**)
			, &featureLevel
			, mContext.GetAddressOf()
		);
		//UINT quility = 0;
		//mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &quility);

		// swapChain
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();

		swapChainDesc.Windowed = true;								// ������, ��üȭ�� ���
		swapChainDesc.OutputWindow = application.GetHwnd();	    // Front Buffer �� ��½�ų ������ �ڵ�
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;	// ���� ������ ����� �������� �ʴ´�.

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 144;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;					// �׷��� 
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	// �̹��� ���� ����.

		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		// ����ü�ο� ���� �� ����
		if (!CreateSwapChain(swapChainDesc))
			return;

		//Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTarget;
		if(FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)(mRenderTarget.GetAddressOf()))))
			return;

		mDevice->CreateRenderTargetView((ID3D11Resource*)mRenderTarget.Get(), nullptr, mRenderTargetView.GetAddressOf());

		D3D11_TEXTURE2D_DESC texdesc = {};

		texdesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;

		texdesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		texdesc.CPUAccessFlags = 0;

		texdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		texdesc.Width = application.GetWidth();
		texdesc.Height = application.GetHeight();
		texdesc.ArraySize = 1;

		texdesc.SampleDesc.Count = 1;
		texdesc.SampleDesc.Quality = 0;

		texdesc.MipLevels = 0;
		texdesc.MiscFlags = 0;

		if (!CreateTexture(&texdesc))
			return;
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	}
	GraphicsDevice_DX11::~GraphicsDevice_DX11() {

	}
	bool GraphicsDevice_DX11::CreateSwapChain(DXGI_SWAP_CHAIN_DESC _swapChainDesc) {

		Microsoft::WRL::ComPtr<IDXGIDevice>     pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter>    pAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory>    pFactory = nullptr;
		// ����Ÿ��
		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
			return false;
		
		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf())))
			return false;
		// ��üȭ��
		if (FAILED(pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf())))
			return false;

		if (FAILED(pFactory->CreateSwapChain(mDevice.Get(), &_swapChainDesc, mSwapChain.GetAddressOf())))
			return false;

		return true;
	}
	bool GraphicsDevice_DX11::CreateTexture(const D3D11_TEXTURE2D_DESC* pDesc/*, D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D*/) {



		// �̸� �ؽ��� ����� ũ�⺰�� ��������
		// ������ ������.
		//D3D11_SUBRESOURCE_DATA data;
		if (FAILED(mDevice->CreateTexture2D(&pDesc, nullptr, ppTexture2D)))
			return false;

		if (FAILED(mDevice->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView)))
			return false;

		return true;
	}
	void GraphicsDevice_DX11::Draw() {
		FLOAT bgColor[4] = {0.2f,0.2f, 0.2f, 0.2f};

		mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);

		mSwapChain->Present(0, 0);
	}
}
