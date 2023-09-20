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
		AudioListener,
		AudioSource,
		Camera,
		End,
	};
	enum class eLayerType
	{	
		Camera,
		Grid,
		Background,
		Tile,
		MonsterOverlay,
		PlayerOverlay,
		Aura,
		FieldItem,
		Wall,
		Player,
		Monster,
		Light,
		AdapterSkill,
		Skill,
		PlayerSkill,
		MonsterSkill,
		UI,
		Item,
		End = 20,
	};
	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
		ComputeShader,
		AudioClip,
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
	enum class eColliderFunctionType
	{
		HitArea,
		Range,
		Sight,
		TilePos,
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