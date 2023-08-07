#pragma once
#include "_Engine.h"
#include "mGraphicDevice_DX11.h"
#include "mShader.h"
#include "mMesh.h"
#include "mConstantBuffer.h"
#include "mCamera.h"
#include "mLight.h"

using namespace m::math;
namespace renderer
{
	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix View;
		Matrix Projection;
	};
	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};
	CBUFFER(AnimatorCB, CBSLOT_ANIMATOR)
	{
		Vector2 spriteLeftTop;
		Vector2 spriteSize;
		Vector2 spriteOffset;
		Vector2 atlasSize;
		UINT animationType = 0;
		float alpha;
	};
	CBUFFER(UVControlCB, CBSLOT_UV)
	{
		float UVYCoord = 1.f;
		UINT uvControlType = 0;
	};
	CBUFFER(ParticleCB, CBSLOT_PARTICLE)
	{
		UINT elementCount;
		float elpasedTime;
		int padd;
		int padd2;
	};

	extern m::graphics::ConstantBuffer* constantBuffers[(UINT)eCBType::END];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<m::Light*> lights;
	extern m::Camera* mainCamera;
	extern std::vector<m::Camera*> cameras;
	extern std::vector<DebugMesh> debugMeshs;

	void Initialize();
	void BindLights();
	void Render();
	void Release();

	void PushDebugMeshAttribute(DebugMesh& mesh);
}
