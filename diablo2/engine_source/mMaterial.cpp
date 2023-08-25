#include "mMaterial.h"

namespace m::graphics
{
	Material::Material()
		: Resource(m::enums::eResourceType::Material)
		, mShader(nullptr)
		, mTexture(nullptr)
		, mMode(eRenderingMode::Opaque)
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
		if(mTexture)
			mTexture->BindShaderResource(eShaderStage::PS, 0);

		if(mShader)
			mShader->Binds();
	}

	void Material::Binds(UINT slot)
	{
		if (mTexture)
			mTexture->BindShaderResource(eShaderStage::PS, slot);

		if (mShader)
			mShader->Binds();
	}

	void Material::Clear()
	{
		//if (mTexture)
			mTexture->Clear();
	}
}