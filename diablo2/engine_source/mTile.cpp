#include "mTile.h"
#include "mTransform.h"
#include "mMeshRenderer.h"
namespace m
{
	Tile::Tile(Vector2 coord)
		: mCoord(coord)
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