#pragma once
#include "_Engine.h"
#include "mGraphicDevice_Dx11.h"
#include "mShader.h"
#include "mMesh.h"
#include "mConstantBuffer.h"

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

	extern m::Mesh* mesh;
	extern m::Shader* shader;
	extern m::graphics::ConstantBuffer* constantBuffer;

	void Initialize();
	void Release();
}
