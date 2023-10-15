#include "mRenderer.h"
#include "mResources.h"
#include "mTexture.h"
#include "mMaterial.h"
#include "ItemLookUpTables.h"
#include "mStructedBuffer.h"
#include "mPaintShader.h"
#include "mParticleComputeShader.h"
#include "mPathFinder.h"
#include "mTileComputeShader.h"
#include "mPathFinderComputeShader.h"
#include "mTileDrawComputeShader.h"

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
	StructuredBuffer* lightsBuffer = nullptr;
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

		shader = m::Resources::Find<Shader>(L"FadeShader");
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

		shader = m::Resources::Find<Shader>(L"NoLightAnimationShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());
		
		shader = m::Resources::Find<Shader>(L"ShadowAnimationShader");
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

		shader = m::Resources::Find<Shader>(L"TileShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = m::Resources::Find<Shader>(L"WallShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = m::Resources::Find<Shader>(L"TileDrawShader");
		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = m::Resources::Find<Shader>(L"ShadowSpriteShader");
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

		//samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		//GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		//GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
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
		//D3D11_DEPTH_STENCIL_DESC depthStencilDesc2 = {};
		//depthStencilDesc2.DepthEnable = true;
		//depthStencilDesc2.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		//depthStencilDesc2.DepthFunc = D3D11_COMPARISON_LESS;
		//depthStencilDesc2.StencilEnable = true;
		//depthStencilDesc2.StencilReadMask = 0xff;
		//depthStencilDesc2.StencilWriteMask = 0xff;

		//depthStencilDesc2.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		//depthStencilDesc2.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		//depthStencilDesc2.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
		//depthStencilDesc2.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;

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
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
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

		vertexes.clear();
		indexes.clear();

		vertexes.resize(4);

		vertexes[0].pos = Vector3(-1.0f, 0.0f, 0.0f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.0f, 0.0f, 0.0f);
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
		std::shared_ptr<Mesh> parallelogram = std::make_shared<Mesh>();
		parallelogram->SetVertexes(vertexes);
		parallelogram->CreateVertexBuffer(vertexes.data(), vertexes.size());
		parallelogram->CreateIndexBuffer(indexes.data(), indexes.size());

		Resources::Insert(L"PMesh", parallelogram);


		vertexes.clear();
		indexes.clear();

		vertexes.resize(4);


		vertexes[0].pos = Vector3(-0.5f, 1.0f, 0.0f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 1.0f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, 0.0f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, 0.0f, 0.0f);
		vertexes[3].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		std::shared_ptr<Mesh> bottomPosMash = std::make_shared<Mesh>();
		bottomPosMash->SetVertexes(vertexes);
		bottomPosMash->CreateVertexBuffer(vertexes.data(), vertexes.size());
		bottomPosMash->CreateIndexBuffer(indexes.data(), indexes.size());

		Resources::Insert(L"BMesh", bottomPosMash);

		vertexes.clear();
		indexes.clear();

		vertexes.resize(4);

		vertexes[0].pos = Vector3(-2.0f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(-1.0f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, 0.0f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, 0.0f, 0.0f);
		vertexes[3].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		std::shared_ptr<Mesh> bottomParaPosMash = std::make_shared<Mesh>();
		bottomParaPosMash->SetVertexes(vertexes);
		bottomParaPosMash->CreateVertexBuffer(vertexes.data(), vertexes.size());
		bottomParaPosMash->CreateIndexBuffer(indexes.data(), indexes.size());

		Resources::Insert(L"BPMesh", bottomParaPosMash);
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

		constantBuffers[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
		constantBuffers[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));

		constantBuffers[(UINT)eCBType::Particle] = new ConstantBuffer(eCBType::Particle);
		constantBuffers[(UINT)eCBType::Particle]->Create(sizeof(ParticleSystemCB));

		//constantBuffers[(UINT)eCBType::Tile] = new ConstantBuffer(eCBType::Tile);
		//constantBuffers[(UINT)eCBType::Tile]->Create(sizeof(TileDataCB));

		lightsBuffer = new StructuredBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 2, eViewType::SRV, nullptr, true);
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

		std::shared_ptr<Shader> shadowSpriteShader = std::make_shared<Shader>();
		shadowSpriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		shadowSpriteShader->Create(eShaderStage::PS, L"ShadowPS.hlsl", "main");
		m::Resources::Insert(L"ShadowSpriteShader", shadowSpriteShader);

		std::shared_ptr<Shader> fadeShader = std::make_shared<Shader>();
		fadeShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		fadeShader->Create(eShaderStage::PS, L"FadePS.hlsl", "main");
		m::Resources::Insert(L"FadeShader", fadeShader);

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

		std::shared_ptr<Shader> noLighAnimationShader = std::make_shared<Shader>();
		noLighAnimationShader->Create(eShaderStage::VS, L"AnimationVS.hlsl", "main");
		noLighAnimationShader->Create(eShaderStage::PS, L"NoLightAnimationPS.hlsl", "main");
		m::Resources::Insert(L"NoLightAnimationShader", noLighAnimationShader);

		std::shared_ptr<Shader> animationShader = std::make_shared<Shader>();
		animationShader->Create(eShaderStage::VS, L"AnimationVS.hlsl", "main");
		animationShader->Create(eShaderStage::PS, L"AnimationPS.hlsl", "main");
		m::Resources::Insert(L"AnimationShader", animationShader);

		std::shared_ptr<Shader> shadowAnimationShader = std::make_shared<Shader>();
		shadowAnimationShader->Create(eShaderStage::VS, L"ShadowAnimationVS.hlsl", "main");
		shadowAnimationShader->Create(eShaderStage::PS, L"ShadowAnimationPS.hlsl", "main");
		m::Resources::Insert(L"ShadowAnimationShader", shadowAnimationShader);


		std::shared_ptr<Shader> noLightShader = std::make_shared<Shader>();
		noLightShader->Create(eShaderStage::VS, L"NoLightSpriteVS.hlsl", "main");
		//noLightShader->Create(eShaderStage::GS, L"DrawGS.hlsl", "main");
		noLightShader->Create(eShaderStage::PS, L"NoLightSpritePS.hlsl", "main");
		m::Resources::Insert(L"NoLightShader", noLightShader);


		std::shared_ptr<Shader> UVControlShader = std::make_shared<Shader>();
		UVControlShader->Create(eShaderStage::VS, L"UVControlVS.hlsl", "main");
		UVControlShader->Create(eShaderStage::PS, L"UVControlPS.hlsl", "main");
		m::Resources::Insert(L"UVControlShader", UVControlShader);

		std::shared_ptr<Shader> wallShader = std::make_shared<Shader>();
		wallShader->Create(eShaderStage::VS, L"WallVS.hlsl", "main");
		wallShader->Create(eShaderStage::PS, L"WallPS.hlsl", "main");
		m::Resources::Insert(L"WallShader", wallShader);

		std::shared_ptr<ParticleComputeShader> psSystemShader = std::make_shared<ParticleComputeShader>();
		psSystemShader->Create(L"ParticleCS.hlsl", "main");
		m::Resources::Insert(L"ParticleComputeShader", psSystemShader);

		std::shared_ptr<TileComputeShader> tileSystemShader = std::make_shared<TileComputeShader>();
		tileSystemShader->Create(L"TileCS.hlsl", "main");
		m::Resources::Insert(L"TileComputeShader", tileSystemShader);


		std::shared_ptr<TileDrawComputeShader> tileDrawSystemShader = std::make_shared<TileDrawComputeShader>();
		tileDrawSystemShader->Create(L"TileDrawCS.hlsl", "main");
		m::Resources::Insert(L"TileDrawComputeShader", tileDrawSystemShader);

		std::shared_ptr<Shader> tileShader = std::make_shared<Shader>();
		tileShader->UseGS();
		tileShader->Create(eShaderStage::VS, L"TileVS.hlsl", "main");
		tileShader->Create(eShaderStage::GS, L"TileGS.hlsl", "main");
		tileShader->Create(eShaderStage::PS, L"TilePS.hlsl", "main");
		tileShader->SetRSState(eRSType::SolidNone);
		tileShader->SetDSState(eDSType::None);
		tileShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);

		m::Resources::Insert(L"TileShader", tileShader);

		std::shared_ptr<Shader> tileDrawShader = std::make_shared<Shader>();
		tileDrawShader->UseGS();
		tileDrawShader->Create(eShaderStage::VS, L"TileDrawVS.hlsl", "main");
		tileDrawShader->Create(eShaderStage::GS, L"TileDrawGS.hlsl", "main");
		tileDrawShader->Create(eShaderStage::PS, L"TileDrawPS.hlsl", "main");
		tileDrawShader->SetRSState(eRSType::SolidNone);
		tileDrawShader->SetDSState(eDSType::None);
		tileDrawShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);

		m::Resources::Insert(L"TileDrawShader", tileDrawShader);
	}

	void LoadTexture()
	{
	}

	void LoadMaterial()
	{
		std::shared_ptr<Shader> spriteShader = m::Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Shader> fadeShader = m::Resources::Find<Shader>(L"FadeShader");
		std::shared_ptr<Shader> noLightShader = m::Resources::Find<Shader>(L"NoLightShader");
		std::shared_ptr<Shader> UVControlShader = m::Resources::Find<Shader>(L"UVControlShader");
		std::shared_ptr<Shader> tileShader = m::Resources::Find<Shader>(L"TileShader");
		std::shared_ptr<Shader> tileDrawShader = m::Resources::Find<Shader>(L"TileDrawShader");
		std::shared_ptr<Shader> wallShader = m::Resources::Find<Shader>(L"WallShader");
#pragma region PlayerBodyParts
		MAKE_MATERIAL_PATH(spriteShader, L"hd_gh", L"..\\Resources\\texture\\character\\sorceress\\get_hit\\hd_gh"
			, 44, 34, 8, L"hdGH");
		MAKE_MATERIAL_PATH(spriteShader, L"cp_hd_gh", L"..\\Resources\\texture\\character\\sorceress\\get_hit\\cp_hd_gh"
			, 43, 35, 8, L"cpHdGH");
		MAKE_MATERIAL_PATH(spriteShader, L"lg_gh", L"..\\Resources\\texture\\character\\sorceress\\get_hit\\lg_gh"
			, 38, 50, 8, L"lgGH");
		MAKE_MATERIAL_PATH(spriteShader, L"la_gh", L"..\\Resources\\texture\\character\\sorceress\\get_hit\\la_gh"
			, 34, 35, 8, L"laGH");
		MAKE_MATERIAL_PATH(spriteShader, L"ra_gh", L"..\\Resources\\texture\\character\\sorceress\\get_hit\\ra_gh"
			, 34, 35, 8, L"raGH");
		MAKE_MATERIAL_PATH(spriteShader, L"ob_ra_gh", L"..\\Resources\\texture\\character\\sorceress\\get_hit\\ob_ra_gh"
			, 48, 36, 8, L"obRaGH");
		MAKE_MATERIAL_PATH(spriteShader, L"ob_gh", L"..\\Resources\\texture\\character\\sorceress\\get_hit\\ob_gh"
			, 60, 39, 8, L"obGH");
		MAKE_MATERIAL_PATH(spriteShader, L"tr_gh", L"..\\Resources\\texture\\character\\sorceress\\get_hit\\tr_gh"
			, 24, 26, 8, L"trGH");

		MAKE_MATERIAL_PATH(spriteShader, L"hd_nu", L"..\\Resources\\texture\\character\\sorceress\\natural\\hd_nu"
			, 35, 30, 8, L"hdNU");
		MAKE_MATERIAL_PATH(spriteShader, L"cp_hd_nu", L"..\\Resources\\texture\\character\\sorceress\\natural\\cp_hd_nu"
			, 35, 30, 8, L"cpHdNU");
		MAKE_MATERIAL_PATH(spriteShader, L"lg_nu", L"..\\Resources\\texture\\character\\sorceress\\natural\\lg_nu"
			, 30, 50, 8, L"lgNU");
		MAKE_MATERIAL_PATH(spriteShader, L"la_nu", L"..\\Resources\\texture\\character\\sorceress\\natural\\la_nu"
			, 30, 32, 8, L"laNU");
		MAKE_MATERIAL_PATH(spriteShader, L"ra_nu", L"..\\Resources\\texture\\character\\sorceress\\natural\\ra_nu"
			, 30, 34, 8, L"raNU");
		MAKE_MATERIAL_PATH(spriteShader, L"tr_nu", L"..\\Resources\\texture\\character\\sorceress\\natural\\tr_nu"
			, 16, 24, 8, L"trNU");
		MAKE_MATERIAL_PATH(spriteShader, L"ob_ra_nu", L"..\\Resources\\texture\\character\\sorceress\\natural\\ob_ra_nu"
			, 48, 35, 8, L"obRaNU");
		MAKE_MATERIAL_PATH(spriteShader, L"ob_nu", L"..\\Resources\\texture\\character\\sorceress\\natural\\ob_nu"
			, 60, 38, 8, L"obNU");

		MAKE_MATERIAL_PATH(spriteShader, L"hd_r", L"..\\Resources\\texture\\character\\sorceress\\run\\hd_r"
			, 32, 30, 8, L"hdR");
		MAKE_MATERIAL_PATH(spriteShader, L"cp_hd_r", L"..\\Resources\\texture\\character\\sorceress\\run\\cp_hd_r"
			, 30, 31, 8, L"cpHdR");
		MAKE_MATERIAL_PATH(spriteShader, L"lg_r", L"..\\Resources\\texture\\character\\sorceress\\run\\lg_r"
			, 61, 52, 8, L"lgR");
		MAKE_MATERIAL_PATH(spriteShader, L"la_r", L"..\\Resources\\texture\\character\\sorceress\\run\\la_r"
			, 54, 35, 8, L"laR");
		MAKE_MATERIAL_PATH(spriteShader, L"ra_r", L"..\\Resources\\texture\\character\\sorceress\\run\\ra_r"
			, 50, 33, 8, L"raR");
		MAKE_MATERIAL_PATH(spriteShader, L"tr_r", L"..\\Resources\\texture\\character\\sorceress\\run\\tr_r"
			, 20, 28, 8, L"trR");
		MAKE_MATERIAL_PATH(spriteShader, L"ob_ra_r", L"..\\Resources\\texture\\character\\sorceress\\run\\ob_ra_r"
			, 42, 33, 8, L"obRaR");
		MAKE_MATERIAL_PATH(spriteShader, L"ob_r", L"..\\Resources\\texture\\character\\sorceress\\run\\ob_r"
			, 46, 40, 8, L"obR");

		MAKE_MATERIAL_PATH(spriteShader, L"hd_sc", L"..\\Resources\\texture\\character\\sorceress\\special_cast\\hd_sc"
			, 43, 35, 14, L"hdSC");
		MAKE_MATERIAL_PATH(spriteShader, L"cp_hd_sc", L"..\\Resources\\texture\\character\\sorceress\\special_cast\\cp_hd_sc"
			, 42, 36, 14, L"cpHdSC");
		MAKE_MATERIAL_PATH(spriteShader, L"lg_sc", L"..\\Resources\\texture\\character\\sorceress\\special_cast\\lg_sc"
			, 30, 51, 14, L"lgSC");
		MAKE_MATERIAL_PATH(spriteShader, L"la_sc", L"..\\Resources\\texture\\character\\sorceress\\special_cast\\la_sc"
			, 85, 62, 14, L"laSC");
		MAKE_MATERIAL_PATH(spriteShader, L"ra_sc", L"..\\Resources\\texture\\character\\sorceress\\special_cast\\ra_sc"
			, 84, 64, 14, L"raSC");
		MAKE_MATERIAL_PATH(spriteShader, L"tr_sc", L"..\\Resources\\texture\\character\\sorceress\\special_cast\\tr_sc"
			, 30, 29, 14, L"trSC");
		MAKE_MATERIAL_PATH(spriteShader, L"ob_sc", L"..\\Resources\\texture\\character\\sorceress\\special_cast\\ob_sc"
			, 92, 66, 14, L"obSC");
#pragma endregion
#pragma region FieldItem
		MAKE_MATERIAL_PATH(spriteShader, L"hp_potion_anim", L"..\\Resources\\texture\\field_items\\hp_potion_anim"
			, 20, 159, 17, L"hpPotionAnim");

		MAKE_MATERIAL_PATH(spriteShader, L"mp_potion_anim", L"..\\Resources\\texture\\field_items\\mp_potion_anim"
			, 20, 159, 17, L"mpPotionAnim");

		MAKE_MATERIAL_PATH(spriteShader, L"bots_anim", L"..\\Resources\\texture\\field_items\\bots_anim"
			, 28, 181, 17, L"botsAnim");

		MAKE_MATERIAL_PATH(spriteShader, L"cap_anim", L"..\\Resources\\texture\\field_items\\cap_anim"
			, 21, 149, 17, L"capAnim");

		MAKE_MATERIAL_PATH(spriteShader, L"leader_armor_anim", L"..\\Resources\\texture\\field_items\\leader_armor_anim"
			, 38, 173, 17, L"leaderArmorAnim");

		MAKE_MATERIAL_PATH(spriteShader, L"jareds_stone_anim", L"..\\Resources\\texture\\field_items\\jareds_stone_anim"
			, 37, 153, 18, L"jaredsStoneAnim");

		MAKE_MATERIAL(spriteShader, L"hp_potion_field", L"..\\Resources\\texture\\field_items\\hp_potion_field.png", L"hpPotionField");
		MAKE_MATERIAL(spriteShader, L"mp_potion_field", L"..\\Resources\\texture\\field_items\\mp_potion_field.png", L"mpPotionField");

		MAKE_MATERIAL(spriteShader, L"leader_armor_field", L"..\\Resources\\texture\\field_items\\leader_armor_field.png", L"leaderArmorField");
		MAKE_MATERIAL(spriteShader, L"bots_field", L"..\\Resources\\texture\\field_items\\bots_field.png", L"botsField");
		MAKE_MATERIAL(spriteShader, L"cap_field", L"..\\Resources\\texture\\field_items\\cap_field.png", L"capField");
		MAKE_MATERIAL(spriteShader, L"jareds_stone_field", L"..\\Resources\\texture\\field_items\\jareds_stone_field.png", L"jaredsStoneField");
#pragma endregion
#pragma region Map
		MAKE_MATERIAL(spriteShader, L"stage_4", L"..\\Resources\\texture\\map\\stage4\\stage4.png", L"stage4");
		MAKE_MATERIAL(spriteShader, L"stage_3", L"..\\Resources\\texture\\map\\stage3\\stage3.png", L"stage3");
		MAKE_MATERIAL(spriteShader, L"stage_2", L"..\\Resources\\texture\\map\\stage2\\stage2.png", L"stage2");
		MAKE_MATERIAL(spriteShader, L"stage_1", L"..\\Resources\\texture\\map\\stage1\\stage1.png", L"stage1");
		MAKE_MATERIAL(spriteShader, L"stage_0", L"..\\Resources\\texture\\map\\stage0\\stage0.png", L"stage0");

		MAKE_MATERIAL_T(wallShader, L"s1_wall_1", L"..\\Resources\\texture\\map\\stage1\\wall_1.png", L"s1Wall1");
		MAKE_MATERIAL_T(wallShader, L"s1_wall_2", L"..\\Resources\\texture\\map\\stage1\\wall_2.png", L"s1Wall2");
		MAKE_MATERIAL_T(wallShader, L"s1_wall_3", L"..\\Resources\\texture\\map\\stage1\\wall_3.png", L"s1Wall3");

		MAKE_MATERIAL_T(wallShader, L"s1_chair_1", L"..\\Resources\\texture\\map\\stage1\\chair_1.png", L"s1Chair1");

		MAKE_MATERIAL_T(wallShader, L"s1_door", L"..\\Resources\\texture\\map\\stage1\\door.png", L"s1Door");
		MAKE_MATERIAL_T(wallShader, L"s1_flag", L"..\\Resources\\texture\\map\\stage1\\flag.png", L"s1Flag");

		MAKE_MATERIAL_PATH(spriteShader, L"st1_torch", L"..\\Resources\\texture\\map\\stage1\\torch"
			, 32, 113, 20, L"st1Torch");

		MAKE_MATERIAL_T(wallShader, L"s2_wall_1", L"..\\Resources\\texture\\map\\stage2\\wall_1.png", L"s2Wall1");

		MAKE_MATERIAL_T(wallShader, L"s4_wall_1", L"..\\Resources\\texture\\map\\stage4\\wall_1.png", L"s4Wall1");
		MAKE_MATERIAL_T(wallShader, L"s4_wall_2", L"..\\Resources\\texture\\map\\stage4\\wall_2.png", L"s4Wall2");

		MAKE_MATERIAL(spriteShader, L"lava_1", L"..\\Resources\\texture\\map\\stage4\\lava\\lava_1.png", L"lava1");
		MAKE_MATERIAL(spriteShader, L"lava_2", L"..\\Resources\\texture\\map\\stage4\\lava\\lava_2.png", L"lava2");
		MAKE_MATERIAL(spriteShader, L"lava_3", L"..\\Resources\\texture\\map\\stage4\\lava\\lava_3.png", L"lava3");
		MAKE_MATERIAL(spriteShader, L"lava_4", L"..\\Resources\\texture\\map\\stage4\\lava\\lava_4.png", L"lava4");
		MAKE_MATERIAL(spriteShader, L"lava_5", L"..\\Resources\\texture\\map\\stage4\\lava\\lava_5.png", L"lava5");
		MAKE_MATERIAL(spriteShader, L"lava_6", L"..\\Resources\\texture\\map\\stage4\\lava\\lava_6.png", L"lava6");
		MAKE_MATERIAL(spriteShader, L"lava_7", L"..\\Resources\\texture\\map\\stage4\\lava\\lava_7.png", L"lava7");
		MAKE_MATERIAL(spriteShader, L"lava_8", L"..\\Resources\\texture\\map\\stage4\\lava\\lava_8.png", L"lava8");
		MAKE_MATERIAL(spriteShader, L"lava_9", L"..\\Resources\\texture\\map\\stage4\\lava\\lava_9.png", L"lava9");
		MAKE_MATERIAL(spriteShader, L"lava_10", L"..\\Resources\\texture\\map\\stage4\\lava\\lava_10.png", L"lava10");
#pragma endregion

#pragma region Particle
		
#pragma endregion
#pragma region Objects
		MAKE_MATERIAL_PATH(spriteShader, L"portal_start", L"..\\Resources\\texture\\objects\\portal_start"
			, 204, 204, 15, L"portalStart");
		MAKE_MATERIAL_PATH(spriteShader, L"portal_loop", L"..\\Resources\\texture\\objects\\portal_loop"
			, 115, 154, 15, L"portalLoop");


		MAKE_MATERIAL(fadeShader, L"_black", L"..\\Resources\\texture\\ui\\play\\black.png", L"black");

#pragma endregion
#pragma region Monster SKill
		MAKE_MATERIAL_PATH(spriteShader, L"diablo_lightning", L"..\\Resources\\texture\\skill_effect\\monster\\missile\\diablo_lightning"
			, 252, 190, 15, L"diabloLightning");

		MAKE_MATERIAL_PATH(spriteShader, L"diablo_fire_nova", L"..\\Resources\\texture\\skill_effect\\monster\\missile\\diablo_fire_nova"
			, 66, 167, 8, L"diabloFireNova");

		MAKE_MATERIAL_PATH(spriteShader, L"andariel_poison_attack", L"..\\Resources\\texture\\skill_effect\\monster\\missile\\andariel_poison_attack"
			, 65, 65, 24, L"andarielPoisonAttack");

		MAKE_MATERIAL_PATH(spriteShader, L"mephisto_missile", L"..\\Resources\\texture\\skill_effect\\monster\\missile\\mephisto_missile"
			, 83, 85, 10, L"mephistoMissile");
#pragma endregion

#pragma region Monster Overlay
		MAKE_MATERIAL_PATH(spriteShader, L"red_lightning_crash", L"..\\Resources\\texture\\skill_effect\\monster\\overlay\\red_lightning_crash"
			, 71, 88, 20, L"redLightningCrash");

		MAKE_MATERIAL_PATH(spriteShader, L"mephisto_missile_crash", L"..\\Resources\\texture\\skill_effect\\monster\\overlay\\mephisto_missile_crash"
			, 86, 77, 12, L"mephistoMissileCrash");

		MAKE_MATERIAL_PATH(spriteShader, L"andariel_flame_death", L"..\\Resources\\texture\\skill_effect\\monster\\overlay\\andariel_flame_death"
			, 38, 122, 15, L"andarielFlameDeath");

		MAKE_MATERIAL(spriteShader, L"mephisto_overlay", L"..\\Resources\\texture\\skill_effect\\monster\\overlay\\mephisto_overlay.png", L"mephistoOverlay");

#pragma endregion
#pragma region Overlay
		MAKE_MATERIAL_PATH(spriteShader, L"holy_freeze", L"..\\Resources\\texture\\skill_effect\\overlay\\holy_freeze"
			, 114, 93, 15, L"holyFreeze");

		MAKE_MATERIAL_PATH(spriteShader, L"ice_cast_3", L"..\\Resources\\texture\\skill_effect\\overlay\\ice_cast_3"
			, 127, 148, 16, L"iceCast3");
		MAKE_MATERIAL_PATH(spriteShader, L"ice_cast_2", L"..\\Resources\\texture\\skill_effect\\overlay\\ice_cast_2"
			, 115, 123, 15, L"iceCast2");
		MAKE_MATERIAL_PATH(spriteShader, L"ice_cast_1", L"..\\Resources\\texture\\skill_effect\\overlay\\ice_cast_1"
			, 97, 55, 15, L"iceCast1");

		MAKE_MATERIAL_PATH(spriteShader, L"light_cast_1", L"..\\Resources\\texture\\skill_effect\\overlay\\light_cast_1"
			, 164, 144, 10, L"lightCast1");

		MAKE_MATERIAL_PATH(spriteShader, L"light_cast_2_front", L"..\\Resources\\texture\\skill_effect\\overlay\\light_cast_2_front"
			, 147, 190, 10, L"lightCast2Front");

		MAKE_MATERIAL_PATH(spriteShader, L"light_cast_2_back", L"..\\Resources\\texture\\skill_effect\\overlay\\light_cast_2_back"
			, 101, 105, 10, L"lightCast2Back");

		MAKE_MATERIAL_PATH(spriteShader, L"fire_cast_1", L"..\\Resources\\texture\\skill_effect\\overlay\\fire_cast_1"
			, 145, 133, 16, L"fireCast1");

		MAKE_MATERIAL_PATH(spriteShader, L"ice_crash_1", L"..\\Resources\\texture\\skill_effect\\overlay\\ice_crash_1"
			, 113, 72, 6, L"iceCrash1");
		MAKE_MATERIAL_PATH(spriteShader, L"ice_crash_2", L"..\\Resources\\texture\\skill_effect\\overlay\\ice_crash_2"
			, 83, 110, 16, L"iceCrash2");
		MAKE_MATERIAL_PATH(spriteShader, L"ice_crash_3", L"..\\Resources\\texture\\skill_effect\\overlay\\ice_crash_3"
			, 143, 107, 15, L"iceCrash3");
		MAKE_MATERIAL_PATH(spriteShader, L"freeze_smoke", L"..\\Resources\\texture\\skill_effect\\overlay\\freeze_smoke"
			, 300, 175, 15, L"freezeSmoke");

		MAKE_MATERIAL_PATH(spriteShader, L"fire_crash_1", L"..\\Resources\\texture\\skill_effect\\overlay\\fire_crash_1"
			, 78, 70, 12, L"fireCrash1");

		MAKE_MATERIAL_PATH(spriteShader, L"fire_crash_2", L"..\\Resources\\texture\\skill_effect\\overlay\\fire_crash_2"
			, 208, 174, 16, L"fireCrash2");

		MAKE_MATERIAL_PATH(spriteShader, L"light_crash_1", L"..\\Resources\\texture\\skill_effect\\overlay\\light_crash_1"
			, 65, 71, 20, L"lightCrash1");



		MAKE_MATERIAL_PATH(spriteShader, L"fire_1", L"..\\Resources\\texture\\skill_effect\\overlay\\fire1"
			, 66, 89, 37, L"fire1");

		MAKE_MATERIAL_PATH(spriteShader, L"fire_2", L"..\\Resources\\texture\\skill_effect\\overlay\\fire2"
			, 66, 167, 37, L"fire2");

		MAKE_MATERIAL_PATH(spriteShader, L"fire_3", L"..\\Resources\\texture\\skill_effect\\overlay\\fire3"
			, 66, 136, 37, L"fire3");

		MAKE_MATERIAL_PATH(spriteShader, L"meteor_target_indicator", L"..\\Resources\\texture\\skill_effect\\overlay\\meteor_target_indicator"
			, 112, 74, 17, L"meteorTargetIndicator");

		MAKE_MATERIAL_PATH(spriteShader, L"_teleport", L"..\\Resources\\texture\\skill_effect\\overlay\\teleport"
			, 136, 154, 18, L"teleport");

		MAKE_MATERIAL_PATH(spriteShader, L"_stun", L"..\\Resources\\texture\\skill_effect\\overlay\\stun"
			, 69, 49, 12, L"stun");

		MAKE_MATERIAL_PATH(spriteShader, L"thunder_storm_cast", L"..\\Resources\\texture\\skill_effect\\overlay\\thunder_storm_cast"
			, 79, 52, 10, L"thunderStormCast");

		MAKE_MATERIAL_PATH(spriteShader, L"thunder_storm_loop", L"..\\Resources\\texture\\skill_effect\\overlay\\thunder_storm_loop"
			, 81, 60, 19, L"thunderStormLoop");

#pragma endregion
#pragma region Summons
		MAKE_MATERIAL_PATH(spriteShader, L"hydra_attack", L"..\\Resources\\texture\\skill_effect\\summons\\hydra\\attack"
			, 104, 67, 12, L"hydraAttack");
		MAKE_MATERIAL_PATH(spriteShader, L"hydra_summon", L"..\\Resources\\texture\\skill_effect\\summons\\hydra\\summon"
			, 84, 84, 12, L"hydraSummon");
		MAKE_MATERIAL_PATH(spriteShader, L"hydra_dead", L"..\\Resources\\texture\\skill_effect\\summons\\hydra\\dead"
			, 88, 80, 10, L"hydraDead");
		MAKE_MATERIAL_PATH(spriteShader, L"hydra_natural", L"..\\Resources\\texture\\skill_effect\\summons\\hydra\\natural"
			, 85, 66, 12, L"hydraNatural");

		MAKE_MATERIAL_PATH(spriteShader, L"hydra_attack_fire", L"..\\Resources\\texture\\skill_effect\\summons\\hydra\\attack_fire"
			, 124, 82, 12, L"hydraAttackFire");
		MAKE_MATERIAL_PATH(spriteShader, L"hydra_summon_fire", L"..\\Resources\\texture\\skill_effect\\summons\\hydra\\summon_fire"
			, 80, 87, 12, L"hydraSummonFire");
		MAKE_MATERIAL_PATH(spriteShader, L"hydra_dead_fire", L"..\\Resources\\texture\\skill_effect\\summons\\hydra\\dead_fire"
			, 81, 88, 10, L"hydraDeadFire");
		MAKE_MATERIAL_PATH(spriteShader, L"hydra_natural_fire", L"..\\Resources\\texture\\skill_effect\\summons\\hydra\\natural_fire"
			, 83, 78, 12, L"hydraNaturalFire");

		MAKE_MATERIAL_PATH(spriteShader, L"hydra_overlay_fire_start", L"..\\Resources\\texture\\skill_effect\\overlay\\hydra_fire\\start"
			, 114, 99, 16, L"hydraOverlayFireStart");
		MAKE_MATERIAL_PATH(spriteShader, L"hydra_overlay_fire_end", L"..\\Resources\\texture\\skill_effect\\overlay\\hydra_fire\\end"
			, 60, 81, 16, L"hydraOverlayFireEnd");
		MAKE_MATERIAL_PATH(spriteShader, L"hydra_overlay_fire_loop", L"..\\Resources\\texture\\skill_effect\\overlay\\hydra_fire\\loop"
			, 63, 90, 20, L"hydraOverlayFireLoop");
#pragma endregion
#pragma region Skill
		MAKE_MATERIAL_PATH(spriteShader, L"ice_bolt", L"..\\Resources\\texture\\skill_effect\\missile\\ice_bolt"
			, 92, 55, 6, L"iceBolt");

		MAKE_MATERIAL_PATH(spriteShader, L"blizzard_1", L"..\\Resources\\texture\\skill_effect\\missile\\blizzard\\blizzard1"
			, 97, 153, 8, L"blizzard1");
		MAKE_MATERIAL_PATH(spriteShader, L"blizzard_3", L"..\\Resources\\texture\\skill_effect\\missile\\blizzard\\blizzard3"
			, 59, 198, 6, L"blizzard3");

		MAKE_MATERIAL_PATH(spriteShader, L"fire_bolt", L"..\\Resources\\texture\\skill_effect\\missile\\fire_bolt"
			, 116, 66, 5, L"fireBolt");
		MAKE_MATERIAL_PATH(spriteShader, L"fire_ball", L"..\\Resources\\texture\\skill_effect\\missile\\fire_ball"
			, 146, 79, 5, L"fireBall");

		MAKE_MATERIAL_PATH(spriteShader, L"frozen_orb", L"..\\Resources\\texture\\skill_effect\\missile\\frozen_orb"
			, 54, 53, 16, L"frozenOrb");

		MAKE_MATERIAL_PATH(spriteShader, L"meteor_head", L"..\\Resources\\texture\\skill_effect\\missile\\meteor_head"
			, 22, 22, 12, L"meteorHead");

		MAKE_MATERIAL_PATH(spriteShader, L"meteor_tail", L"..\\Resources\\texture\\skill_effect\\missile\\meteor_tail"
			, 77, 125, 12, L"meteor");

		MAKE_MATERIAL_PATH(spriteShader, L"frost_nova", L"..\\Resources\\texture\\skill_effect\\missile\\frost_nova"
			, 118, 69, 14, L"frostNova");


		MAKE_MATERIAL_PATH(spriteShader, L"_nova", L"..\\Resources\\texture\\skill_effect\\missile\\nova"
			, 70, 48, 13, L"nova");

		MAKE_MATERIAL_PATH(spriteShader, L"fire_wall", L"..\\Resources\\texture\\skill_effect\\missile\\fire_wall"
			, 66, 167, 37, L"fireWall");

		MAKE_MATERIAL_PATH(spriteShader, L"_blaze", L"..\\Resources\\texture\\skill_effect\\missile\\fire_wall"
			, 66, 167, 37, L"blaze");

		MAKE_MATERIAL_PATH(spriteShader, L"_lightning", L"..\\Resources\\texture\\skill_effect\\missile\\lightning"
			, 148, 106, 8, L"lightning");

		MAKE_MATERIAL_PATH(spriteShader, L"_lightning", L"..\\Resources\\texture\\skill_effect\\missile\\lightning"
			, 148, 106, 8, L"chainLightning");

		MAKE_MATERIAL_PATH(spriteShader, L"thunder_storm", L"..\\Resources\\texture\\skill_effect\\missile\\thunder_storm"
			, 36, 113, 8, L"thunderStorm");

		MAKE_MATERIAL_PATH(spriteShader, L"ice_blast", L"..\\Resources\\texture\\skill_effect\\missile\\ice_blast"
			, 169, 94, 5, L"iceBlast");

		MAKE_MATERIAL_PATH(spriteShader, L"clacial_spike", L"..\\Resources\\texture\\skill_effect\\missile\\clacial_spike"
			, 180, 110, 6, L"clacialSpike");

		MAKE_MATERIAL_PATH(spriteShader, L"charged_bolt", L"..\\Resources\\texture\\skill_effect\\missile\\charged_bolt"
			, 85, 78, 10, L"chargedBolt");

		MAKE_MATERIAL_PATH(spriteShader, L"flame_1", L"..\\Resources\\texture\\skill_effect\\missile\\flame_1"
			, 76, 77, 15, L"flame1");

		MAKE_MATERIAL_PATH(spriteShader, L"flame_2", L"..\\Resources\\texture\\skill_effect\\missile\\flame_2"
			, 76, 84, 15, L"flame2");

#pragma endregion
#pragma region Monster
		MAKE_MATERIAL_PATH(spriteShader, L"balrog_natural_body", L"..\\Resources\\texture\\enemy\\balrog\\body\\natural"
			, 191, 148, 8, L"balrogNatural");
		MAKE_MATERIAL_PATH(spriteShader, L"balrog_hit_body", L"..\\Resources\\texture\\enemy\\balrog\\body\\hit"
			, 197, 145, 6, L"balrogHit");
		MAKE_MATERIAL_PATH(spriteShader, L"balrog_run_body", L"..\\Resources\\texture\\enemy\\balrog\\body\\run"
			, 171, 153, 8, L"balrogRun");
		MAKE_MATERIAL_PATH(spriteShader, L"balrog_attack1_body", L"..\\Resources\\texture\\enemy\\balrog\\body\\attack"
			, 222, 157, 16, L"balrogAttack");
		MAKE_MATERIAL_PATH(spriteShader, L"balrog_to_dead_body", L"..\\Resources\\texture\\enemy\\balrog\\body\\to_dead"
			, 210, 179, 20, L"balrogToDead");
		MAKE_MATERIAL_PATH(spriteShader, L"balrog_dead_body", L"..\\Resources\\texture\\enemy\\balrog\\body\\dead"
			, 207, 109, 1, L"balrogDead");
		MAKE_MATERIAL_PATH(spriteShader, L"balrog_natural_rh", L"..\\Resources\\texture\\enemy\\balrog\\rh\\natural"
			, 161, 74, 8, L"balrogNaturalRH");
		MAKE_MATERIAL_PATH(spriteShader, L"balrog_hit_rh", L"..\\Resources\\texture\\enemy\\balrog\\rh\\hit"
			, 157, 80, 6, L"balrogHitRH");
		MAKE_MATERIAL_PATH(spriteShader, L"balrog_run_rh", L"..\\Resources\\texture\\enemy\\balrog\\rh\\run"
			, 152, 76, 8, L"balrogRunRH");
		MAKE_MATERIAL_PATH(spriteShader, L"balrog_attack1_rh", L"..\\Resources\\texture\\enemy\\balrog\\rh\\attack"
			, 207, 165, 16, L"balrogAttackRH");

		MAKE_MATERIAL_PATH(spriteShader, L"andariel_natural", L"..\\Resources\\texture\\enemy\\andariel\\natural"
			, 178, 179, 16, L"andarielNatural");
		MAKE_MATERIAL_PATH(spriteShader, L"andariel_attack", L"..\\Resources\\texture\\enemy\\andariel\\attack"
			, 247, 248, 16, L"andarielAttack");
		MAKE_MATERIAL(spriteShader, L"andariel_special", L"..\\Resources\\texture\\enemy\\andariel\\andariel_special_cast.png", L"andarielSpecial");
		MAKE_MATERIAL_PATH(spriteShader, L"andariel_walk", L"..\\Resources\\texture\\enemy\\andariel\\walk"
			, 148, 184, 12, L"andarielWalk");
		MAKE_MATERIAL_PATH(spriteShader, L"andariel_hit", L"..\\Resources\\texture\\enemy\\andariel\\hit"
			, 173, 180, 6, L"andarielHit");
		MAKE_MATERIAL(spriteShader, L"andariel_to_dead", L"..\\Resources\\texture\\enemy\\andariel\\andariel_to_dead.png", L"andarielToDead");

		MAKE_MATERIAL_PATH(spriteShader, L"andariel_dead", L"..\\Resources\\texture\\enemy\\andariel\\dead"
			, 177, 116, 1, L"andarielDead");

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

		MAKE_MATERIAL(spriteShader, L"diablo_to_dead_1", L"..\\Resources\\texture\\enemy\\diablo\\diablo_to_dead_1.png", L"diabloToDead1");
		MAKE_MATERIAL(spriteShader, L"diablo_to_dead_2", L"..\\Resources\\texture\\enemy\\diablo\\diablo_to_dead_2.png", L"diabloToDead2");
		MAKE_MATERIAL(spriteShader, L"diablo_to_dead_3", L"..\\Resources\\texture\\enemy\\diablo\\diablo_to_dead_3.png", L"diabloToDead3");

		MAKE_MATERIAL(spriteShader, L"duriel_natural", L"..\\Resources\\texture\\enemy\\duriel\\duriel_natural.png", L"durielNatural");
		MAKE_MATERIAL(spriteShader, L"duriel_attack1", L"..\\Resources\\texture\\enemy\\duriel\\duriel_attack1.png", L"durielAttack1");
		MAKE_MATERIAL(spriteShader, L"duriel_attack2", L"..\\Resources\\texture\\enemy\\duriel\\duriel_attack2.png", L"durielAttack2");
		MAKE_MATERIAL(spriteShader, L"duriel_dead", L"..\\Resources\\texture\\enemy\\duriel\\duriel_dead.png", L"durielDead");
		MAKE_MATERIAL(spriteShader, L"duriel_get_hit", L"..\\Resources\\texture\\enemy\\duriel\\duriel_get_hit.png", L"durielHit");
		MAKE_MATERIAL(spriteShader, L"duriel_to_dead", L"..\\Resources\\texture\\enemy\\duriel\\duriel_to_dead.png", L"durielToDead");
		MAKE_MATERIAL(spriteShader, L"duriel_walk", L"..\\Resources\\texture\\enemy\\duriel\\duriel_walk.png", L"durielWalk");

		MAKE_MATERIAL(spriteShader, L"mephisto_natural", L"..\\Resources\\texture\\enemy\\mephisto\\mephisto_natural.png", L"mephistoNatural");
		MAKE_MATERIAL(spriteShader, L"mephisto_attack1", L"..\\Resources\\texture\\enemy\\mephisto\\mephisto_attack1.png", L"mephistoAttack1");
		MAKE_MATERIAL(spriteShader, L"mephisto_attack2", L"..\\Resources\\texture\\enemy\\mephisto\\mephisto_attack2.png", L"mephistoAttack2");
		MAKE_MATERIAL(spriteShader, L"mephisto_attack2_1", L"..\\Resources\\texture\\enemy\\mephisto\\mephisto_attack2_1.png", L"mephistoAttack21");
		MAKE_MATERIAL(spriteShader, L"mephisto_dead", L"..\\Resources\\texture\\enemy\\mephisto\\mephisto_dead.png", L"mephistoDead");
		MAKE_MATERIAL(spriteShader, L"mephisto_get_hit", L"..\\Resources\\texture\\enemy\\mephisto\\mephisto_get_hit.png", L"mephistoGetHit");
		MAKE_MATERIAL(spriteShader, L"mephisto_to_dead", L"..\\Resources\\texture\\enemy\\mephisto\\mephisto_to_dead.png", L"mephistoToDead");
		MAKE_MATERIAL(spriteShader, L"mephisto_walk", L"..\\Resources\\texture\\enemy\\mephisto\\mephisto_walk.png", L"mephistoWalk");
#pragma endregion

#pragma region Characters
		MAKE_MATERIAL(spriteShader, L"sorceress_town_natural", L"..\\Resources\\texture\\character\\sorceress\\natural.png", L"sorceressTownNatural");
		MAKE_MATERIAL(spriteShader, L"sorceress_town_walk", L"..\\Resources\\texture\\character\\sorceress\\town_walk.png", L"sorceressTownWalk");

		MAKE_MATERIAL_T(spriteShader, L"sorceress_attack_1", L"..\\Resources\\texture\\character\\sorceress\\attack_1.png", L"sorceressAttack1");
		MAKE_MATERIAL_T(spriteShader, L"sorceress_attack_2", L"..\\Resources\\texture\\character\\sorceress\\attack_2.png", L"sorceressAttack2");
		MAKE_MATERIAL_T(spriteShader, L"sorceress_block", L"..\\Resources\\texture\\character\\sorceress\\block.png", L"sorceressBlock");
		MAKE_MATERIAL_T(spriteShader, L"sorceress_get_hit", L"..\\Resources\\texture\\character\\sorceress\\get_hit.png", L"sorceressGetHit");
		MAKE_MATERIAL_T(spriteShader, L"sorceress_kick", L"..\\Resources\\texture\\character\\sorceress\\kick.png", L"sorceressKick");
		MAKE_MATERIAL_T(spriteShader, L"sorceress_natural", L"..\\Resources\\texture\\character\\sorceress\\natural.png", L"sorceressNatural");
		MAKE_MATERIAL_T(spriteShader, L"sorceress_run", L"..\\Resources\\texture\\character\\sorceress\\run.png", L"sorceressRun");
		MAKE_MATERIAL_T(spriteShader, L"sorceress_special_1", L"..\\Resources\\texture\\character\\sorceress\\special1.png", L"sorceressSpecial1");
		MAKE_MATERIAL_T(spriteShader, L"sorceress_special_cast", L"..\\Resources\\texture\\character\\sorceress\\special_cast.png", L"sorceressSpecialCast");
		MAKE_MATERIAL_T(spriteShader, L"sorceress_walk", L"..\\Resources\\texture\\character\\sorceress\\walk.png", L"sorceressWalk");
		MAKE_MATERIAL_T(spriteShader, L"sorceress_dead", L"..\\Resources\\texture\\character\\sorceress\\dead.png", L"sorceressDead");
#pragma endregion
#pragma region Background
		MAKE_MATERIAL(noLightShader, L"main_menu_2", L"..\\Resources\\texture\\ui\\mainMenu\\mainMenu2.png", L"mainMenu2");
		MAKE_MATERIAL(noLightShader, L"main_menu_2_1", L"..\\Resources\\texture\\ui\\mainMenu\\main_menu_2_1.png", L"mainMenu2_1");
		MAKE_MATERIAL(noLightShader, L"character_select_1", L"..\\Resources\\texture\\ui\\characterSelect\\charactercreationscreenEXP.png", L"characterSelect1");
		MAKE_MATERIAL(noLightShader, L"charactercreation_test", L"..\\Resources\\texture\\ui\\characterSelect\\charactercreation_.png", L"charactercreationTest");
		MAKE_MATERIAL(noLightShader, L"test_logo", L"..\\Resources\\texture\\ui\\mainMenu\\test_logo.png", L"testLogo");
		MAKE_MATERIAL(noLightShader, L"logo_s", L"..\\Resources\\texture\\ui\\mainMenu\\logos.png", L"logos");
#pragma endregion
#pragma region Buttons
		MAKE_MATERIAL(noLightShader, L"m_medium_button_blank", L"..\\Resources\\texture\\ui\\buttons\\MediumButtonBlank.png", L"mMediumButtonBlank");
		MAKE_MATERIAL(noLightShader, L"m_button_blank", L"..\\Resources\\texture\\ui\\buttons\\widebuttonblank.png", L"mWideButtonBlank");
		MAKE_MATERIAL(noLightShader, L"m_button_blank_02", L"..\\Resources\\texture\\ui\\buttons\\widebuttonblank02.png", L"mWideButtonBlankClick");
		MAKE_MATERIAL(noLightShader, L"tab_bt", L"..\\Resources\\texture\\ui\\buttons\\tabbt.png", L"tabBt");
		MAKE_MATERIAL(noLightShader, L"close_btn", L"..\\Resources\\texture\\ui\\buttons\\close_btn.png", L"closeBtn");
		MAKE_MATERIAL(noLightShader, L"close_btn_click", L"..\\Resources\\texture\\ui\\buttons\\close_btn_c.png", L"closeBtnClick");
		MAKE_MATERIAL(noLightShader, L"level_btn", L"..\\Resources\\texture\\ui\\buttons\\level_btn.png", L"levelBtn");
		MAKE_MATERIAL(noLightShader, L"level_btn_c", L"..\\Resources\\texture\\ui\\buttons\\level_btn_c.png", L"levelBtnClick");
		MAKE_MATERIAL(noLightShader, L"level_btn_d", L"..\\Resources\\texture\\ui\\buttons\\level_btn_d.png", L"levelBtnDisable");
		MAKE_MATERIAL(noLightShader, L"btn_0", L"..\\Resources\\texture\\ui\\buttons\\btn_0.png", L"btn0");
		MAKE_MATERIAL(noLightShader, L"btn_0_c", L"..\\Resources\\texture\\ui\\buttons\\btn_0_c.png", L"btn0Click");
		MAKE_MATERIAL(noLightShader, L"btn_1", L"..\\Resources\\texture\\ui\\buttons\\btn_1.png", L"btn1");
		MAKE_MATERIAL(noLightShader, L"btn_1_c", L"..\\Resources\\texture\\ui\\buttons\\btn_1_c.png", L"btn1Click");
		MAKE_MATERIAL(noLightShader, L"btn_2", L"..\\Resources\\texture\\ui\\buttons\\btn_2.png", L"btn2");
		MAKE_MATERIAL(noLightShader, L"btn_2_c", L"..\\Resources\\texture\\ui\\buttons\\btn_2_c.png", L"btn2Click");
		MAKE_MATERIAL(noLightShader, L"btn_3_d", L"..\\Resources\\texture\\ui\\buttons\\btn_3_d.png", L"btn3Disable");
		MAKE_MATERIAL(noLightShader, L"btn_3", L"..\\Resources\\texture\\ui\\buttons\\btn_3.png", L"btn3");
		MAKE_MATERIAL(noLightShader, L"btn_3_c", L"..\\Resources\\texture\\ui\\buttons\\btn_3_c.png", L"btn3Click");

#pragma endregion
#pragma region Tiles
		MAKE_MATERIAL(tileShader, L"tile_", L"..\\Resources\\texture\\tile.png", L"tile");
		MAKE_MATERIAL(tileShader, L"green_tile", L"..\\Resources\\texture\\green_tile.png", L"greenTile");
		MAKE_MATERIAL(tileShader, L"green_outline_tile", L"..\\Resources\\texture\\green_outline_tile.png", L"greenOutlineTile");
		MAKE_MATERIAL(tileShader, L"red_tile", L"..\\Resources\\texture\\red_tile.png", L"redTile");

		MAKE_MATERIAL(tileShader, L"tile_d", L"..\\Resources\\texture\\tile_d.png", L"tileD");
		MAKE_MATERIAL(tileShader, L"green_tile_d", L"..\\Resources\\texture\\green_tile_d.png", L"greenTileD");
		MAKE_MATERIAL(tileDrawShader, L"green_tile_d", L"..\\Resources\\texture\\green_tile_d.png", L"greenTileD" + tileDrawShader->GetKey());
		MAKE_MATERIAL(tileShader, L"green_outline_tile_d", L"..\\Resources\\texture\\green_outline_tile_d.png", L"greenOutlineTileD");
		MAKE_MATERIAL(noLightShader, L"red_tile_d", L"..\\Resources\\texture\\red_tile_d.png", L"redTileD");

#pragma endregion
#pragma region ETC
		MAKE_MATERIAL(noLightShader, L"800_600_panel_border_left", L"..\\Resources\\texture\\ui\\800_600_panel_border_left.png", L"panelBorderLeft");
		MAKE_MATERIAL(noLightShader, L"800_600_panel_border_right", L"..\\Resources\\texture\\ui\\800_600_panel_border_right.png", L"panelBorderRight");
		MAKE_MATERIAL(noLightShader, L"test_debug_rect", L"..\\Resources\\texture\\testDebugRect.png", L"testDebugRect");

		MAKE_MATERIAL(noLightShader, L"inven_rect", L"..\\Resources\\texture\\ui\\play\\inventory_inven.png", L"invenRect");
		MAKE_MATERIAL_T(noLightShader, L"none", L"..\\Resources\\texture\\none.png", L"noneRect");

		MAKE_MATERIAL(noLightShader, L"none", L"..\\Resources\\texture\\none.png", L"noneRect" + noLightShader->GetKey());
		MAKE_MATERIAL(tileShader, L"none", L"..\\Resources\\texture\\none.png", L"noneRect" + tileShader->GetKey());
		MAKE_MATERIAL(spriteShader, L"none", L"..\\Resources\\texture\\none.png", L"noneRect" + spriteShader->GetKey());
		MAKE_MATERIAL(UVControlShader, L"none", L"..\\Resources\\texture\\none.png", L"noneRect" + UVControlShader->GetKey());
		MAKE_MATERIAL(tileDrawShader, L"none", L"..\\Resources\\texture\\none.png", L"noneRect" + tileDrawShader->GetKey());

#pragma endregion
#pragma region InGame User Interface
		MAKE_MATERIAL(UVControlShader, L"enemy_hp", L"..\\Resources\\texture\\ui\\play\\enemy_hp.png", L"enemyHp");
		MAKE_MATERIAL_T(noLightShader, L"talk_UI", L"..\\Resources\\texture\\ui\\play\\talk_ui.png", L"talkUI");
		MAKE_MATERIAL_T(noLightShader, L"item_ex_back", L"..\\Resources\\texture\\ui\\play\\item_ex_back.png", L"itemExBack");
#pragma endregion
#pragma region Items
		MAKE_MATERIAL(noLightShader, L"hp_potion_1", L"..\\Resources\\texture\\inventory_items\\potion\\hp_potion_1.png", itemNameTable[(int)eItem::hpPotion1]);
		MAKE_MATERIAL(noLightShader, L"mp_potion_1", L"..\\Resources\\texture\\inventory_items\\potion\\mp_potion_1.png", itemNameTable[(int)eItem::mpPotion1]);
		MAKE_MATERIAL(noLightShader, L"jareds_stone", L"..\\Resources\\texture\\inventory_items\\orb\\invo5.png", itemNameTable[(int)eItem::jaredsStone]);
		MAKE_MATERIAL(noLightShader, L"leader_armor", L"..\\Resources\\texture\\inventory_items\\armor\\leader_armor.png", itemNameTable[(int)eItem::leaderArmor]);
		MAKE_MATERIAL(noLightShader, L"cap_", L"..\\Resources\\texture\\inventory_items\\armor\\cap.png", itemNameTable[(int)eItem::cap]);
#pragma endregion
#pragma region Bottom User Interface
		MAKE_MATERIAL(noLightShader, L"bottom_ui", L"..\\Resources\\texture\\ui\\play\\ctrlpanelcenter.png", L"bottomUi");
		MAKE_MATERIAL(noLightShader, L"hp_ui", L"..\\Resources\\texture\\ui\\play\\ctrlpanellife.png", L"hpUi");
		MAKE_MATERIAL(noLightShader, L"mp_ui", L"..\\Resources\\texture\\ui\\play\\ctrlpanelmana.png", L"mpUi");
		MAKE_MATERIAL(noLightShader, L"ex_pocket", L"..\\Resources\\texture\\ui\\play\\ex_pocket.png", L"exPocket");
		MAKE_MATERIAL(UVControlShader, L"hp_t", L"..\\Resources\\texture\\ui\\play\\life.png", L"hp");
		MAKE_MATERIAL(UVControlShader, L"addiction_hp_t", L"..\\Resources\\texture\\ui\\play\\addiction_life.png", L"addictionHp");
		MAKE_MATERIAL(UVControlShader, L"mp_t", L"..\\Resources\\texture\\ui\\play\\mana.png", L"mp");
		MAKE_MATERIAL(noLightShader, L"hp_overlap_hands", L"..\\Resources\\texture\\ui\\play\\hp_overlap_hands.png", L"hpOverlapHands");
		MAKE_MATERIAL(noLightShader, L"mp_overlap_hands", L"..\\Resources\\texture\\ui\\play\\mp_overlap_hands.png", L"mpOverlapHands");
#pragma endregion
#pragma region Skill User Interface
		MAKE_MATERIAL(noLightShader, L"skill_panel_cold", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_pannel\\sorceress_skill_pannel_cold.png", L"skillPanelCold");
		MAKE_MATERIAL(noLightShader, L"skill_panel_light", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_pannel\\sorceress_skill_pannel_light.png", L"skillPanelLight");
		MAKE_MATERIAL(noLightShader, L"skill_panel_fire", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_pannel\\sorceress_skill_pannel_fire.png", L"skillPanelFire");
		MAKE_MATERIAL(noLightShader, L"skill_de_active_btn", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_pannel\\skill_de_active_btn.png", L"skillDeActiveBtn");
#pragma endregion
#pragma region Skill Cold
		MAKE_MATERIAL(noLightShader, L"blizzard_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\blizzard.png", L"blizzardIcon");
		MAKE_MATERIAL(noLightShader, L"chilling_armor_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\chilling_armor.png", L"chillingArmorIcon");
		MAKE_MATERIAL(noLightShader, L"clacial_spike_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\clacial_spike.png", L"clacialSpikeIcon");
		MAKE_MATERIAL(noLightShader, L"cold_mastery_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\cold_mastery.png", L"coldMasteryIcon");
		MAKE_MATERIAL(noLightShader, L"frost_nova_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\frost_nova.png", L"frostNovaIcon");
		MAKE_MATERIAL(noLightShader, L"frozen_armor_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\frozen_armor.png", L"frozenArmorIcon");
		MAKE_MATERIAL(noLightShader, L"frozen_orb_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\frozen_orb.png", L"frozenOrbIcon");
		MAKE_MATERIAL(noLightShader, L"ice_blast_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\ice_blast.png", L"iceBlastIcon");
		MAKE_MATERIAL(noLightShader, L"ice_bolt_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\ice_bolt.png", L"iceBoltIcon");
		MAKE_MATERIAL(noLightShader, L"shiver_armor_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\shiver_armor.png", L"shiverArmorIcon");
#pragma endregion
#pragma region Skill Click Cold
		MAKE_MATERIAL(noLightShader, L"blizzard_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\blizzard_c.png", L"blizzardClickIcon");
		MAKE_MATERIAL(noLightShader, L"chilling_armor_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\chilling_armor_c.png", L"chillingArmorClickIcon");
		MAKE_MATERIAL(noLightShader, L"clacial_spike_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\clacial_spike_c.png", L"clacialSpikeClickIcon");
		MAKE_MATERIAL(noLightShader, L"cold_mastery_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\cold_mastery_c.png", L"coldMasteryClickIcon");
		MAKE_MATERIAL(noLightShader, L"frost_nova_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\frost_nova_c.png", L"frostNovaClickIcon");
		MAKE_MATERIAL(noLightShader, L"frozen_armor_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\frozen_armor_c.png", L"frozenArmorClickIcon");
		MAKE_MATERIAL(noLightShader, L"frozen_orb_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\frozen_orb_c.png", L"frozenOrbClickIcon");
		MAKE_MATERIAL(noLightShader, L"ice_blast_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\ice_blast_c.png", L"iceBlastClickIcon");
		MAKE_MATERIAL(noLightShader, L"ice_bolt_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\ice_bolt_c.png", L"iceBoltClickIcon");
		MAKE_MATERIAL(noLightShader, L"shiver_armor_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\cold\\shiver_armor_c.png", L"shiverArmorClickIcon");
#pragma endregion
#pragma region Skill Fire
		MAKE_MATERIAL(noLightShader, L"blaze_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\blaze.png", L"blazeIcon");
		MAKE_MATERIAL(noLightShader, L"enchant_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\enchant.png", L"enchantIcon");
		MAKE_MATERIAL(noLightShader, L"fire_ball_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_ball.png", L"fireBallIcon");
		MAKE_MATERIAL(noLightShader, L"fire_bolt_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_bolt.png", L"fireBoltIcon");
		MAKE_MATERIAL(noLightShader, L"fire_mastery_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_mastery.png", L"fireMasteryIcon");
		MAKE_MATERIAL(noLightShader, L"fire_wall_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_wall.png", L"fireWallIcon");
		MAKE_MATERIAL(noLightShader, L"hydra_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\hydra.png", L"hydraIcon");
		MAKE_MATERIAL(noLightShader, L"inferno_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\inferno.png", L"infernoIcon");
		MAKE_MATERIAL(noLightShader, L"meteor_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\meteor.png", L"meteorIcon");
		MAKE_MATERIAL(noLightShader, L"warmth_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\warmth.png", L"warmthIcon");
#pragma endregion
#pragma region Skill Click Fire
		MAKE_MATERIAL(noLightShader, L"blaze_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\blaze_c.png", L"blazeClickIcon");
		MAKE_MATERIAL(noLightShader, L"enchant_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\enchant_c.png", L"enchantClickIcon");
		MAKE_MATERIAL(noLightShader, L"fire_ball_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_ball_c.png", L"fireBallClickIcon");
		MAKE_MATERIAL(noLightShader, L"fire_bolt_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_bolt_c.png", L"fireBoltClickIcon");
		MAKE_MATERIAL(noLightShader, L"fire_mastery_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_mastery_c.png", L"fireMasteryClickIcon");
		MAKE_MATERIAL(noLightShader, L"fire_wall_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\fire_wall_c.png", L"fireWallClickIcon");
		MAKE_MATERIAL(noLightShader, L"hydra_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\hydra_c.png", L"hydraClickIcon");
		MAKE_MATERIAL(noLightShader, L"inferno_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\inferno_c.png", L"infernoClickIcon");
		MAKE_MATERIAL(noLightShader, L"meteor_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\meteor_c.png", L"meteorClickIcon");
		MAKE_MATERIAL(noLightShader, L"warmth_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\fire\\warmth_c.png", L"warmthClickIcon");
#pragma endregion
#pragma region Skill Lightning
		MAKE_MATERIAL(noLightShader, L"chain_lightning_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\chain_lightning.png", L"chainLightningIcon")
			MAKE_MATERIAL(noLightShader, L"charged_bolt_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\charged_bolt.png", L"chargedBoltIcon")
			MAKE_MATERIAL(noLightShader, L"energy_shield_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\energy_shield.png", L"energyShieldIcon")
			MAKE_MATERIAL(noLightShader, L"lightning_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\lightning.png", L"lightningIcon")
			MAKE_MATERIAL(noLightShader, L"lightning_mastery_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\lightning_mastery.png", L"lightningMasteryIcon")
			MAKE_MATERIAL(noLightShader, L"nova_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\nova.png", L"novaIcon")
			MAKE_MATERIAL(noLightShader, L"static_field_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\static_field.png", L"staticFieldIcon")
			MAKE_MATERIAL(noLightShader, L"telekinesis_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\telekinesis.png", L"telekinesisIcon")
			MAKE_MATERIAL(noLightShader, L"teleport_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\teleport.png", L"teleportIcon")
			MAKE_MATERIAL(noLightShader, L"thunder_storm_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\thunder_storm.png", L"thunderStormIcon")
#pragma endregion
#pragma region Skill Click Lightning
			MAKE_MATERIAL(noLightShader, L"charged_bolt_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\charged_bolt_c.png", L"chargedBoltClickIcon")
			MAKE_MATERIAL(noLightShader, L"static_field_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\static_field_c.png", L"staticFieldClickIcon")
			MAKE_MATERIAL(noLightShader, L"telekinesis_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\telekinesis_c.png", L"telekinesisClickIcon")
			MAKE_MATERIAL(noLightShader, L"nova_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\nova_c.png", L"novaClickIcon")
			MAKE_MATERIAL(noLightShader, L"lightning_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\lightning_c.png", L"lightningClickIcon")
			MAKE_MATERIAL(noLightShader, L"chain_lightning_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\chain_lightning_c.png", L"chainLightningClickIcon")
			MAKE_MATERIAL(noLightShader, L"teleport_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\teleport_c.png", L"teleportClickIcon")
			MAKE_MATERIAL(noLightShader, L"thunder_storm_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\thunder_storm_c.png", L"thunderStormClickIcon")
			MAKE_MATERIAL(noLightShader, L"energy_shield_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\energy_shield_c.png", L"energyShieldClickIcon")
			MAKE_MATERIAL(noLightShader, L"lightning_mastery_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\lightning_mastery_c.png", L"lightningMasteryClickIcon")
			MAKE_MATERIAL(noLightShader, L"thunder_storm_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\lightning\\thunder_storm_c.png", L"thunderStormClickIcon")
#pragma endregion
#pragma region Skill ETC
			MAKE_MATERIAL(noLightShader, L"normal_attack_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\normal_attack.png", L"normalAttackIcon")
			MAKE_MATERIAL(noLightShader, L"normal_attack_click_icon", L"..\\Resources\\texture\\ui\\skill\\sorceress_skill_icons\\normal_attack_c.png", L"normalAttackClickIcon")
#pragma endregion
#pragma region NPC
			MAKE_MATERIAL_PATH(spriteShader, L"npc_1", L"..\\Resources\\texture\\npc\\npc_1"
				, 29, 76, 16, L"npc1");

		MAKE_MATERIAL_PATH(spriteShader, L"npc_2", L"..\\Resources\\texture\\npc\\npc_2"
			, 29, 76, 17, L"npc2");
#pragma endregion
#pragma region Shop
		MAKE_MATERIAL(noLightShader, L"shop_inventory", L"..\\Resources\\texture\\ui\\play\\shop\\shop_invens.png", L"shopInventory");
#pragma endregion
#pragma region Status
		MAKE_MATERIAL(noLightShader, L"character_status", L"..\\Resources\\texture\\ui\\play\\characterpanel_panel.png", L"characterStatus");
		MAKE_MATERIAL(noLightShader, L"stat_point", L"..\\Resources\\texture\\ui\\play\\stat_point.png", L"statPoint");

#pragma endregion
#pragma region Character Select
		MAKE_MATERIAL_PATH(spriteShader, L"sorceress_pick_loop", L"..\\Resources\\texture\\character_select\\sorceress_pick_loop"
			, 120, 260, 12, L"sorceressPickLoop");
		MAKE_MATERIAL_T(noLightShader, L"character_select_fire", L"..\\Resources\\texture\\character_select\\fire.png", L"characterSelectFire");
		MAKE_MATERIAL_T(noLightShader, L"character_name_Input", L"..\\Resources\\texture\\character_select\\character_name_Input.png", L"characterNameInput");
#pragma endregion
#pragma region Inventory
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"inventory_panel", L"..\\Resources\\texture\\ui\\play\\inventorypanel.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(noLightShader);
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
			material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"AnimationMaterial", material);
		}
		{
			spriteShader
				= Resources::Find<Shader>(L"NoLightAnimationShader");
			std::shared_ptr<Material> material = std::make_shared<Material>();

			material = std::make_shared<Material>();
			material->SetShader(spriteShader);
			material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"NoLightAnimationMaterial", material);
		}
		{
			spriteShader
				= Resources::Find<Shader>(L"ShadowAnimationShader");
			//spriteShader->SetBSState(eBSType::NoBlendOhter);

			std::shared_ptr<Material> material = std::make_shared<Material>();

			material = std::make_shared<Material>();
			material->SetShader(spriteShader);
			material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"ShadowAnimationMaterial", material);
		}
		{
			std::shared_ptr<Shader> shader
				= Resources::Find<Shader>(L"ParticleShader");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"ParticleMaterial", material);
		}
		{
			std::shared_ptr<Shader> shader
				= Resources::Find<Shader>(L"TileShader");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"TileMaterial", material);
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
			attribute.size = lights.size();
			lightsAttributes.push_back(attribute);
		}
		lights.clear();

		if (!lightsAttributes.empty())
		{
			lightsBuffer->SetData(lightsAttributes.data(), lightsAttributes.size());
			lightsBuffer->BindSRV(eShaderStage::VS, 13);
			lightsBuffer->BindSRV(eShaderStage::PS, 13);
		}
	}
	void BindNoiseTexture()
	{
	}
	void Render()
	{
		//BindNoiseTexture();
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



