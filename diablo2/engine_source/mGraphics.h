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
#define CBSLOT_UV				4
#define CBSLOT_PARTICLE			5
#define CBSLOT_NOISE			6
#define CBSLOT_TILE				7
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
	End,
};

enum class eCBType
{
	Transform,
	Material,
	Grid,
	Animator,
	UVControl,
	Particle,
	Noise,
	Tile,
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
	NoBlendOhter,
	End,
};
enum class eRenderingMode
{
	Opaque,
	CutOut,
	Transparent,
	End,
};
enum class eViewType
{
	None,
	SRV,
	UAV,
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
struct LightAttribute
{
	m::math::Vector4 color;
	m::math::Vector4 position;
	m::math::Vector4 direction;

	m::enums::eLightType type;
	float radiusX;
	float radiusY;
	float angle;
	int pad;
	int size;
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

	BOOL visible;
	float radius;
	float duration;
	float time;
};
//struct PathFinderSharedData
//{
//	BOOL findStart = false;
//	m::math::Vector2 startTileCoord;
//	m::math::Vector2 targetTileCoord;
//
//	float searchSize;
//
//	BOOL allowdiagonal = true;
//	BOOL dontcrosscorner = true;
//
//	int xLength;
//	int yLength;
//
//	BOOL isMonster;
//	int monsterId;
//};
//struct FoundedPath
//{
//	m::math::Vector2 foundPaths;
//};

struct DrawObject
{
	m::math::Vector4 position = m::math::Vector4::Zero;
	m::math::Vector2 size = m::math::Vector2::Zero;
};
struct SkillWallCollision
{
	m::math::Vector3 skillPosition = m::math::Vector3::Zero;
	int skillId = 0;
	BOOL crash = false;
};
struct ComputeTile
{
	m::math::Vector4 tilePosition = m::math::Vector4::Zero;
	m::math::Vector2 tileSize = m::math::Vector2::Zero;
	m::math::Vector2 tileCoord = m::math::Vector2::Zero;

	BOOL isWall = false;
	BOOL isThrough = false;

	//m::math::Vector2 parentCoord;

	
	//BOOL onMonster;

	//UINT willOnMonsterCount;

	//BOOL inClose;
	//BOOL inOpen;

	//int G;
	//int H;
};
struct TrapColor
{
	m::math::Vector4 color = m::math::Vector4(1.f, 1.f, 1.f, 1.f);
};
struct SpriteOffsetCenter
{
	m::math::Vector2 offset = m::math::Vector2(0.f, 0.f);
};
struct SpriteAlpha
{
	float alpha = 1.f;
};
struct ComputeTileSharedData
{
	m::math::Vector4 mousePos = m::math::Vector4::Zero;
	m::math::Vector4 playerPos = m::math::Vector4::Zero;
	UINT tileCount = 0;
	UINT monsterCount = 0;
	int skillCount = 0;
	BOOL hoverUI = false;
};
struct ComputedTileCoord
{
	m::math::Vector2 mouseHoverTileCoord = m::math::Vector2(-1.f, -1.f);
	m::math::Vector2 playerStandTileCoord = m::math::Vector2(-1.f, -1.f);
	m::math::Vector2 hoverMonsterTileCoord = m::math::Vector2(-1.f, -1.f);
	int hoverMonsterId = -1;
	BOOL hoverMonster = false;
};
struct ComputeMonster
{
	m::math::Vector4 monsterPos = m::math::Vector4::Zero;
	m::math::Vector3 monsterSize = m::math::Vector3::Zero;
	m::math::Vector2 monsterNextCoord = m::math::Vector2::Zero;
	int monsterCount = 0;
};
struct ComputedMonsterCoord
{
	m::math::Vector2 monsterStandTileCoord = m::math::Vector2(-1.f, -1.f);
};
struct Vertex
{
	m::math::Vector3 pos;
	m::math::Vector4 color;
	m::math::Vector2 uv;
};
struct Particle
{
	m::math::Vector4 position;
	m::math::Vector4 direction;

	float alpha;
	float alpha2;
	float alpha3;
	float endTime;
	float time;
	float speed;
	UINT active;
};
struct ParticleShared
{
	UINT sharedActiveCount;
};
//struct BoundingSphere
//{
//	m::math::Vector3 center;
//	float radius;
//};