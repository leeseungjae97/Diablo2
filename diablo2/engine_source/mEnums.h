#pragma once

namespace m::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
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
}