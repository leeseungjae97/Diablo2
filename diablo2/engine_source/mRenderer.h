#pragma once
#include "_Engine.h"
#include "mGraphicDevice_Dx11.h"
#include "mShader.h"
#include "mMesh.h"
#include "mConstantBuffer.h"

using namespace m::math;
using namespace m::graphics;
namespace m::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	extern vector<Vertex> vertexes;
	extern vector<UINT> indexes;

	extern m::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::END];

	void Initialize();
	void Release();
}
