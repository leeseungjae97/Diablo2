#include "mRenderer.h"


namespace m::renderer
{
	m::Shader* shader = nullptr;

	std::shared_ptr<class m::graphics::ConstantBuffer> constantBuffers[(UINT)eCBType::END];

	void SetupState()
	{
		// Input layout 정점 구조 정보를 넘겨줘야한다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

		arrLayout[0].AlignedByteOffset = 0;
		//arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 16;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 2
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());
	}

	void LoadBuffer()
	{
		constantBuffers[(UINT)eCBType::Transform] = std::make_shared<m::graphics::ConstantBuffer>(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(Vertex));
	}

	void LoadShader()
	{
		shader = new m::Shader();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
	}

	void Initialize()
	{
		LoadBuffer();
		LoadShader();
		SetupState();
	}
	void Release()
	{
		delete shader;

		//for(UINT i = 0 ; i < (UINT)eCBType::END; i++)
		//	delete constantBuffers[i];
	}
}



