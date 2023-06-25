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
	enum class eSceneType
	{
		MainMenuScene,
		SelectCharacterScene,
		PlayScene,
		End,
	};

	std::wstring wsScenes[(UINT)eSceneType::End] =
	{
		L"MainMenuScene",
		L"SelectCharacterScene",
		L"PlayScene",
	};
}