#include "mShader.h"
#include "mRenderer.h"

namespace m
{

	namespace
	{
		std::filesystem::path GetGraphicsShaderSourcePath()
		{
			wchar_t modulePath[MAX_PATH] = {};
			GetModuleFileNameW(nullptr, modulePath, MAX_PATH);

			std::filesystem::path current = std::filesystem::path(modulePath).parent_path();
			for (int i = 0; i < 4 && !current.empty(); ++i)
			{
				std::filesystem::path candidate = current / L"shader_source";
				if (std::filesystem::exists(candidate))
					return candidate;

				current = current.parent_path();
			}

			return std::filesystem::current_path().parent_path() / L"shader_source";
		}
	}
	Shader::Shader()
		: Resource(enums::eResourceType::Shader)
		, mInputLayout(nullptr)
		, mTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
		, mRSType(eRSType::SolidBack)
		, mDSType(eDSType::LessEqua)
		, mBSType(eBSType::AlphaBlend)
		, bGSUse(false)
	{}
	Shader::~Shader()
	{
		if (mInputLayout)
		{
			mInputLayout->Release();
			mInputLayout = nullptr;
		}
	}
	HRESULT Shader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
	bool Shader::Create(const eShaderStage stage
		, const std::wstring& fileName
		, const std::string& funcName)
	{
		std::filesystem::path fullPath = GetGraphicsShaderSourcePath() / fileName;

		ID3DBlob* errorBlob = nullptr;
		if (stage == eShaderStage::VS)
		{
			if (!GetDevice()->CompileFromfile(fullPath, funcName, "vs_5_0", mVSBlob.GetAddressOf()))
				return false;

			return GetDevice()->CreateVertexShader(mVSBlob->GetBufferPointer()
				, mVSBlob->GetBufferSize(), mVS.GetAddressOf());
		}
		else if (stage == eShaderStage::GS)
		{
			if (!GetDevice()->CompileFromfile(fullPath, funcName, "gs_5_0", mGSBlob.GetAddressOf()))
				return false;

			return GetDevice()->CreateGeometryShader(mGSBlob->GetBufferPointer()
											  , mGSBlob->GetBufferSize(), mGS.GetAddressOf());
		}
		else if (stage == eShaderStage::PS)
		{
			if (!GetDevice()->CompileFromfile(fullPath, funcName, "ps_5_0", mPSBlob.GetAddressOf()))
				return false;

			return GetDevice()->CreatePixelShader(mPSBlob->GetBufferPointer()
				, mPSBlob->GetBufferSize(), mPS.GetAddressOf());
		}


		return false;
	}
	void Shader::Binds()
	{
		GetDevice()->BindPrimitiveTopology(mTopology);
		GetDevice()->BindInputLayout(mInputLayout);

		GetDevice()->BindVertexShader(mVS.Get());
		if(bGSUse) GetDevice()->BindGeometryShader(mGS.Get());
		else GetDevice()->BindGeometryShader(mGSN.Get());
		GetDevice()->BindPixelShader(mPS.Get());

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> rsState = renderer::rasterizerStates[(UINT)mRSType];
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState = renderer::depthStencilStates[(UINT)mDSType];
		Microsoft::WRL::ComPtr<ID3D11BlendState> bsState = renderer::blendStates[(UINT)mBSType];

		GetDevice()->BindRasterizeState(rsState.Get());
		GetDevice()->BindDepthStencilState(dsState.Get());
		GetDevice()->BindBlendState(bsState.Get());
	}
}