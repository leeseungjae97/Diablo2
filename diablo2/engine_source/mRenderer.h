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
		Vector4 pos;
		Vector4 color;
	};
	extern m::Shader* shader;
	extern std::shared_ptr<class m::graphics::ConstantBuffer> constantBuffers[];

	void Initialize();
	void Release();
}
