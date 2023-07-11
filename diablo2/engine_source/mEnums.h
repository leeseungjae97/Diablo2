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
		Script,
		Camera,
		End,
	};
	enum class eLayerType
	{
		//Camera,
		Grid,
		Player,
		Monster,
		Tile,
		UI,
		Item,
		End,
	};
	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
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
}