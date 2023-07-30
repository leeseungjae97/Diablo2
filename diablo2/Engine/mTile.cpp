#include "mTile.h"

#include "..\engine_source\mTransform.h"
#include "..\engine_source\mMeshRenderer.h"
namespace m
{
	Tile::Tile(Vector2 coord)
		: mCoord(coord)
		, isWall(false)
	{
		AddComponent<MeshRenderer>();
	}
	Tile::~Tile()
	{}
	void Tile::Initialize()
	{}
	void Tile::Update()
	{
		GameObject::Update();
	}
	void Tile::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Tile::Render()
	{
		GameObject::Render();
	}
}