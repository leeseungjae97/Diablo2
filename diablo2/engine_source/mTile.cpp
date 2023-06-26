#include "mTile.h"
#include "mTransform.h"
#include "mMeshRenderer.h"
namespace m
{
	Tile::Tile(Vector3 iniPos, Vector2 coord)
		: mPosition(iniPos)
		, mCoord(coord)
	{
		GetComponent<Transform>()->SetPosition(iniPos);
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