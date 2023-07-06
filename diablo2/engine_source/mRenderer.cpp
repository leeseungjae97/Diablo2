#include "mRenderer.h"
#include "mResources.h"
#include "mTexture.h"
#include "mMaterial.h"

namespace renderer
{
	using namespace m;
	using namespace m::graphics;
	vector<Vertex> doubleSizeRectVertex;
	vector<Vertex> halfSizeRectVertex;
	vector<Vertex> rectVertex;
	vector<UINT> rectIndexes;

	m::graphics::ConstantBuffer* constantBuffers[(UINT)eCBType::END] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	std::vector<m::Camera*> cameras = {};

	void SetupState()
	{
#pragma region InputLayout
		// Input layout 정점 구조 정보를 넘겨줘야한다.
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



		//int iNumElement = sizeof(arrLayout) / sizeof(D3D11_INPUT_ELEMENT_DESC);
		std::shared_ptr<Shader> triangleShader = m::Resources::Find<Shader>(L"TriangleShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, triangleShader->GetVSCode()
			, triangleShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> spriteShader = m::Resources::Find<Shader>(L"SpriteShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, spriteShader->GetVSCode()
			, spriteShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> gridShader = m::Resources::Find<Shader>(L"GridShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, gridShader->GetVSCode()
			, gridShader->GetInputLayoutAddressOf());
#pragma endregion
#pragma region Sampler State
		//Sampler State
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer State
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
#pragma endregion
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

		//less
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

		//less eqauls
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::LessEqua].GetAddressOf());

		//Greater
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		//No Write
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		//None
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion
#pragma region Blend State
		D3D11_BLEND_DESC blendDesc = {};

		//default
		blendStates[(UINT)eBSType::Default] = nullptr;

		// Alpha Blend
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		// one one
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;

		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion
	}

	void LoadMesh()
	{
		halfSizeRectVertex.resize(4);
		doubleSizeRectVertex.resize(4);
		rectVertex.resize(4);

		halfSizeRectVertex[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		halfSizeRectVertex[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		halfSizeRectVertex[0].uv = Vector2(0.0f, 0.0f);

		halfSizeRectVertex[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		halfSizeRectVertex[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		halfSizeRectVertex[1].uv = Vector2(1.0f, 0.0f);

		halfSizeRectVertex[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		halfSizeRectVertex[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		halfSizeRectVertex[2].uv = Vector2(1.0f, 1.0f);

		halfSizeRectVertex[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		halfSizeRectVertex[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		halfSizeRectVertex[3].uv = Vector2(0.0f, 1.0f);

		doubleSizeRectVertex[0].pos = Vector3(-1.0f, 1.0f, 0.0f);
		doubleSizeRectVertex[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		doubleSizeRectVertex[0].uv = Vector2(0.0f, 0.0f);

		doubleSizeRectVertex[1].pos = Vector3(1.0f, 1.0f, 0.0f);
		doubleSizeRectVertex[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		doubleSizeRectVertex[1].uv = Vector2(1.0f, 0.0f);

		doubleSizeRectVertex[2].pos = Vector3(1.0f, -1.0f, 0.0f);
		doubleSizeRectVertex[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		doubleSizeRectVertex[2].uv = Vector2(1.0f, 1.0f);

		doubleSizeRectVertex[3].pos = Vector3(1.0f, -1.0f, 0.0f);
		doubleSizeRectVertex[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		doubleSizeRectVertex[3].uv = Vector2(0.0f, 1.0f);

		rectVertex[0].pos = Vector3(0.0f, 0.0f, 0.0f);
		rectVertex[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		rectVertex[0].uv = Vector2(0.0f, 0.0f);

		rectVertex[1].pos = Vector3(1.f, 0.0f, 0.0f);
		rectVertex[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		rectVertex[1].uv = Vector2(1.0f, 0.0f);

		rectVertex[2].pos = Vector3(1.f, -1.0f, 0.0f);
		rectVertex[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		rectVertex[2].uv = Vector2(1.0f, 1.0f);

		rectVertex[3].pos = Vector3(0.0f, -1.0f, 0.0f);
		rectVertex[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		rectVertex[3].uv = Vector2(0.0f, 1.0f);

		rectIndexes.push_back(0);
		rectIndexes.push_back(1);
		rectIndexes.push_back(2);

		rectIndexes.push_back(0);
		rectIndexes.push_back(2);
		rectIndexes.push_back(3);

		std::shared_ptr<Mesh> halfMesh = std::make_shared<Mesh>();
		Resources::Insert(L"halfRectMesh", halfMesh);
		halfMesh->CreateVertexBuffer(halfSizeRectVertex.data(), halfSizeRectVertex.size());
		halfMesh->CreateIndexBuffer(rectIndexes.data(), rectIndexes.size());

		std::shared_ptr<Mesh> doubleMesh = std::make_shared<Mesh>();
		Resources::Insert(L"doubleRectMesh", doubleMesh);
		doubleMesh->CreateVertexBuffer(doubleSizeRectVertex.data(), doubleSizeRectVertex.size());
		doubleMesh->CreateIndexBuffer(rectIndexes.data(), rectIndexes.size());

		std::shared_ptr<Mesh> fullMesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", fullMesh);
		fullMesh->CreateVertexBuffer(rectVertex.data(), rectVertex.size());
		fullMesh->CreateIndexBuffer(rectIndexes.data(), rectIndexes.size());
	}

	void LoadBuffer()
	{
		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		//constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Animator);
		//constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(AnimatorCB));
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

		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		m::Resources::Insert(L"GridShader", gridShader);
	}

	void LoadMaterial()
	{
		std::shared_ptr<Shader> spriteShader = m::Resources::Find<Shader>(L"SpriteShader");
#pragma region Characters
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
#pragma endregion
#pragma region Background
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"main_menu_2", L"..\\Resources\\texture\\ui\\mainMenu\\mainMenu2.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"mainMenu2", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"main_menu_2_1", L"..\\Resources\\texture\\ui\\mainMenu\\mainMenu2_1.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"mainMenu2_1", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"character_select_1", L"..\\Resources\\texture\\ui\\characterSelect\\charactercreationscreenEXP.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"characterSelect1", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"charactercreation_test", L"..\\Resources\\texture\\ui\\characterSelect\\charactercreation_.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"charactercreationTest", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"test_logo", L"..\\Resources\\texture\\ui\\mainMenu\\test_logo.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"testLogo", spriteMateiral);
		}
#pragma endregion
#pragma region Buttons
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"m_medium_button_blank", L"..\\Resources\\texture\\ui\\MediumButtonBlank.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"mMediumButtonBlank", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"m_button_blank", L"..\\Resources\\texture\\ui\\widebuttonblank.bmp");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"mWideButtonBlank", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"m_button_blank_02", L"..\\Resources\\texture\\ui\\widebuttonblank02.bmp");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"mWideButtonBlankClick", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"tab_bt", L"..\\Resources\\texture\\ui\\tabbt.bmp");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"tabBt", spriteMateiral);
		}
#pragma endregion
#pragma region Tiles
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"town_floors", L"..\\Resources\\texture\\act1_town\\town_floor.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			//spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"townFloors", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"test_tile", L"..\\Resources\\texture\\tile1.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			//spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"testTile", spriteMateiral);
		}
#pragma endregion
#pragma region ETC
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"test_amazon", L"..\\Resources\\texture\\amazon_test.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"testAmazon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"800_600_panel_border_left", L"..\\Resources\\texture\\ui\\800_600_panel_border_left.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"panelBorderLeft", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"800_600_panel_border_right", L"..\\Resources\\texture\\ui\\800_600_panel_border_right.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"panelBorderRight", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"t1", L"..\\Resources\\texture\\move_scene_key_info.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"tt1", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"t2", L"..\\Resources\\texture\\inven_key_info.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"tt2", spriteMateiral);
		}
		//move_scene_key_info.png
#pragma endregion
#pragma region Items
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"hp_posion_1", L"..\\Resources\\texture\\items\\posion\\hp_posion_1.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"hpPosion1", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"mp_posion_1", L"..\\Resources\\texture\\items\\posion\\mp_posion_1.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"mpPosion1", spriteMateiral);
		}
#pragma endregion

#pragma region Bottom User Interface
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"bottom_ui", L"..\\Resources\\texture\\ui\\play\\ctrlpanelcenter.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"bottomUi", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"hp_ui", L"..\\Resources\\texture\\ui\\play\\ctrlpanellife.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"hpUi", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"mp_ui", L"..\\Resources\\texture\\ui\\play\\ctrlpanelmana.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"mpUi", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"ex_pocket", L"..\\Resources\\texture\\ui\\play\\ex_pocket.bmp");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"exPocket", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"hp_t", L"..\\Resources\\texture\\ui\\play\\life.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"hp", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"mp_t", L"..\\Resources\\texture\\ui\\play\\mana.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"mp", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"hp_overlap_hands", L"..\\Resources\\texture\\ui\\play\\hp_overlap_hands.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"hpOverlapHands", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"mp_overlap_hands", L"..\\Resources\\texture\\ui\\play\\mp_overlap_hands.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"mpOverlapHands", spriteMateiral);
		}
#pragma endregion
#pragma region Skill User Interface
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"skill_panel_cold", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_pannel_cold.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"skillPanelCold", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"skill_panel_light", L"..\\Resources\\texture\\ui\\skill\\orceress_skill_pannel\\sorceress_skill_pannel_light.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"skillPanelLight", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"skill_panel_fire", L"..\\Resources\\texture\\ui\\skill\\orceress_skill_pannel\\sorceress_skill_pannel_fire.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"skillPanelFire", spriteMateiral);
		}
#pragma endregion
#pragma region Skill icons
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"blaze_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\blaze.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"blazeIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"blaze_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\blaze_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"blazeClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"blizzard_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\blizzard.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"blizzardIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"blizzard_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\blizzard_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"blizzardClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"frozen_orb_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\frozen_orb.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"frozenOrbIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"frozen_orb_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\frozen_orb_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"frozenOrbClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"thunder_storm_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\thunder_storm.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"thunderStormIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"thunder_storm_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\thunder_storm_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"thunderStormClickicon", spriteMateiral);
		}
#pragma endregion
#pragma region Inventory
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"inventory_panel", L"..\\Resources\\texture\\ui\\play\\inventorypanel.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			//spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"inventoryPanel", spriteMateiral);
		}
#pragma endregion
#pragma region Grid
		{
			std::shared_ptr<Material> gridMateiral = std::make_shared<Material>();
			std::shared_ptr<Shader> gridShader
				= Resources::Find<Shader>(L"GridShader");

			gridMateiral->SetShader(gridShader);
			//gridMateiral->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"GridMaterial", gridMateiral);
		}
#pragma endregion

	}

	void Initialize()
	{
		LoadShader();
		SetupState();
		LoadBuffer();
		LoadMesh();
		LoadMaterial();
	}

	void Render()
	{
		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras.clear();
	}

	void Release()
	{
		for (ConstantBuffer* buff : constantBuffers)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}
	}
}



