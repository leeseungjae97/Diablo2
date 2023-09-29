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
		Shadow,
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
		Overlay,
		MonsterOverlay,
		PlayerOverlay,
		Aura,
		FieldItem,
		Shadow,
		Wall,
		Summons,
		Player,
		Monster,
		NPC,
		AdapterSkill,
		Skill,
		PlayerSkill,
		MonsterSkill,
		Light,
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