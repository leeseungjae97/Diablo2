#include "mRenderer.h"
#include "mResources.h"
#include "mTexture.h"
#include "mMaterial.h"

namespace renderer
{
	using namespace m;
	using namespace m::graphics;
	vector<Vertex> fullSizeRectVertex;
	vector<Vertex> rectVertex;
	vector<UINT> rectIndexes;
	vector<UINT> fullSizeRectIndexes;

	m::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::END] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};

	void SetupState()
	{
		// Input layout ���� ���� ������ �Ѱ�����Ѵ�.
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;


		std::shared_ptr<Shader> shader = m::Resources::Find<Shader>(L"TriangleShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = m::Resources::Find<Shader>(L"SpriteShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		//Sampler State
		D3D11_SAMPLER_DESC desc = {};
		desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSampler(&desc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		desc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSampler(&desc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
	}

	void LoadBuffer()
	{
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(rectVertex.data(), rectVertex.size());
		mesh->CreateIndexBuffer(rectIndexes.data(), rectIndexes.size());

		std::shared_ptr<Mesh> fullMesh = std::make_shared<Mesh>();
		Resources::Insert(L"fullRectMesh", fullMesh);

		fullMesh->CreateVertexBuffer(fullSizeRectVertex.data(), fullSizeRectVertex.size());
		fullMesh->CreateIndexBuffer(rectIndexes.data(), rectIndexes.size());

		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));
	}

	void LoadShader()
	{
		//m::graphics::GetDevice()->CreateShader();
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		m::Resources::Insert(L"TriangleShader", shader);

		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		m::Resources::Insert(L"SpriteShader", spriteShader);
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"amazon_attack1", L"..\\Resources\\texture\\character\\amazon_attack1.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"amazonAttack1", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"amazon_walk", L"..\\Resources\\texture\\character\\amazon_walk.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"amazonWalk", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"main_menu_1", L"..\\Resources\\texture\\main\\back\\mainMenu1.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"mainMenu1", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"m_button_blank", L"..\\Resources\\texture\\ui\\MediumButtonBlank.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"mButtonBlank", spriteMateiral);
		}
	}

	void Initialize()
	{
		// triangle
		rectVertex.resize(4);

		rectVertex[0].pos = Vector3(0.0f, 0.0f, 0.0f);
		rectVertex[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		rectVertex[0].uv = Vector2(0.0f, 0.0f);

		rectVertex[1].pos = Vector3(0.5f, 0.0f, 0.0f);
		rectVertex[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		rectVertex[1].uv = Vector2(1.0f, 0.0f);

		rectVertex[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		rectVertex[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		rectVertex[2].uv = Vector2(1.0f, 1.0f);

		rectVertex[3].pos = Vector3(0.0f, -0.5f, 0.0f);
		rectVertex[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		rectVertex[3].uv = Vector2(0.0f, 1.0f);

		rectIndexes.push_back(0);
		rectIndexes.push_back(1);
		rectIndexes.push_back(2);

		rectIndexes.push_back(0);
		rectIndexes.push_back(2);
		rectIndexes.push_back(3);

		fullSizeRectVertex.resize(4);

		fullSizeRectVertex[0].pos = Vector3(-1.0f, 1.0f, 0.0f);
		fullSizeRectVertex[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		fullSizeRectVertex[0].uv = Vector2(0.0f, 0.0f);

		fullSizeRectVertex[1].pos = Vector3(1.f, 1.0f, 0.0f);
		fullSizeRectVertex[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		fullSizeRectVertex[1].uv = Vector2(1.0f, 0.0f);

		fullSizeRectVertex[2].pos = Vector3(1.f, -1.f, 0.0f);
		fullSizeRectVertex[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		fullSizeRectVertex[2].uv = Vector2(1.0f, 1.0f);

		fullSizeRectVertex[3].pos = Vector3(-1.0f, -1.0f, 0.0f);
		fullSizeRectVertex[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		fullSizeRectVertex[3].uv = Vector2(0.0f, 1.0f);

		fullSizeRectIndexes.push_back(0);
		fullSizeRectIndexes.push_back(1);
		fullSizeRectIndexes.push_back(2);

		fullSizeRectIndexes.push_back(0);
		fullSizeRectIndexes.push_back(2);
		fullSizeRectIndexes.push_back(3);


		LoadBuffer();
		LoadShader();
		SetupState();
	}
	void Release()
	{
		for (ConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}
	}
}



