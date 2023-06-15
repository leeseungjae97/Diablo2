#include "mRenderer.h"


namespace m::renderer
{
	vector<Vertex> vertexes;
	vector<UINT> indexes;

	m::Mesh* mesh = nullptr;
	m::Shader* shader = nullptr;

	m::graphics::ConstantBuffer* constantBuffer = nullptr;

	void SetupState()
	{
		// Input layout 정점 구조 정보를 넘겨줘야한다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

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


		m::graphics::GetDevice()->CreateInputLayout(arrLayout, 2
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());
	}

	void LoadBuffer()
	{
		mesh = new m::Mesh();
		mesh->CreateVertexBuffer(vertexes.data(), 4);

		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		constantBuffer = new m::graphics::ConstantBuffer(eCBType::Transform);
		constantBuffer->Create(sizeof(Vector4));
	}

	void LoadShader()
	{
		//m::graphics::GetDevice()->CreateShader();
		shader = new m::Shader();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
	}

	void Initialize()
	{
		// triangle
		vertexes.resize(3);
		
		vertexes[0].pos = Vector3(0.0f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		// rhombus
		//vertexes.resize(4);
		//
		//vertexes[0].pos = Vector3(0.0f, 0.1f, 0.0f);
		//vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		//vertexes[1].pos = Vector3(0.1f, -0.1f, 0.0f);
		//vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		//vertexes[2].pos = Vector3(-0.1f, -0.1f, 0.0f);
		//vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		//
		//vertexes[3].pos = Vector3(0.0f, -0.3f, 0.0f);
		//vertexes[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		//indexes.push_back(3);
		//indexes.push_back(2);
		//indexes.push_back(1);

		//indexes.push_back(0);
		//indexes.push_back(1);
		//indexes.push_back(2);
		 
		// rect
		//vertexes.resize(4);

		//vertexes[0].pos = Vector3(-0.1f, 0.1f, 0.0f);
		//vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		//vertexes[1].pos = Vector3(0.1f, 0.1f, 0.0f);
		//vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		//vertexes[2].pos = Vector3(0.1f, -0.1f, 0.0f);
		//vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		//vertexes[3].pos = Vector3(-0.1f, -0.1f, 0.0f);
		//vertexes[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		//indexes.push_back(0);
		//indexes.push_back(2);
		//indexes.push_back(3);

		//indexes.push_back(0);
		//indexes.push_back(1);
		//indexes.push_back(2);


		// circle, polygon
		/*Vertex center = {
			Vector3(0.0f, 0.0f, 0.0f) ,
			Vector4(0.0f, 1.0f, 0.0f, 1.0f)
		};

		vertexes.push_back(center);


		int iSlice = 80;
		float fRadius = 0.5f;
		float fTheta = (3.14159f * 2.f) / (float)iSlice;


		for (float i = 0; i < iSlice; i++)
		{
			Vertex circleLine = {
				Vector3(fRadius * cosf(fTheta * i)
					, fRadius * sinf(fTheta * i)
					, 0.0f),
				Vector4(0.0f, 1.0f, 0.0f, 1.f)
			};
			circleLine.pos.x -= (fRadius * cosf(fTheta * i)) / 2;
			vertexes.push_back(circleLine);
		}

		int j = 0;
		for (int i = vertexes.size() - 1; i >= 0; --i)
		{
			j++;
			indexes.push_back(i + 1);
			if (j == 2)
			{
				j = 0;
				indexes.push_back(1);
				i++;
			}
		}
		indexes.push_back(1);*/

		LoadBuffer();
		LoadShader();
		SetupState();
	}
	void Release()
	{
		delete mesh;
		delete shader;
		delete constantBuffer;
	}
}



