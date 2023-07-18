#include "mRenderer.h"
#include "mResources.h"
#include "mTexture.h"
#include "mMaterial.h"
#include "ItemLookUpTables.h"

namespace renderer
{
	using namespace m;
	using namespace m::graphics;

	m::graphics::ConstantBuffer* constantBuffers[(UINT)eCBType::END] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	m::Camera* mainCamera = nullptr;
	std::vector<m::Camera*> cameras = {};
	std::vector<DebugMesh> debugMeshs = {};

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
		std::shared_ptr<Shader> shader = m::Resources::Find<Shader>(L"TriangleShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = m::Resources::Find<Shader>(L"SpriteShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = m::Resources::Find<Shader>(L"GridShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = m::Resources::Find<Shader>(L"DebugShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

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
		std::vector<Vertex> vertexes;
		std::vector<UINT> indexes;

		vertexes.resize(4);

		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		std::shared_ptr<Mesh> fullMesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", fullMesh);
		fullMesh->SetVertexes(vertexes);
		fullMesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		fullMesh->CreateIndexBuffer(indexes.data(), indexes.size());

		indexes.clear();
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);

		std::shared_ptr<Mesh> rectDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugRect", rectDebug);
		rectDebug->SetVertexes(vertexes);
		rectDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		rectDebug->CreateIndexBuffer(indexes.data(), indexes.size());

		for (int i = 0; i < vertexes.size(); ++i)
			vertexes[i].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		rectDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugRedRect", rectDebug);
		rectDebug->SetVertexes(vertexes);
		rectDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		rectDebug->CreateIndexBuffer(indexes.data(), indexes.size());

		// Circle Debug Mesh
		vertexes.clear();
		indexes.clear();

		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.f);
			vertexes.push_back(center);
		}

		for (int i = 0; i < vertexes.size() - 2; ++i)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		std::shared_ptr<Mesh> circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugCircle", circleDebug);
		circleDebug->SetVertexes(vertexes);
		circleDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		circleDebug->CreateIndexBuffer(indexes.data(), indexes.size());

		for (int i = 0; i < vertexes.size(); ++i)
			vertexes[i].color = Vector4(1.f, 0.f, 0.f, 1.f);

		circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugRedCircle", circleDebug);
		circleDebug->SetVertexes(vertexes);
		circleDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		circleDebug->CreateIndexBuffer(indexes.data(), indexes.size());
	}

	void PushDebugMeshAttribute(DebugMesh& mesh)
	{
		debugMeshs.push_back(mesh);
	}

	void LoadBuffer()
	{
		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		constantBuffers[(UINT)eCBType::Vertex] = new ConstantBuffer(eCBType::Vertex);
		constantBuffers[(UINT)eCBType::Vertex]->Create(sizeof(Vertex));

		constantBuffers[(UINT)eCBType::Animator] = new ConstantBuffer(eCBType::Animator);
		constantBuffers[(UINT)eCBType::Animator]->Create(sizeof(AnimatorCB));

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

		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
		debugShader->SetRSState(eRSType::SolidNone);
		//debugShader->SetDSState(eDSType::NoWrite);
		m::Resources::Insert(L"DebugShader", debugShader);
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
		MAKE_MATERIAL(spriteShader, L"main_menu_2", L"..\\Resources\\texture\\ui\\mainMenu\\mainMenu2.png", L"mainMenu2");
		MAKE_MATERIAL(spriteShader, L"main_menu_2_1", L"..\\Resources\\texture\\ui\\mainMenu\\main_menu_2_1.png", L"mainMenu2_1");
		MAKE_MATERIAL(spriteShader, L"character_select_1", L"..\\Resources\\texture\\ui\\characterSelect\\charactercreationscreenEXP.png", L"characterSelect1");
		MAKE_MATERIAL(spriteShader, L"charactercreation_test", L"..\\Resources\\texture\\ui\\characterSelect\\charactercreation_.png", L"charactercreationTest");
		MAKE_MATERIAL(spriteShader, L"test_logo", L"..\\Resources\\texture\\ui\\mainMenu\\test_logo.png", L"testLogo");
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
		MAKE_MATERIAL(spriteShader, L"town_floors", L"..\\Resources\\texture\\act1_town\\town_floor.png", L"townFloors");
		MAKE_MATERIAL(spriteShader, L"test_tile", L"..\\Resources\\texture\\tile1.png", L"testTile");
#pragma endregion
#pragma region ETC
		MAKE_MATERIAL(spriteShader, L"test_amazon", L"..\\Resources\\texture\\amazon_test.png", L"testAmazon");
		MAKE_MATERIAL(spriteShader, L"800_600_panel_border_left", L"..\\Resources\\texture\\ui\\800_600_panel_border_left.png", L"panelBorderLeft");
		MAKE_MATERIAL(spriteShader, L"800_600_panel_border_right", L"..\\Resources\\texture\\ui\\800_600_panel_border_right.png", L"panelBorderRight");
		MAKE_MATERIAL(spriteShader, L"t1", L"..\\Resources\\texture\\move_scene_key_info.png", L"tt1");
		MAKE_MATERIAL(spriteShader, L"t2", L"..\\Resources\\texture\\inven_key_info.png", L"tt2");
		MAKE_MATERIAL(spriteShader, L"test_debug_rect", L"..\\Resources\\texture\\testDebugRect.png", L"testDebugRect");
		MAKE_MATERIAL(spriteShader, L"none", L"..\\Resources\\texture\\none.png", L"noneRect");
		//move_scene_key_info.png
#pragma endregion
#pragma region Items
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"hp_posion_1", L"..\\Resources\\texture\\inventory_items\\posion\\hp_posion_1.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(itemNameTable[(int)eItem::hpPosion1], spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"mp_posion_1", L"..\\Resources\\texture\\inventory_items\\posion\\mp_posion_1.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(itemNameTable[(int)eItem::mpPosion1], spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"jareds_stone", L"..\\Resources\\texture\\inventory_items\\orb\\invo5.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(itemNameTable[(int)eItem::jaredsStone], spriteMateiral);
		}
#pragma endregion
#pragma region Bottom User Interface
		MAKE_MATERIAL(spriteShader, L"bottom_ui", L"..\\Resources\\texture\\ui\\play\\ctrlpanelcenter.png", L"bottomUi");
		MAKE_MATERIAL(spriteShader, L"hp_ui", L"..\\Resources\\texture\\ui\\play\\ctrlpanellife.png", L"hpUi");
		MAKE_MATERIAL(spriteShader, L"mp_ui", L"..\\Resources\\texture\\ui\\play\\ctrlpanelmana.png", L"mpUi");
		MAKE_MATERIAL(spriteShader, L"ex_pocket", L"..\\Resources\\texture\\ui\\play\\ex_pocket.png", L"exPocket");
		MAKE_MATERIAL(spriteShader, L"hp_t", L"..\\Resources\\texture\\ui\\play\\life.png", L"hp");
		MAKE_MATERIAL(spriteShader, L"mp_t", L"..\\Resources\\texture\\ui\\play\\mana.png", L"mp");
		MAKE_MATERIAL(spriteShader, L"hp_overlap_hands", L"..\\Resources\\texture\\ui\\play\\hp_overlap_hands.png", L"hpOverlapHands");
		MAKE_MATERIAL(spriteShader, L"mp_overlap_hands", L"..\\Resources\\texture\\ui\\play\\mp_overlap_hands.png", L"mpOverlapHands");
#pragma endregion
#pragma region Skill User Interface
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"skill_panel_cold", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_pannel\\sorceress_skill_pannel_cold.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"skillPanelCold", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"skill_panel_light", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_pannel\\sorceress_skill_pannel_light.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"skillPanelLight", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"skill_panel_fire", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_pannel\\sorceress_skill_pannel_fire.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"skillPanelFire", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"skill_deactive_btn", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_pannel\\skill_deactive_btn.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"skillDeactiveBtn", spriteMateiral);
		}
#pragma endregion
#pragma region Skill Cold
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"blizzard_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\blizzard.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"blizzardIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"chilling_armor_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\chilling_armor.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"chillingArmorIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"clacial_spike_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\clacial_spike.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"clacialSpikeIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"cold_mastery_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\cold_mastery.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"coldMasteryIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"frost_nova_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\frost_nova.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"frostNovaIcon", spriteMateiral);
		}

		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"frozen_armor_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\frozen_armor.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"frozenArmorIcon", spriteMateiral);
		}

		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"frozen_orb_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\frozen_orb.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"frozenOrbIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"ice_blast_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\ice_blast.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"iceBlastIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"ice_bolt_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\ice_bolt.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"iceBoltIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"shiver_armor_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\shiver_armor.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"shiverArmorIcon", spriteMateiral);
		}
#pragma endregion
#pragma region Skill Click Cold

		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"blizzard_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\blizzard_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"blizzardClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"chilling_armor_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\chilling_armor_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"chillingArmorClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"clacial_spike_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\clacial_spike_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"clacialSpikeClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"cold_mastery_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\cold_mastery_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"coldMasteryClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"frost_nova_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\frost_nova_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"frostNovaClickIcon", spriteMateiral);
		}

		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"frozen_armor_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\frozen_armor_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"frozenArmorClickIcon", spriteMateiral);
		}

		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"frozen_orb_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\frozen_orb_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"frozenOrbClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"ice_blast_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\ice_blast_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"iceBlastClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"ice_bolt_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\ice_bolt_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"iceBoltClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"shiver_armor_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\shiver_armor_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"shiverArmorClickIcon", spriteMateiral);
		}
#pragma endregion
#pragma region Skill Fire
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"blaze_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\blaze.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"blazeIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"enchant_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\enchant.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"enchantIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"fire_ball_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_ball.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"fireBallIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"fire_bolt_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_bolt.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"fireBoltIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"fire_mastery_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_mastery.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"fireMasteryIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"fire_wall_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_wall.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"fireWallIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"hydra_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\hydra.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"hydraIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"inferno_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\inferno.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"infernoIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"meteor_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\meteor.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"meteorIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"warmth_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\warmth.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"warmthIcon", spriteMateiral);
		}
#pragma endregion
#pragma region Skill Click Fire
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"blaze_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\blaze_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"blazeClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"enchant_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\enchant_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"enchantClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"fire_ball_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_ball_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"fireBallClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"fire_bolt_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_bolt_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"fireBoltClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"fire_mastery_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_mastery_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"fireMasteryClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"fire_wall_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_wall_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"fireWallClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"hydra_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\hydra_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"hydraClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"inferno_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\inferno_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"infernoClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"meteor_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\meteor_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"meteorClickIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"warmth_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\warmth_c.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"warmthClickIcon", spriteMateiral);
		}
#pragma endregion
#pragma region Skill Lightning
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"chain_lightning_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\chain_lightning.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"chainLightningIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"charged_bolt_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\charged_bolt.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"chargedBoltIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"energy_shield_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\energy_shield.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"energyShieldIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"lightning_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\lightning.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"lightningIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"lightning_mastery_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\lightning_mastery.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"lightningMasteryIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"nove_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\nove.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"noveIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"static_field_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\static_field.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"staticFieldIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"telekinesis_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\telekinesis.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"telekinesisIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"teleport_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\teleport.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"teleportIcon", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"thunder_storm_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\thunder_storm.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"thunderStormIcon", spriteMateiral);
		}
#pragma endregion
#pragma region Skill Click Lightning
		MAKE_MATERIAL(spriteShader, L"charged_bolt_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\charged_bolt_c.png", L"chargedBoltClickIcon")
		MAKE_MATERIAL(spriteShader, L"static_field_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\static_field_c.png", L"staticFieldClickIcon")
		MAKE_MATERIAL(spriteShader, L"telekinesis_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\telekinesis_c.png", L"telekinesisClickIcon")
		MAKE_MATERIAL(spriteShader, L"nove_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\nove_c.png", L"noveClickIcon")
		MAKE_MATERIAL(spriteShader, L"lightning_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\lightning_c.png", L"lightningClickIcon")
		MAKE_MATERIAL(spriteShader, L"chain_lightning_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\chain_lightning_c.png", L"chainLightningClickIcon")
		MAKE_MATERIAL(spriteShader, L"teleport_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\teleport_c.png", L"teleportClickIcon")
		MAKE_MATERIAL(spriteShader, L"thunder_storm_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\thunder_storm_c.png", L"thunderStormClickIcon")
		MAKE_MATERIAL(spriteShader, L"energy_shield_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\energy_shield_c.png", L"energyShieldClickIcon")
		MAKE_MATERIAL(spriteShader, L"lightning_mastery_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\lightning_mastery_c.png", L"lightningMasteryClickIcon")
		MAKE_MATERIAL(spriteShader, L"thunder_storm_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\thunder_storm_c.png", L"thunderStormClickIcon")
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
		{
			std::shared_ptr<Shader> debugShader
				= Resources::Find<Shader>(L"DebugShader");
			std::shared_ptr<Material> material = std::make_shared<Material>();

			material = std::make_shared<Material>();
			material->SetShader(debugShader);
			Resources::Insert(L"DebugMaterial", material);
		}
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



