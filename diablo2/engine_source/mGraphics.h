#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "mEnums.h"
#include "mMath.h"
#include "mCamera.h"

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name 

#define CBSLOT_TRANSFORM		0
#define CBSLOT_GRID				2
#define CBSLOT_ANIMATOR			3
enum class eShaderStage
{
	VS,
	HS,
	DS,
	GS,
	PS,
	CS,
	END,
};

enum class eSamplerType
{
	Point,
	Anisotropic,
	End,
};

enum class eCBType
{
	Transform,
	Material,
	Grid,
	Animator,
	Vertex,
	END,
};
enum class eRSType
{
	SolidBack,
	SolidFront,
	SolidNone,
	WireframeNone,
	End,
};

enum class eDSType
{
	Less,
	LessEqua,
	Greater,
	NoWrite,
	None,
	End,
};

enum class eBSType
{
	Default,
	AlphaBlend,
	OneOne,
	End,
};
enum class eRenderingMode
{
	Opaque,
	CutOut,
	Transparent,
	End,
};

struct GpuBuffer
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	D3D11_BUFFER_DESC desc;

	GpuBuffer()
		: buffer(nullptr)
		, desc{}
	{

	}
	virtual ~GpuBuffer() = default;
};
struct DebugMesh
{
	m::enums::eColliderType type;
	m::math::Vector3 position;
	m::math::Vector3 rotation;
	m::math::Vector3 scale;
	m::math::Matrix view;
	m::math::Matrix projection;
	m::enums::eColor color;

	bool visible;
	float radius;
	float duration;
	float time;
};
struct Vertex
{
	m::math::Vector3 pos;
	m::math::Vector4 color;
	m::math::Vector2 uv;
};