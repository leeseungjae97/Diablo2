#pragma once
#include "mResource.h"
#include "mTexture.h"
#include "mShader.h"

namespace m::graphics
{
	class Material :
		public Resource
	{
	public:
		Material();
		~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void Binds();
		void Binds(UINT slot);
		void Clear();

		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
		std::shared_ptr<Shader> GetShader() { return mShader; }
		std::shared_ptr<Texture> GetTexture() { return mTexture; }

		void SetRenderingMode(eRenderingMode mode) { mMode = mode; }
		eRenderingMode GetRenderingMode() { return mMode; }
	private:
		std::shared_ptr<Shader> mShader;
		std::shared_ptr<Texture> mTexture;
		eRenderingMode mMode;
	};
}

