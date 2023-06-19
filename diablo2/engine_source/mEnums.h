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
		End,
	};
	enum class eLayerType
	{
		Player,
		Monster,
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