#pragma once
#include "_Engine.h"
#include "mGraphicDevice_Dx11.h"
#include "mShader.h"
#include "mMesh.h"

using namespace m::math;
namespace m::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern vector<Vertex> vertexes;
	extern vector<UINT> indexes;
	//extern ID3D11Buffer* triangleBuffer;
	//extern ID3D11Buffer* triangleIndexBuffer;

	extern m::Mesh* mesh;
	extern m::Shader* shader;

	//extern ID3DBlob* triangleVSBlob;
	//extern ID3DBlob* trianglePSBlob;
	//extern ID3DBlob* errorBlob;

	extern ID3D11InputLayout* triangleLayout;

	//extern ID3D11VertexShader* triangleVSShader;
	//extern ID3D11PixelShader* trianglePSShader;
	
	extern ID3D11Buffer* triangleConstantBuffer;

	void Initialize();
	void Release();
}