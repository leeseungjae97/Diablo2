#include "mMaterial.h"

namespace m::graphics
{
	Material::Material()
		: Resource(m::enums::eResourceType::Material)
		, mShader(nullptr)
		, mTexture(nullptr)
	{

	}

	Material::~Material()
	{}

	HRESULT Material::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Material::Binds()
	{
		mTexture->BindShader(eShaderStage::PS, 0);
		mShader->Binds();
	}
	void Material::Clear()
	{
		mTexture->Clear();
	}
}