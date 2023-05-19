#include "mEnums.h"


namespace m::enums {
	const char* charComponentType[(int)eComponentType::End] =
	{
		//component
		"Component",
		"Transform",
		"Camera",
		"Collider",
		"Animator",
		"Light",

		//render
		"MeshRenderer",
		"SpriteRenderer",
		"ParticleSystem",
		"SkyBox",
		"Decal",

		//etc
		"Script",
	};

	const wchar_t* wcharComponentType[(int)eComponentType::End] =
	{
		//component
		L"Component",
		L"Transform",
		L"Camera",
		L"Collider",
		L"Animator",
		L"Light",

		//render
		L"MeshRenderer",
		L"SpriteRenderer",
		L"ParticleSystem",
		L"SkyBox",
		L"Decal",

		//etc
		L"Script",
	};

	const char* charResourceType[(int)eResourceType::End] =
	{
		"Mesh",
		"Texture",
		"Material",
		"Sound",
		"Prefab",
		"MeshData",
		"GraphicsShader",
		"ComputeShader",
	};

	const wchar_t* wcharResourceType[(int)eResourceType::End] =
	{
		L"Mesh",
		L"Texture",
		L"Material",
		L"Sound",
		L"Prefab",
		L"MeshData",
		L"GraphicsShader",
		L"ComputeShader",
	};
}