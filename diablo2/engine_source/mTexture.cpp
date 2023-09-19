#include "mTexture.h"
#include "mGraphicDevice_DX11.h"

namespace m::graphics
{
	float Texture::fWidRatio = RESOL_WID / 800.f;
	float Texture::fHeiRatio = RESOL_HEI / 600.f;
	Texture::Texture()
		: Resource(enums::eResourceType::Texture)
		, mImage{}
		, mTexture(nullptr)
		, mSRV(nullptr)
		, mSlot(0)
		, mDesc{}
	{
	}

	Texture::~Texture()
	{

	}
	HRESULT Texture::MergeTex2(std::vector<std::shared_ptr<Texture>> mergeTextures, UINT width, UINT height, int count)
	{
		ScratchImage atlasImage;
		HRESULT hr = S_OK;
	    atlasImage.Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, width, height, 1, 1);
		
		//for(int i = 0 ; i < mergeTextures.size(); ++i)
		GUID format = GetWICCodec(WIC_CODEC_PNG);
		for (std::shared_ptr<Texture> tex : mergeTextures)
		{

			//int randIndex = rand() % mergeTextures.size();

			//int randPosX = rand() % 10;
			//int randPosY = rand() % 10;

			//++randPosX;
			//++randPosY;

			//std::shared_ptr<Texture> tex = mergeTextures[i];
			ScratchImage& image = tex->GetScratchImage();
			//hr = SaveToWICFile(
			//	(*image).GetImage(0, 0, 0)
			//	, WIC_FLAGS::WIC_FLAGS_NONE
			//	, format
			//	, L"save3.png"
			//	, nullptr
			//);
			//if (FAILED(hr))
			//{
			//	return hr;
			//}
			// DirectX 텍스처에 이미지 데이터 복사

			//hr = CopyRectangle(*image.GetImage(0, 0, 0), Rect(0, 0, image.GetMetadata().width, image.GetMetadata().height)
			hr = CopyRectangle(*image.GetImage(0, 0, 0), Rect(0, 0, image.GetMetadata().width, image.GetMetadata().height)
				,*atlasImage.GetImage(0, 0, 0), TEX_FILTER_DEFAULT, 0, 0);

			if (FAILED(hr))
			{
				CoUninitialize();
				return hr;
			}
		}
		CreateShaderResourceView
		(
			GetDevice()->GetID3D11Device()
			, atlasImage.GetImages()
			, atlasImage.GetImageCount()
			, atlasImage.GetMetadata()
			, mSRV.GetAddressOf()
		);

		mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

		mImage.Initialize2D(
			atlasImage.GetMetadata().format,
			atlasImage.GetMetadata().width,
			atlasImage.GetMetadata().height,
			atlasImage.GetMetadata().arraySize,
			atlasImage.GetMetadata().mipLevels
		);

		//hr = SaveToWICFile(
		//	*mImage.GetImage(0, 0, 0)
		//	, WIC_FLAGS::WIC_FLAGS_NONE
		//	, format
		//	, L"save4.png"
		//	, nullptr
		//);

		mWidth = atlasImage.GetMetadata().width;
		mHeight = atlasImage.GetMetadata().height;
		//CoUninitialize();
		return S_OK;
	}

	HRESULT Texture::MergeTex(std::vector<std::shared_ptr<Texture>> mergeTextures, std::vector<Vector2> texturePosition, UINT perWidth, UINT perHeight, UINT oneLength, UINT addtionCount, const std::wstring& mergedTextureName)
	{
		ScratchImage atlasImage;
		UINT imageCount = texturePosition.size() + addtionCount;
		UINT column = imageCount <= oneLength ? 1 : imageCount / oneLength;

		UINT atWid = perWidth * oneLength;
		UINT atHei = perHeight * column;
		atlasImage.Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, atWid, atHei, 1, 1);

		int index = 0;
		for (std::shared_ptr<Texture> tex : mergeTextures)
		{
			const ScratchImage& image = tex->GetScratchImage();
			Vector2 pos = texturePosition[index];
			++index;

			if (pos == Vector2(-99.f, -99.f)) continue;
			UINT wid = perWidth * (UINT)pos.x;
			UINT hei = perHeight * (UINT)pos.y;

			CopyRectangle(*image.GetImage(0, 0, 0), Rect(0, 0, image.GetMetadata().width, image.GetMetadata().height),
				*atlasImage.GetImage(0, 0, 0), TEX_FILTER_DEFAULT, wid, hei);
		}

		CreateShaderResourceView
		(
			GetDevice()->GetID3D11Device()
			, atlasImage.GetImages()
			, atlasImage.GetImageCount()
			, atlasImage.GetMetadata()
			, mSRV.GetAddressOf()
		);

		mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

		mImage.Initialize2D(
			atlasImage.GetMetadata().format,
			atlasImage.GetMetadata().width,
			atlasImage.GetMetadata().height,
			atlasImage.GetMetadata().arraySize,
			atlasImage.GetMetadata().mipLevels
		);

		mWidth = mImage.GetMetadata().width;
		mHeight = mImage.GetMetadata().height;

		return S_OK;
	}
	
	HRESULT Texture::CreateTex(UINT perWidth, UINT perHeight, UINT oneAnimLength, const std::wstring& path)
	{
		ScratchImage atlasImage;
		HRESULT hr = S_OK;
		UINT sumWidth = 0;
		UINT fileCount = 0;

		wchar_t ext[_MAX_EXT] = {};
		_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT);
		ScratchImage image;

		std::filesystem::path fs(path);

		mPerWidth = perWidth;
		mPerHeight = perHeight;

		for (const auto& p : std::filesystem::recursive_directory_iterator(path)) fileCount++;

		UINT column = fileCount / oneAnimLength;
		//column += 1;

		hr = atlasImage.Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, mPerWidth * oneAnimLength, mPerHeight * column, 1, 1);

		if (FAILED(hr))
		{
			CoUninitialize();
			return hr;
		}

		int xidx = 0;
		int yidx = 0;

		int tt = 0;
		for (const auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = p.path().wstring();

			if (_wcsicmp(ext, L".dds") == 0) hr = LoadFromDDSFile(fullName.c_str(), DDS_FLAGS_NONE, nullptr, image);
			else if (_wcsicmp(ext, L".tga") == 0)hr = LoadFromTGAFile(fullName.c_str(), nullptr, image);
			else if (_wcsicmp(ext, L".hdr") == 0) hr = LoadFromHDRFile(fullName.c_str(), nullptr, image);
			else hr = LoadFromWICFile(fullName.c_str(), WIC_FLAGS_NONE, nullptr, image);
			if (FAILED(hr))
			{
				CoUninitialize();
				return hr;
			}

			ScratchImage convertedImage;
			hr = Convert(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DXGI_FORMAT_R8G8B8A8_UNORM, TEX_FILTER_DEFAULT, TEX_THRESHOLD_DEFAULT, convertedImage);
			if (FAILED(hr))
			{
				CoUninitialize();
				return hr;
			}


			if (xidx != 0) sumWidth += convertedImage.GetMetadata().width;

			if (sumWidth >= mPerWidth * oneAnimLength)
			{
				sumWidth = 0;
				xidx = 0;
				yidx++;
			}

			UINT wid = convertedImage.GetMetadata().width * xidx;
			UINT hei = convertedImage.GetMetadata().height * yidx;

			hr = CopyRectangle(*convertedImage.GetImage(0, 0, 0), Rect(0, 0, convertedImage.GetMetadata().width, convertedImage.GetMetadata().height),
				*atlasImage.GetImage(0, 0, 0), TEX_FILTER_DEFAULT, wid, hei);
			if (FAILED(hr)) return hr;

			tt++;
			xidx++;
		}

		if(path == L"..\\Resources\\texture\\enemy\\andariel\\special")
		{
			GUID format = GetWICCodec(WIC_CODEC_PNG);
			hr = SaveToWICFile(
				*atlasImage.GetImage(0, 0, 0)
				, WIC_FLAGS::WIC_FLAGS_NONE
				, format
				, L"save4.png"
				, nullptr
			);
		}
		
		CreateShaderResourceView
		(
			GetDevice()->GetID3D11Device()
			, atlasImage.GetImages()
			, atlasImage.GetImageCount()
			, atlasImage.GetMetadata()
			, mSRV.GetAddressOf()
		);
		mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

		mImage.Initialize2D(
			atlasImage.GetMetadata().format,
			atlasImage.GetMetadata().width,
			atlasImage.GetMetadata().height,
			atlasImage.GetMetadata().arraySize,
			atlasImage.GetMetadata().mipLevels
		);

		mWidth = mImage.GetMetadata().width;
		mHeight = mImage.GetMetadata().height;
	}
	bool Texture::Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag)
	{
		if (mTexture == nullptr)
		{
			mDesc.BindFlags = bindFlag;
			mDesc.Usage = D3D11_USAGE_DEFAULT;
			mDesc.CPUAccessFlags = 0;
			mDesc.Format = format;
			mDesc.Width = width;
			mDesc.Height = height;
			mDesc.ArraySize = 1;

			mDesc.SampleDesc.Count = 1;
			mDesc.SampleDesc.Quality = 0;

			mDesc.MipLevels = 1;
			mDesc.MiscFlags = 0;

			mWidth = width;
			mHeight = height;

			if (!GetDevice()->CreateTexture2D(&mDesc, nullptr, mTexture.GetAddressOf()))
				return false;
		}

		if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
		{
			if (!GetDevice()->CreateDepthStencilView(mTexture.Get(), nullptr, mDSV.GetAddressOf()))
				return false;
		}
		if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};
			tSRVDesc.Format = mDesc.Format;
			tSRVDesc.Texture2D.MipLevels = 1;
			tSRVDesc.Texture2D.MostDetailedMip = 0;
			tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateShaderResourceView(mTexture.Get(), &tSRVDesc, mSRV.GetAddressOf()))
				return false;
		}

		if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
		{
			D3D11_RENDER_TARGET_VIEW_DESC tSRVDesc = {};
			tSRVDesc.Format = mDesc.Format;
			tSRVDesc.Texture2D.MipSlice = 0;
			tSRVDesc.ViewDimension = D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateRenderTargetView(mTexture.Get(), nullptr, mRTV.GetAddressOf()))
				return false;
		}

		if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC tUAVDesc = {};
			tUAVDesc.Format = mDesc.Format;
			tUAVDesc.Texture2D.MipSlice = 0;
			tUAVDesc.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateUnordedAccessView(mTexture.Get(), &tUAVDesc, mUAV.GetAddressOf()))
				return false;
		}

		return true;
	}
	ScratchImage Texture::loadImage(const std::wstring& path)
	{
		//= CoInitializeEx(nullptr, COINIT_MULTITHREADED)
		HRESULT hr;
		wchar_t szExtension[50] = {};
		_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, 50);

		ScratchImage image;
		
		std::wstring extension = szExtension;
		if (extension == L".dds" || extension == L".DDS")
		{
			if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, image)))
			{
				image.Initialize2D(DXGI_FORMAT_B8G8R8A8_UNORM, 0, 0, 1, 1);
				return image;
			}
				
		}
		else if (extension == L".tga" || extension == L".TGA")
		{
			if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, image)))
			{
				image.Initialize2D(DXGI_FORMAT_B8G8R8A8_UNORM, 0, 0, 1, 1);
				return image;
			}
		}
		else
		{
			if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, image)))
			{
				image.Initialize2D(DXGI_FORMAT_B8G8R8A8_UNORM, 0, 0, 1, 1);
				return image;
			}
		}
		CreateShaderResourceView
		(
			GetDevice()->GetID3D11Device()
			, image.GetImages()
			, image.GetImageCount()
			, image.GetMetadata()
			, mSRV.GetAddressOf()
		);
		mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

		mImage.Initialize2D(
			image.GetMetadata().format,
			image.GetMetadata().width,
			image.GetMetadata().height,
			image.GetMetadata().arraySize,
			image.GetMetadata().mipLevels
		);

		mWidth = image.GetMetadata().width;
		mHeight = image.GetMetadata().height;

		//CoUninitialize();
		return image;
	}
	HRESULT Texture::Load(const std::wstring& path)
	{
		wchar_t szExtension[50] = {};
		_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, 50);

		std::wstring extension = szExtension;
		if (extension == L".dds" || extension == L".DDS")
		{
			if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}
		else if (extension == L".tga" || extension == L".TGA")
		{
			if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, mImage)))
				return S_FALSE;
		}
		else // WIC (png, jpg, jpeg, bmp )
		{
			if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}

		CreateShaderResourceView
		(
			GetDevice()->GetID3D11Device()
			, mImage.GetImages()
			, mImage.GetImageCount()
			, mImage.GetMetadata()
			, mSRV.GetAddressOf()
		);
		mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

		mWidth = mImage.GetMetadata().width;
		mHeight = mImage.GetMetadata().height;

		return S_OK;
	}

	void Texture::BindShaderResource(eShaderStage stage, UINT startSlot)
	{
		mSlot = startSlot;
		GetDevice()->BindShaderResource(stage, mSlot, mSRV.GetAddressOf());
	}
	void Texture::BindUnorderedAccessViews(UINT slot)
	{
		mSlot = slot;
		UINT i = -1;
		GetDevice()->BindUnorderedAccess(mSlot, mUAV.GetAddressOf(), &i);
	}
	void Texture::ClearUnorderedAccessViews(UINT slot)
	{
		ID3D11UnorderedAccessView* p = nullptr;
		UINT i = -1;
		GetDevice()->BindUnorderedAccess(mSlot, &p, &i);
	}
	void Texture::Clear()
	{
		ID3D11ShaderResourceView* srv = nullptr;
		int slot = 0;
		if(this != nullptr )
		{
			slot = mSlot;
		}
		GetDevice()->BindShaderResource(eShaderStage::VS, slot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::DS, slot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::GS, slot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::HS, slot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::CS, slot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::PS, slot, &srv);
	}

    void Texture::SetTexture(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture)
    {
		mTexture = texture;
		texture->GetDesc(&mDesc);

		mWidth = mDesc.Width;
		mHeight = mDesc.Height;
    }
}
