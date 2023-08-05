#include "mRenderer.h"
#include "mResources.h"
#include "mTexture.h"
#include "mMaterial.h"
#include "ItemLookUpTables.h"
#include "mStructedBuffer.h"
#include "mPaintShader.h"
#include "mParticleShader.h"

namespace renderer
{
	using namespace m;
	using namespace m::graphics;

	m::graphics::ConstantBuffer* constantBuffers[(UINT)eCBType::END] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	std::vector<Light*> lights = {};
	StructedBuffer* lightsBuffer = nullptr;
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

		shader = m::Resources::Find<Shader>(L"AnimationShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = m::Resources::Find<Shader>(L"NoLightShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = m::Resources::Find<Shader>(L"UVControlShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = m::Resources::Find<Shader>(L"ParticleShader");
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

		Vertex v = {};
		v.pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexes.push_back(v);
		indexes.push_back(0);
		std::shared_ptr<Mesh> pointMesh = std::make_shared<Mesh>();
		pointMesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		pointMesh->CreateIndexBuffer(indexes.data(), indexes.size());
		Resources::Insert(L"PointMesh", pointMesh);

		vertexes.clear();
		indexes.clear();

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

		std::shared_ptr<Mesh> UVControlfullMesh = std::make_shared<Mesh>();
		Resources::Insert(L"UVControlRectMesh", UVControlfullMesh);
		UVControlfullMesh->SetVertexes(vertexes);
		UVControlfullMesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		UVControlfullMesh->CreateIndexBuffer(indexes.data(), indexes.size());

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

		int iSlice = 80;
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

		constantBuffers[(UINT)eCBType::Animator] = new ConstantBuffer(eCBType::Animator);
		constantBuffers[(UINT)eCBType::Animator]->Create(sizeof(AnimatorCB));

		constantBuffers[(UINT)eCBType::UVControl] = new ConstantBuffer(eCBType::UVControl);
		constantBuffers[(UINT)eCBType::UVControl]->Create(sizeof(UVControlCB));

		constantBuffers[(UINT)eCBType::Particle] = new ConstantBuffer(eCBType::Particle);
		constantBuffers[(UINT)eCBType::Particle]->Create(sizeof(ParticleCB));

		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 2, eViewType::SRV, nullptr);
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
		gridShader->SetRSState(eRSType::SolidNone);
		m::Resources::Insert(L"GridShader", gridShader);

		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
		debugShader->SetRSState(eRSType::SolidNone);
		//debugShader->SetDSState(eDSType::NoWrite);
		m::Resources::Insert(L"DebugShader", debugShader);

		std::shared_ptr<Shader> animationShader = std::make_shared<Shader>();
		animationShader->Create(eShaderStage::VS, L"AnimationVS.hlsl", "main");
		animationShader->Create(eShaderStage::PS, L"AnimationPS.hlsl", "main");
		m::Resources::Insert(L"AnimationShader", animationShader);

		std::shared_ptr<Shader> noLightShader = std::make_shared<Shader>();
		noLightShader->Create(eShaderStage::VS, L"NoLightSpriteVS.hlsl", "main");
		noLightShader->Create(eShaderStage::PS, L"NoLightSpritePS.hlsl", "main");
		m::Resources::Insert(L"NoLightShader", noLightShader);

		
		std::shared_ptr<Shader> UVControlShader = std::make_shared<Shader>();
		UVControlShader->Create(eShaderStage::VS, L"UVControlVS.hlsl", "main");
		UVControlShader->Create(eShaderStage::PS, L"UVControlPS.hlsl", "main");
		m::Resources::Insert(L"UVControlShader", UVControlShader);

		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		m::Resources::Insert(L"PaintShader", paintShader);

		std::shared_ptr<ParticleShader> psSystemShader = std::make_shared<ParticleShader>();
		psSystemShader->Create(L"ParticleCS.hlsl", "main");
		m::Resources::Insert(L"ParticleSystemShader", psSystemShader);

		std::shared_ptr<Shader> paritcleShader = std::make_shared<Shader>();
		paritcleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		paritcleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		paritcleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		paritcleShader->SetRSState(eRSType::SolidNone);
		paritcleShader->SetDSState(eDSType::None);
		paritcleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);

		m::Resources::Insert(L"ParticleShader", paritcleShader);
	}

	void LoadTexture()
	{
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		m::Resources::Insert(L"PaintTexture", uavTexture);
	}

	void LoadMaterial()
	{
		std::shared_ptr<Shader> spriteShader = m::Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Shader> animShader = m::Resources::Find<Shader>(L"AnimationShader");
		std::shared_ptr<Shader> noLightSahder = m::Resources::Find<Shader>(L"NoLightShader");
		std::shared_ptr<Shader> UVControlShader = m::Resources::Find<Shader>(L"UVControlShader");
		{
			

		}
#pragma region Skill
		MAKE_MATERIAL_PATH(spriteShader, L"fire_bolt", L"..\\Resources\\texture\\skill_effect\\fire_bolt"
						   , 116, 66, 5, L"fireBolt");
#pragma endregion
#pragma region Monster
		MAKE_MATERIAL(spriteShader, L"diablo_natural", L"..\\Resources\\texture\\enemy\\diablo\\diablo_natural.png", L"diabloNatural");
		MAKE_MATERIAL(spriteShader, L"diablo_walk", L"..\\Resources\\texture\\enemy\\diablo\\diablo_walk.png", L"diabloWalk");
		MAKE_MATERIAL(spriteShader, L"diablo_attack1", L"..\\Resources\\texture\\enemy\\diablo\\diablo_attack1.png", L"diabloAttack1");
		MAKE_MATERIAL(spriteShader, L"diablo_attack2", L"..\\Resources\\texture\\enemy\\diablo\\diablo_attack2.png", L"diabloAttack2");
		MAKE_MATERIAL(spriteShader, L"diablo_block", L"..\\Resources\\texture\\enemy\\diablo\\diablo_block.png", L"diabloBlock");
		MAKE_MATERIAL(spriteShader, L"diablo_hit", L"..\\Resources\\texture\\enemy\\diablo\\diablo_hit.png", L"diabloHit");
		MAKE_MATERIAL(spriteShader, L"diablo_run", L"..\\Resources\\texture\\enemy\\diablo\\diablo_run.png", L"diabloRun");
		MAKE_MATERIAL(spriteShader, L"diablo_special_cast", L"..\\Resources\\texture\\enemy\\diablo\\diablo_special_cast.png", L"diabloSpecial_cast");
		MAKE_MATERIAL(spriteShader, L"diablo_special1", L"..\\Resources\\texture\\enemy\\diablo\\diablo_special1.png", L"diabloSpecial1");
		MAKE_MATERIAL(spriteShader, L"diablo_special2", L"..\\Resources\\texture\\enemy\\diablo\\diablo_special2.png", L"diabloSpecial2");
		MAKE_MATERIAL(spriteShader, L"diablo_special3", L"..\\Resources\\texture\\enemy\\diablo\\diablo_special3.png", L"diabloSpecial3");
		MAKE_MATERIAL(spriteShader, L"diablo_special4", L"..\\Resources\\texture\\enemy\\diablo\\diablo_special4.png", L"diabloSpecial4");
		MAKE_MATERIAL(spriteShader, L"diablo_dead", L"..\\Resources\\texture\\enemy\\diablo\\diablo_dead.png", L"diabloDead");
#pragma endregion

#pragma region Characters
		// town
		MAKE_MATERIAL(spriteShader, L"sorceress_town_natural", L"..\\Resources\\texture\\character\\sorceress\\natural.png", L"sorceressTownNatural");
		MAKE_MATERIAL(spriteShader, L"sorceress_town_walk", L"..\\Resources\\texture\\character\\sorceress\\town_walk.png", L"sorceressTownWalk");

		// battle field
		MAKE_MATERIAL(spriteShader, L"sorceress_attack_1", L"..\\Resources\\texture\\character\\sorceress\\attack_1.png", L"sorceressAttack1");
		MAKE_MATERIAL(spriteShader, L"sorceress_attack_2", L"..\\Resources\\texture\\character\\sorceress\\attack_2.png", L"sorceressAttack2");
		MAKE_MATERIAL(spriteShader, L"sorceress_block", L"..\\Resources\\texture\\character\\sorceress\\block.png", L"sorceressBlock");
		MAKE_MATERIAL(spriteShader, L"sorceress_get_hit", L"..\\Resources\\texture\\character\\sorceress\\get_hit.png", L"sorceressGetHit");
		MAKE_MATERIAL(spriteShader, L"sorceress_kick", L"..\\Resources\\texture\\character\\sorceress\\kick.png", L"sorceressKick");
		MAKE_MATERIAL(spriteShader, L"sorceress_natural", L"..\\Resources\\texture\\character\\sorceress\\natural.png", L"sorceressNatural");
		MAKE_MATERIAL(spriteShader, L"sorceress_run", L"..\\Resources\\texture\\character\\sorceress\\run.png", L"sorceressRun");
		MAKE_MATERIAL(spriteShader, L"sorceress_special_1", L"..\\Resources\\texture\\character\\sorceress\\special1.png", L"sorceressSpecial1");
		MAKE_MATERIAL(spriteShader, L"sorceress_special_cast", L"..\\Resources\\texture\\character\\sorceress\\special_cast.png", L"sorceressSpecialCast");
		MAKE_MATERIAL(spriteShader, L"sorceress_walk", L"..\\Resources\\texture\\character\\sorceress\\walk.png", L"sorceressWalk");
		MAKE_MATERIAL(spriteShader, L"sorceress_dead", L"..\\Resources\\texture\\character\\sorceress\\dead.png", L"sorceressDead");
#pragma endregion
#pragma region Background
		MAKE_MATERIAL(noLightSahder, L"main_menu_2", L"..\\Resources\\texture\\ui\\mainMenu\\mainMenu2.png", L"mainMenu2");
		MAKE_MATERIAL(noLightSahder, L"main_menu_2_1", L"..\\Resources\\texture\\ui\\mainMenu\\main_menu_2_1.png", L"mainMenu2_1");
		MAKE_MATERIAL(noLightSahder, L"character_select_1", L"..\\Resources\\texture\\ui\\characterSelect\\charactercreationscreenEXP.png", L"characterSelect1");
		MAKE_MATERIAL(noLightSahder, L"charactercreation_test", L"..\\Resources\\texture\\ui\\characterSelect\\charactercreation_.png", L"charactercreationTest");
		MAKE_MATERIAL(noLightSahder, L"test_logo", L"..\\Resources\\texture\\ui\\mainMenu\\test_logo.png", L"testLogo");
#pragma endregion
#pragma region Buttons
		MAKE_MATERIAL(noLightSahder, L"m_medium_button_blank", L"..\\Resources\\texture\\ui\\buttons\\MediumButtonBlank.png", L"mMediumButtonBlank");
		MAKE_MATERIAL(noLightSahder, L"m_button_blank", L"..\\Resources\\texture\\ui\\buttons\\widebuttonblank.png", L"mWideButtonBlank");
		MAKE_MATERIAL(noLightSahder, L"m_button_blank_02", L"..\\Resources\\texture\\ui\\buttons\\widebuttonblank02.png", L"mWideButtonBlankClick");
		MAKE_MATERIAL(noLightSahder, L"tab_bt", L"..\\Resources\\texture\\ui\\buttons\\tabbt.png", L"tabBt");
		MAKE_MATERIAL(noLightSahder, L"close_btn", L"..\\Resources\\texture\\ui\\buttons\\close_btn.png", L"closeBtn");
		MAKE_MATERIAL(noLightSahder, L"close_btn_click", L"..\\Resources\\texture\\ui\\buttons\\close_btn_c.png", L"closeBtnClick");
#pragma endregion
#pragma region Tiles
		MAKE_MATERIAL(spriteShader, L"town_floors", L"..\\Resources\\texture\\act1_town\\town_floor.png", L"townFloors");
		MAKE_MATERIAL(spriteShader, L"test_tile", L"..\\Resources\\texture\\tile1.png", L"testTile");
		MAKE_MATERIAL(spriteShader, L"test_tile2", L"..\\Resources\\texture\\tile2.png", L"testTile2");
		MAKE_MATERIAL(spriteShader, L"test_tile3", L"..\\Resources\\texture\\tile3.png", L"testTile3");
#pragma endregion
#pragma region ETC
		//MAKE_MATERIAL(noLightSahder, L"test_amazon", L"..\\Resources\\texture\\amazon_test.png", L"testAmazon");
		MAKE_MATERIAL_COMPUT_TEST(spriteShader, L"PaintTexture", L"testAmazon");
		MAKE_MATERIAL(noLightSahder, L"test_sc", L"..\\Resources\\texture\\sc_town_walk.png", L"testSc");
		MAKE_MATERIAL(noLightSahder, L"800_600_panel_border_left", L"..\\Resources\\texture\\ui\\800_600_panel_border_left.png", L"panelBorderLeft");
		MAKE_MATERIAL(noLightSahder, L"800_600_panel_border_right", L"..\\Resources\\texture\\ui\\800_600_panel_border_right.png", L"panelBorderRight");
		MAKE_MATERIAL(noLightSahder, L"t1", L"..\\Resources\\texture\\move_scene_key_info.png", L"tt1");
		MAKE_MATERIAL(noLightSahder, L"t2", L"..\\Resources\\texture\\inven_key_info.png", L"tt2");
		MAKE_MATERIAL(noLightSahder, L"test_debug_rect", L"..\\Resources\\texture\\testDebugRect.png", L"testDebugRect");
		MAKE_MATERIAL(noLightSahder, L"none", L"..\\Resources\\texture\\none.png", L"noneRect");
		MAKE_MATERIAL(noLightSahder, L"inven_rect", L"..\\Resources\\texture\\ui\\play\\inventory_inven.png", L"invenRect");
#pragma endregion
#pragma region Items

		MAKE_MATERIAL(noLightSahder, L"hp_posion_1", L"..\\Resources\\texture\\inventory_items\\posion\\hp_posion_1.png", itemNameTable[(int)eItem::hpPosion1]);
		MAKE_MATERIAL(noLightSahder, L"mp_posion_1", L"..\\Resources\\texture\\inventory_items\\posion\\mp_posion_1.png", itemNameTable[(int)eItem::mpPosion1]);
		MAKE_MATERIAL(noLightSahder, L"jareds_stone", L"..\\Resources\\texture\\inventory_items\\orb\\invo5.png", itemNameTable[(int)eItem::jaredsStone]);
		MAKE_MATERIAL(noLightSahder, L"leader_armor", L"..\\Resources\\texture\\inventory_items\\armor\\leader_armor.png", itemNameTable[(int)eItem::leaderArmor]);
		MAKE_MATERIAL(noLightSahder, L"cap_", L"..\\Resources\\texture\\inventory_items\\armor\\cap.png", itemNameTable[(int)eItem::cap]);
#pragma endregion
#pragma region Bottom User Interface
		MAKE_MATERIAL(noLightSahder, L"bottom_ui", L"..\\Resources\\texture\\ui\\play\\ctrlpanelcenter.png", L"bottomUi");
		MAKE_MATERIAL(noLightSahder, L"hp_ui", L"..\\Resources\\texture\\ui\\play\\ctrlpanellife.png", L"hpUi");
		MAKE_MATERIAL(noLightSahder, L"mp_ui", L"..\\Resources\\texture\\ui\\play\\ctrlpanelmana.png", L"mpUi");
		MAKE_MATERIAL(noLightSahder, L"ex_pocket", L"..\\Resources\\texture\\ui\\play\\ex_pocket.png", L"exPocket");
		MAKE_MATERIAL(UVControlShader, L"hp_t", L"..\\Resources\\texture\\ui\\play\\life.png", L"hp");
		MAKE_MATERIAL(UVControlShader, L"mp_t", L"..\\Resources\\texture\\ui\\play\\mana.png", L"mp");
		MAKE_MATERIAL(noLightSahder, L"hp_overlap_hands", L"..\\Resources\\texture\\ui\\play\\hp_overlap_hands.png", L"hpOverlapHands");
		MAKE_MATERIAL(noLightSahder, L"mp_overlap_hands", L"..\\Resources\\texture\\ui\\play\\mp_overlap_hands.png", L"mpOverlapHands");
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
		MAKE_MATERIAL(noLightSahder, L"chain_lightning_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\chain_lightning.png", L"chainLightningIcon")
		MAKE_MATERIAL(noLightSahder, L"charged_bolt_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\charged_bolt.png", L"chargedBoltIcon")
		MAKE_MATERIAL(noLightSahder, L"energy_shield_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\energy_shield.png", L"energyShieldIcon")
		MAKE_MATERIAL(noLightSahder, L"lightning_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\lightning.png", L"lightningIcon")
		MAKE_MATERIAL(noLightSahder, L"lightning_mastery_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\lightning_mastery.png", L"lightningMasteryIcon")
		MAKE_MATERIAL(noLightSahder, L"nove_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\nove.png", L"noveIcon")
		MAKE_MATERIAL(noLightSahder, L"static_field_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\static_field.png", L"staticFieldIcon")
		MAKE_MATERIAL(noLightSahder, L"telekinesis_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\telekinesis.png", L"telekinesisIcon")
		MAKE_MATERIAL(noLightSahder, L"teleport_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\teleport.png", L"teleportIcon")
		MAKE_MATERIAL(noLightSahder, L"thunder_storm_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\thunder_storm.png", L"thunderStormIcon")
#pragma endregion
#pragma region Skill Click Lightning
		MAKE_MATERIAL(noLightSahder, L"charged_bolt_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\charged_bolt_c.png", L"chargedBoltClickIcon")
		MAKE_MATERIAL(noLightSahder, L"static_field_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\static_field_c.png", L"staticFieldClickIcon")
		MAKE_MATERIAL(noLightSahder, L"telekinesis_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\telekinesis_c.png", L"telekinesisClickIcon")
		MAKE_MATERIAL(noLightSahder, L"nove_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\nove_c.png", L"noveClickIcon")
		MAKE_MATERIAL(noLightSahder, L"lightning_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\lightning_c.png", L"lightningClickIcon")
		MAKE_MATERIAL(noLightSahder, L"chain_lightning_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\chain_lightning_c.png", L"chainLightningClickIcon")
		MAKE_MATERIAL(noLightSahder, L"teleport_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\teleport_c.png", L"teleportClickIcon")
		MAKE_MATERIAL(noLightSahder, L"thunder_storm_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\thunder_storm_c.png", L"thunderStormClickIcon")
		MAKE_MATERIAL(noLightSahder, L"energy_shield_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\energy_shield_c.png", L"energyShieldClickIcon")
		MAKE_MATERIAL(noLightSahder, L"lightning_mastery_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\lightning_mastery_c.png", L"lightningMasteryClickIcon")
		MAKE_MATERIAL(noLightSahder, L"thunder_storm_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\thunder_storm_c.png", L"thunderStormClickIcon")
#pragma endregion
#pragma region Skill ETC
		MAKE_MATERIAL(noLightSahder, L"normal_attack_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\normal_attack.png", L"normalAttackIcon")
		MAKE_MATERIAL(noLightSahder, L"normal_attack_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\normal_attack_c.png", L"normalAttackClickIcon")
#pragma endregion

#pragma region Inventory
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"inventory_panel", L"..\\Resources\\texture\\ui\\play\\inventorypanel.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(noLightSahder);
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
			//material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"DebugMaterial", material);
		}
		{
			spriteShader
				= Resources::Find<Shader>(L"AnimationShader");
			std::shared_ptr<Material> material = std::make_shared<Material>();

			material = std::make_shared<Material>();
			material->SetShader(spriteShader);
			//material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"AnimationMaterial", material);
		}
		{
			std::shared_ptr<Shader> shader
				= Resources::Find<Shader>(L"ParticleShader");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"ParticleMaterial", material);
		}
	}

	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadTexture();
		LoadMaterial();
	}

	void BindLights()
	{
		std::vector<LightAttribute> lightsAttributes = {};
		for (Light* light : lights)
		{
			LightAttribute attribute = light->GetAttribute();
			lightsAttributes.push_back(attribute);
		}

		lightsBuffer->SetData(lightsAttributes.data(), lightsAttributes.size());
		lightsBuffer->BindSRV(eShaderStage::VS, 13);
		lightsBuffer->BindSRV(eShaderStage::PS, 13);
	}

	void Render()
	{
		BindLights();

		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras.clear();
		lights.clear();
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

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}
}



