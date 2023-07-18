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
		End,
	};
	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};
	enum class eColor
	{
		Red,
		Green,
		Blue,
		End,
	};
}