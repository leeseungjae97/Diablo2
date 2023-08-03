#pragma once

namespace m::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		Collider2D,
		Particle,
		MeshRenderer,
		Animator,
		Script,
		Light,
		Camera,
		End,
	};
	enum class eLayerType
	{
		//Camera,
		Grid,
		Tile,
		Player,
		Monster,
		Light,
		Skill,
		Camera,
		UI,
		Item,
		End = 16,
	};
	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
		ComputeShader,
		End,
	};
	enum class eColliderType
	{
		Dot,
		Rect,
		Circle,
		Sphere,
		Rhombus,
		Cube,
		End,
	};
	enum class eColor
	{
		Red,
		Green,
		Blue,
		None,
		End,
	};
	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};
}