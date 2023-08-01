#include "mGraphicDevice_DX11.h"
#include "mApplication.h"
#include "mRenderer.h"
#include "mMesh.h"

extern m::Application application;

namespace m::graphics
{
	GraphicDevice_DX11::GraphicDevice_DX11()
	{
		// Device, Context 생성
		HWND hWnd = application.GetHwnd();
		UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;

		// GPU에 device, context의 주소 할당
		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
			, deviceFlag, nullptr, 0
			, D3D11_SDK_VERSION
			, mDevice.GetAddressOf(), &featureLevel
			, mContext.GetAddressOf()); // ComPtr의 주소를 가져오는 함수 (**)

		// swapChain
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = application.GetMetaDataWidth();
		swapChainDesc.BufferDesc.Height = application.GetMetaDataHeight();

		// 스왑체인에 대한 값 설정

		if (!CreateSwapChain(&swapChainDesc, hWnd))
			return;

		mRenderTarget = std::make_shared<Texture>();
		mDepthStencil = std::make_shared<Texture>();

		Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTarget;
		if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D)
			, (void**)(renderTarget.GetAddressOf()))))
			return;
		mRenderTarget->SetTexture(renderTarget);

		//mDevice->CreateRenderTargetView((ID3D11Resource*)mRenderTarget.Get(), nullptr, mRenderTargetView.GetAddressOf());

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
		mDevice->CreateRenderTargetView((ID3D11Resource*)mRenderTarget->GetTexture().Get()
										, nullptr, renderTargetView.GetAddressOf());
		mRenderTarget->SetRTV(renderTargetView);


		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.CPUAccessFlags = 0;

		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.Width = application.GetMetaDataWidth();
		depthStencilDesc.Height = application.GetMetaDataHeight();
		depthStencilDesc.ArraySize = 1;

		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;

		depthStencilDesc.MipLevels = 0;
		depthStencilDesc.MiscFlags = 0;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer = nullptr;
		if (!CreateTexture2D(&depthStencilDesc, nullptr, depthStencilBuffer.GetAddressOf()))
			return;
		mDepthStencil->SetTexture(depthStencilBuffer);

		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView = nullptr;
		if (!CreateDepthStencilView(depthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf()))
			return;
		mDepthStencil->SetDSV(mDepthStencilView);

		/*D3D11_SUBRESOURCE_DATA data;
		if (!CreateTexture2D(&depthStencilDesc, &data))
			return;*/

		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		mViewPort = 
		{
			0.0f, 0.0f
			,(float)(winRect.right - winRect.left)
			,(float)(winRect.bottom- winRect.top)
			,0.0f, 1.0f
		};
		BindViewPort(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTarget->GetRTV().GetAddressOf(), mDepthStencil->GetDSV().Get());
	}
	GraphicDevice_DX11::~GraphicDevice_DX11()
	{

	}
	bool GraphicDevice_DX11::CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd)
	{

		DXGI_SWAP_CHAIN_DESC dxgiDesc = {};

		dxgiDesc.OutputWindow = hWnd;										// Front Buffer 를 출력시킬 윈도우 핸들
		dxgiDesc.Windowed = true;											// 윈도우, 전체화면 모드
		dxgiDesc.BufferCount = desc->BufferCount;
		dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;

		dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		dxgiDesc.BufferDesc.Width = desc->BufferDesc.Width;
		dxgiDesc.BufferDesc.Height = desc->BufferDesc.Height;
		dxgiDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		dxgiDesc.BufferDesc.RefreshRate.Numerator = 144;
		dxgiDesc.BufferDesc.RefreshRate.Denominator = 1;
		dxgiDesc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;							// 그래픽 
		dxgiDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	// 이미지 생성 방향.

		dxgiDesc.SampleDesc.Count = 1;
		dxgiDesc.SampleDesc.Quality = 0;

		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pFactory = nullptr;

		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
			return false;

		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf())))
			return false;

		if (FAILED(pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf())))
			return false;

		if (FAILED(pFactory->CreateSwapChain(mDevice.Get(), &dxgiDesc, mSwapChain.GetAddressOf())))
			return false;

		return true;
	}
	bool GraphicDevice_DX11::CreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data)
	{
		if (FAILED(mDevice->CreateBuffer(desc, data, buffer)))
			return false;

		return true;
	}
	bool GraphicDevice_DX11::CreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ComputeShader** ppComputeShader)
	{
		if (FAILED(mDevice->CreateComputeShader(pShaderBytecode, BytecodeLength, nullptr, ppComputeShader)))
			return false;

		return true;
	}
	bool GraphicDevice_DX11::CompileFromfile(const std::wstring& fileName, const std::string& funcName, const std::string& version, ID3DBlob** ppCode)
	{
		ID3DBlob* errorBlob = nullptr;
		D3DCompileFromFile(fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, funcName.c_str(), version.c_str(), 0, 0, ppCode, &errorBlob);

		if (errorBlob)
		{
			OutputDebugStringA((char*)(errorBlob->GetBufferPointer()));
			errorBlob->Release();
			errorBlob = nullptr;
		}

		return false;
	}
	bool GraphicDevice_DX11::CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11VertexShader** ppVertexShader)
	{
		if (FAILED(mDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, nullptr, ppVertexShader)))
			return false;

		return true;
	}
	bool GraphicDevice_DX11::CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11PixelShader** ppPixelShader)
	{
		if (FAILED(mDevice->CreatePixelShader(pShaderBytecode, BytecodeLength, nullptr, ppPixelShader)))
			return false;

		return true;
	}
	bool GraphicDevice_DX11::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
	{
		if (FAILED(mDevice->CreateSamplerState(pSamplerDesc, ppSamplerState)))
			return false;

		return true;
	}
	bool GraphicDevice_DX11::CreateRasterizeState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState)
	{
		if (FAILED(mDevice->CreateRasterizerState(pRasterizerDesc, ppRasterizerState)))
			return false;

		return true;
	}
	bool GraphicDevice_DX11::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState)
	{
		if (FAILED(mDevice->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState)))
			return false;

		return true;
	}
	bool GraphicDevice_DX11::CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState)
	{
		if (FAILED(mDevice->CreateBlendState(pBlendStateDesc, ppBlendState)))
			return false;

		return true;
	}
	bool GraphicDevice_DX11::CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView)
	{
		if (FAILED(mDevice->CreateShaderResourceView(pResource, pDesc, ppSRView)))
			return false;

		return true;
	}
	bool GraphicDevice_DX11::CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView)
	{
		if (FAILED(mDevice->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView)))
			return false;

		return true;
	}
	bool GraphicDevice_DX11::CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView)
	{
		if (FAILED(mDevice->CreateRenderTargetView(pResource, pDesc, ppRTView)))
			return false;

		return true;
	}
	bool GraphicDevice_DX11::CreateUnordedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView)
	{
		if (FAILED(mDevice->CreateUnorderedAccessView(pResource, pDesc, ppUAView)))
			return false;

		return true;
	}

	void GraphicDevice_DX11::BindInputLayout(ID3D11InputLayout* pInputLayout)
	{
		mContext->IASetInputLayout(pInputLayout);
	}
	void GraphicDevice_DX11::BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
	{
		mContext->IASetPrimitiveTopology(Topology);
	}
	bool GraphicDevice_DX11::CreateTexture2D(const D3D11_TEXTURE2D_DESC* desc, void* data, ID3D11Texture2D** ppTexture2D)
	{
		if (FAILED(mDevice->CreateTexture2D(desc, nullptr, ppTexture2D)))
			return false;

		return true;
	}
	//bool GraphicDevice_DX11::CreateTexture2D(const D3D11_TEXTURE2D_DESC* desc, D3D11_SUBRESOURCE_DATA* pInitialData)
	//{
	//	D3D11_TEXTURE2D_DESC dxgiDesc = {};
	//	dxgiDesc.BindFlags = desc->BindFlags;
	//	dxgiDesc.Usage = desc->Usage;
	//	dxgiDesc.CPUAccessFlags = 0;

	//	dxgiDesc.Format = desc->Format;
	//	dxgiDesc.Width = desc->Width;
	//	dxgiDesc.Height = desc->Height;
	//	dxgiDesc.ArraySize = desc->ArraySize;

	//	dxgiDesc.SampleDesc.Count = desc->SampleDesc.Count;
	//	dxgiDesc.SampleDesc.Quality = 0;

	//	dxgiDesc.MipLevels = desc->MipLevels; // 미리 텍스쳐 사이즈를 크기별로 만들어놓은 경우 레벨 사이즈를 정함.
	//	dxgiDesc.MiscFlags = desc->MiscFlags;

	//	//D3D11_SUBRESOURCE_DATA data; // 데이터 넘겨줄때 form
	//	if (FAILED(mDevice->CreateTexture2D(&dxgiDesc, nullptr, mDepthStencilBuffer.ReleaseAndGetAddressOf())))
	//		return false;

	//	if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf())))
	//		return false;

	//	return true;
	//}
	bool GraphicDevice_DX11::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, ID3DBlob* byteCode, ID3D11InputLayout** ppInputLayout)
	{
		if (FAILED(mDevice->CreateInputLayout(pInputElementDescs, NumElements
			, byteCode->GetBufferPointer()
			, byteCode->GetBufferSize()
			, ppInputLayout)))
			return false;

		return true;
	}
	void GraphicDevice_DX11::BindViewPort(D3D11_VIEWPORT* viewPort)
	{
		mContext->RSSetViewports(1, viewPort);
	}
	void GraphicDevice_DX11::BindRasterizeState(ID3D11RasterizerState* pRasterizerState)
	{
		mContext->RSSetState(pRasterizerState);
	}
	void GraphicDevice_DX11::BindDepthStencilState(ID3D11DepthStencilState * pDepthStencilState)
	{
		mContext->OMSetDepthStencilState(pDepthStencilState, 0);
	}
	void GraphicDevice_DX11::BindBlendState(ID3D11BlendState * pBlendState)
	{
		mContext->OMSetBlendState(pBlendState, nullptr, 0xffffffff);
	}
	void GraphicDevice_DX11::BindVertexBuffer(UINT StartSlot
		, ID3D11Buffer* const* ppVertexBuffers
		, const UINT* pStrides
		, const UINT* pOffsets)
	{
		mContext->IASetVertexBuffers(StartSlot, 1, ppVertexBuffers, pStrides, pOffsets);
	}

	void GraphicDevice_DX11::BindIndexBuffer(ID3D11Buffer* pIndexBuffer
		, DXGI_FORMAT Format
		, UINT Offset)
	{
		mContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
	}

	void GraphicDevice_DX11::BindVertexShader(ID3D11VertexShader* pVetexShader)
	{
		mContext->VSSetShader(pVetexShader, 0, 0);
	}

	void GraphicDevice_DX11::BindPixelShader(ID3D11PixelShader* pPixelShader)
	{
		mContext->PSSetShader(pPixelShader, 0, 0);
	}
	void GraphicDevice_DX11::BindComputeShader(ID3D11ComputeShader* pComputeShader)
	{
		mContext->CSSetShader(pComputeShader, 0, 0);
	}
	void GraphicDevice_DX11::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
	{
		mContext->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
	}
	void GraphicDevice_DX11::SetConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE subRes = {};
		mContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
		memcpy(subRes.pData, data, size);
		mContext->Unmap(buffer, 0);
	}
	void GraphicDevice_DX11::BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer * buffer)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			mContext->VSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::HS:
			mContext->HSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::DS:
			mContext->DSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::GS:
			mContext->GSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::PS:
			mContext->PSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::CS:
			mContext->CSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::END:
			break;
		default:
			break;
		}
	}
	void GraphicDevice_DX11::BindsConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer * buffer)
	{
		mContext->VSSetConstantBuffers((UINT)type, 1, &buffer);
		mContext->HSSetConstantBuffers((UINT)type, 1, &buffer);
		mContext->DSSetConstantBuffers((UINT)type, 1, &buffer);
		mContext->GSSetConstantBuffers((UINT)type, 1, &buffer);
		mContext->PSSetConstantBuffers((UINT)type, 1, &buffer);
		mContext->CSSetConstantBuffers((UINT)type, 1, &buffer);
	}
	void GraphicDevice_DX11::BindBuffer(ID3D11Buffer* buffer, void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, data, size);
		mContext->Unmap(buffer, 0);
	}
	void GraphicDevice_DX11::BindShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			mContext->VSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::HS:
			mContext->HSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::DS:
			mContext->DSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::GS:
			mContext->GSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::PS:
			mContext->PSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::CS:
			mContext->CSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::END:
			break;
		default:
			break;
		}
	}
	void GraphicDevice_DX11::BindUnorderedAccess(UINT slot, ID3D11UnorderedAccessView** ppUnorderedAccessViews, const UINT* pUAVInitialCounts)
	{
		mContext->CSSetUnorderedAccessViews(slot, 1, ppUnorderedAccessViews, pUAVInitialCounts);
	}
	void GraphicDevice_DX11::BindSampler(eShaderStage stage, UINT StartSlot, ID3D11SamplerState** ppSamplers)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			mContext->VSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::HS:
			mContext->HSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::DS:
			mContext->DSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::GS:
			mContext->GSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::PS:
			mContext->PSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::CS:
			mContext->CSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::END:
			break;
		default:
			break;
		}
	}
	void GraphicDevice_DX11::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
	{
		mContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
	}
	void GraphicDevice_DX11::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount
							  , UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
	{
		mContext->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
	}
	void GraphicDevice_DX11::ClearTarget()
	{
		FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 0.0f };

		mContext->ClearRenderTargetView(mRenderTarget->GetRTV().Get(), bgColor);
		mContext->ClearDepthStencilView(mDepthStencil->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0.0f);
		mContext->OMSetRenderTargets(1, mRenderTarget->GetRTV().GetAddressOf(), mDepthStencil->GetDSV().Get());
	}
	void GraphicDevice_DX11::UpdateViewPort()
	{
		HWND hWnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		mViewPort =
		{
			0.0f, 0.0f
			,(FLOAT)(winRect.right - winRect.left)
			,(FLOAT)(winRect.bottom - winRect.top)
			,0.0f, 1.0f
		};
		BindViewPort(&mViewPort);
	}
	void GraphicDevice_DX11::Draw()
	{
	}
	void GraphicDevice_DX11::Present()
	{
		mSwapChain->Present(0, 0);
	}
}
