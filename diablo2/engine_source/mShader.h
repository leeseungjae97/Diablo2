#pragma once
#include "mResource.h"
#include "mGraphicDevice_DX11.h"
namespace m
{
	using namespace graphics;
    class Shader :
        public Resource
    {
	public:
		Shader();
		~Shader();

		virtual HRESULT Load(const std::wstring& path) override;

		bool Create(const eShaderStage stage, const std::wstring& fileName, const std::string& funcName);
		void Binds();

	private:
		Microsoft::WRL::ComPtr<ID3DBlob> mVSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mHSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mDSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mGSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mPSBlob;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVS;
		Microsoft::WRL::ComPtr<ID3D11HullShader> mHS;
		Microsoft::WRL::ComPtr<ID3D11DomainShader> mDS;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGS;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPS;
    };
}


