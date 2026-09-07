#include "mComputeShader.h"
#include "mGraphicDevice_DX11.h"
namespace m::graphics
{

	namespace
	{
		std::filesystem::path GetComputeShaderSourcePath()
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
	ComputeShader::ComputeShader(int x, int y, int z)
		: Resource(enums::eResourceType::ComputeShader)
	{
		mThreadGroupCountX = x;
		mThreadGroupCountY = y;
		mThreadGroupCountZ = z;
	}
	ComputeShader::ComputeShader()
		: Resource(enums::eResourceType::ComputeShader)
	{
		mThreadGroupCountX = 32;
		mThreadGroupCountY = 32;
		mThreadGroupCountZ = 1;
	}
	ComputeShader::~ComputeShader()
	{
	}
	bool ComputeShader::Create(const std::wstring& name, const std::string& methodName)
	{
		std::filesystem::path fullPath = GetComputeShaderSourcePath() / name;

		ID3DBlob* errorBlob = nullptr;
		if (!graphics::GetDevice()->CompileFromfile(fullPath, methodName, "cs_5_0", mCSBlob.GetAddressOf()))
			return false;

		return graphics::GetDevice()->CreateComputeShader(mCSBlob->GetBufferPointer()
											   , mCSBlob->GetBufferSize(), mCS.GetAddressOf());
	}
	void ComputeShader::OnExcute()
	{
		Binds();

		GetDevice()->BindComputeShader(mCS.Get());
		GetDevice()->Dispatch(mGroupX, mGroupY, mGroupZ);
	}
	void ComputeShader::Binds()
	{
	}
	void ComputeShader::Clear()
	{
	}
}
