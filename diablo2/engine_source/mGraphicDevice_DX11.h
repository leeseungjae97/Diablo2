#pragma once
#include "_Engine.h"
#include "mGraphics.h"

namespace m::graphics
{
	class GraphicDevice_DX11
	{
	public:
		GraphicDevice_DX11();
		~GraphicDevice_DX11();

		bool CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd);
		bool CreateTexture(const D3D11_TEXTURE2D_DESC* desc, D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D);
		bool CreateTexture(const D3D11_TEXTURE2D_DESC* desc, D3D11_SUBRESOURCE_DATA* pInitialData);
		bool CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, ID3DBlob* byteCode, ID3D11InputLayout** ppInputLayout);
		bool CreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data);
		bool CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView);
		bool CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView);
		bool CompileFromfile(const std::wstring& fileName, const std::string& funcName, const std::string& version, ID3DBlob** ppCode);
		bool CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView);
		bool CreateUnorderedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView);
		bool CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11VertexShader** ppVertexShader);
		bool CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11PixelShader** ppPixelShader);
		bool CreateSampler(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState);

		void BindInputLayout(ID3D11InputLayout* pInputLayout);
		void BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);
		void BindVertexBuffer(UINT StartSlot, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets);
		void BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset);
		void BindVertexShader(ID3D11VertexShader* pVetexShader);
		void BindPixelShader(ID3D11PixelShader* pPixelShader);
		void SetConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size);
		void BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		void BindsConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		void BindShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV);
		void BindSampler(eShaderStage stage, UINT StartSlot, ID3D11SamplerState** ppSamplers);
		void BindViewPort(D3D11_VIEWPORT* viewPort);

		void DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);\
		void ClearTarget();
		void UpdateViewPort();
		void Draw();
		void Present();

		ID3D11Device* GetID3D11Device() { return mDevice.Get(); }

	private:
		Microsoft::WRL::ComPtr<ID3D11Device>			mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>		mContext;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			mRenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	mRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			mDepthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	mDepthStencilView;
		Microsoft::WRL::ComPtr<IDXGISwapChain>			mSwapChain;
		D3D11_VIEWPORT									mViewPort;
	};

	inline GraphicDevice_DX11*& GetDevice()
	{
		static GraphicDevice_DX11* device = nullptr;
		return device;
	}
}
