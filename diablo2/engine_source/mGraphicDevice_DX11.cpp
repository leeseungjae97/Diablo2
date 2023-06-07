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
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();

		// 스왑체인에 대한 값 설정

		if (!CreateSwapChain(&swapChainDesc, hWnd))
			return;

		//Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTarget;
		if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D)
			, (void**)(mRenderTarget.GetAddressOf()))))
			return;

		mDevice->CreateRenderTargetView((ID3D11Resource*)mRenderTarget.Get(), nullptr, mRenderTargetView.GetAddressOf());

		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.CPUAccessFlags = 0;

		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.Width = application.GetWidth();
		depthStencilDesc.Height = application.GetHeight();
		depthStencilDesc.ArraySize = 1;

		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;

		depthStencilDesc.MipLevels = 0;
		depthStencilDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA data;
		if (!CreateTexture(&depthStencilDesc, &data))
			return;

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
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
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
		dxgiDesc.BufferDesc.RefreshRate.Numerator = 240;
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
	//bool GraphicDevice_DX11::CreateShader()
	//{
		//std::filesystem::path shaderPath
		//	= std::filesystem::current_path().parent_path();
		//shaderPath += L"\\Shader_SOURCE\\";

		//std::filesystem::path vsPath(shaderPath.c_str());
		//vsPath += L"TriangleVS.hlsl";

		//D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		//	, "main", "vs_5_0", 0, 0, &m::renderer::triangleVSBlob, &m::renderer::errorBlob);

		//// error message
		//if (m::renderer::errorBlob)
		//{
		//	OutputDebugStringA((char*)m::renderer::errorBlob->GetBufferPointer());
		//	m::renderer::errorBlob->Release();
		//}

		//mDevice->CreateVertexShader(m::renderer::triangleVSBlob->GetBufferPointer()
		//	, m::renderer::triangleVSBlob->GetBufferSize()
		//	, nullptr, &m::renderer::triangleVSShader);

		//std::filesystem::path psPath(shaderPath.c_str());
		//psPath += L"TrianglePS.hlsl";

		//D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		//	, "main", "ps_5_0", 0, 0, &m::renderer::trianglePSBlob, &m::renderer::errorBlob);

		//// error message
		//if (m::renderer::errorBlob)
		//{
		//	OutputDebugStringA((char*)m::renderer::errorBlob->GetBufferPointer());
		//	m::renderer::errorBlob->Release();
		//}

		//mDevice->CreatePixelShader(m::renderer::trianglePSBlob->GetBufferPointer()
		//	, m::renderer::trianglePSBlob->GetBufferSize()
		//	, nullptr, &m::renderer::trianglePSShader);

		//D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

		//arrLayout[0].AlignedByteOffset = 0;
		//arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		//arrLayout[0].InputSlot = 0;
		//arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		//arrLayout[0].SemanticName = "POSITION";
		//arrLayout[0].SemanticIndex = 0;

		//arrLayout[1].AlignedByteOffset = 12;
		//arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		//arrLayout[1].InputSlot = 0;
		//arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		//arrLayout[1].SemanticName = "COLOR";
		//arrLayout[1].SemanticIndex = 0;

		//mDevice->CreateInputLayout(arrLayout, 2
		//	, renderer::triangleVSBlob->GetBufferPointer()
		//	, renderer::triangleVSBlob->GetBufferSize()
		//	, &renderer::triangleLayout);

		//return true;
	//}
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
	bool GraphicDevice_DX11::CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data)
	{
		D3D11_TEXTURE2D_DESC dxgiDesc = {};
		dxgiDesc.BindFlags = desc->BindFlags;
		dxgiDesc.Usage = desc->Usage;
		dxgiDesc.CPUAccessFlags = 0;

		dxgiDesc.Format = desc->Format;
		dxgiDesc.Width = desc->Width;
		dxgiDesc.Height = desc->Height;
		dxgiDesc.ArraySize = desc->ArraySize;

		dxgiDesc.SampleDesc.Count = desc->SampleDesc.Count;
		dxgiDesc.SampleDesc.Quality = 0;

		dxgiDesc.MipLevels = desc->MipLevels; // 미리 텍스쳐 사이즈를 크기별로 만들어놓은 경우 레벨 사이즈를 정함.
		dxgiDesc.MiscFlags = desc->MiscFlags;

		//D3D11_SUBRESOURCE_DATA data; // 데이터 넘겨줄때 form
		if (FAILED(mDevice->CreateTexture2D(&dxgiDesc, nullptr, mDepthStencilBuffer.ReleaseAndGetAddressOf())))
			return false;

		if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf())))
			return false;

		return true;
	}
	void GraphicDevice_DX11::BindViewPort(D3D11_VIEWPORT* viewPort)
	{
		mContext->RSSetViewports(1, viewPort);
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
	void GraphicDevice_DX11::Draw()
	{
		FLOAT bgColor[4] = { 0.2f,0.2f, 0.2f, 1.0f };

		mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0.0f);

		HWND hWnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		mViewPort =
		{
			0.0f, 0.0f
			,(float)(winRect.right - winRect.left)
			,(float)(winRect.bottom - winRect.top)
			,0.0f, 1.0f
		};
		BindViewPort(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());

		//UINT vertexsize = sizeof(renderer::Vertex);
		//UINT offset = 0;

		//mContext->IASetVertexBuffers(0, 1, &renderer::triangleBuffer, &vertexsize, &offset);
		//mContext->IASetIndexBuffer(renderer::triangleIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		renderer::mesh->BindBuffer();

		mContext->IASetInputLayout(renderer::triangleLayout);

		mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		

		//mContext->VSSetShader(renderer::triangleVSShader, 0, 0);
		//mContext->PSSetShader(renderer::trianglePSShader, 0, 0);

		renderer::shader->Binds();

		//mContext->Draw(renderer::vertexes.size(), 0);
		//mContext->DrawIndexed(renderer::indexes.size(), 0, 0);
		mContext->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);
		

		mSwapChain->Present(0, 0);
	}
}
