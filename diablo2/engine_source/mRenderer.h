#pragma once
#include "_Engine.h"
#include "mGraphicDevice_Dx11.h"
#include "mShader.h"
#include "mMesh.h"
#include "mConstantBuffer.h"

using namespace m::math;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};

	extern vector<Vertex> vertexes;
	extern vector<UINT> indexes;

	extern m::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::END];

	void Initialize();
	void Release();
}
