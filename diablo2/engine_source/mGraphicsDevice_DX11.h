#pragma once
#include "mGraphics.h"

namespace m::graphics{
	class GraphicsDevice_DX11 {
	public:
		GraphicsDevice_DX11();
		~GraphicsDevice_DX11();

		//bool CreateSwapChain(DXGI_SWAP_CHAIN_DESC desc);
		//bool CreateBuffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* initial_data, ID3D11Buffer** buffer);
		//bool CreateTexture(const D3D11_TEXTURE2D_DESC* pDesc, D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D);
		//bool CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView);
		//bool CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView);
		//bool CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState);
		//bool CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState);
		//bool CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState);
		//bool CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState);

		////bool CreateShader(const graphics::ShaderStage stage, const std::wstring& file, const std::string& funcName);
		//bool CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements
		//	, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout);
		//bool CompileFromFile(const std::wstring& fileName, const std::string& funcName, const std::string& version, ID3DBlob** ppCode);
		//bool CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11VertexShader** ppVertexShader);
		//bool CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11PixelShader** ppVertexShader);
		//bool CreateGeometryShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11GeometryShader** ppGeometryShader);
		//bool CreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ComputeShader** ppVertexShader);
		//bool CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView);
		//bool CreateUnorderedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView);

		//void BindInputLayout(ID3D11InputLayout* pInputLayout);
		//void BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);
		////void BindSamplers(eShaderStage stage, UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers);
		//void BindsSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers);
		//void BindVertexBuffer(UINT startSlot, UINT numBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT stride, const UINT offset = 0);
		//void BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT format, UINT Offset = 0);
		//void CopyResource(ID3D11Resource* pDstResource, ID3D11Resource* pSrcResource);

		//void BindVertexShader(ID3D11VertexShader* pVertexShader);
		//void BindHullShader(ID3D11HullShader* pHullShader);
		//void BindDomainShader(ID3D11DomainShader* pDomainShader);
		//void BindGeometryShader(ID3D11GeometryShader* pGeometryShader);
		//void BindPixelShader(ID3D11PixelShader* pPixelShader);
		//void BindComputeShader(ID3D11ComputeShader* pPixelShader);
		//void Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ);

		//void BindViewports(D3D11_VIEWPORT* viewPort);
		//void SetData(ID3D11Buffer* buffer, void* data, UINT size);
		//void BindRasterizerState(ID3D11RasterizerState* pRasterizerState);
		//void BindDepthStencilState(ID3D11DepthStencilState* pDepthStencilState);
		//void BindBlendState(ID3D11BlendState* pBlendState);
		////void BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		////void BindShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV);
		//void BindUnorderedAccessViews(UINT startSlot, ID3D11UnorderedAccessView** ppUnorderedAccessViews, const UINT* pUAVInitialCounts);

		//void Clear();
		//void AdjustViewport();
		//void Draw(UINT VertexCount, UINT StartVertexLocation);
		//void DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
		//void DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation);
		//void Present();
		//void Render();

		//ID3D11Device* GetID3D11Device() { return mDevice.Get(); }
		//ID3D11DeviceContext* GetID3D11DeviceContext() { return mContext.Get(); }
		//Viewport GetViewPort();
		//std::shared_ptr<class Texture> GetRenderTargetTexture() { return mRenderTargetTexture; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Device>			mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>		mContext;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			mRenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	mRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			mDepthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	mDepthStencilView;
		Microsoft::WRL::ComPtr<IDXGISwapChain>			mSwapChain;
		//std::shared_ptr<class Texture> mRenderTargetTexture;
		//std::shared_ptr<class Texture> mDepthStencilTexture;
	};

	// This is a helper to get access to a global device instance
	//	- The engine uses this, but it is not necessary to use a single global device object
	//	- This is not a lifetime managing object, just a way to globally expose a reference to an object by pointer
	inline GraphicsDevice_DX11*& GetDevice() {
		static GraphicsDevice_DX11* device = nullptr;
		return device;
	}
}
