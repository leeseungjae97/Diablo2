#include "mTile.h"

#include "..\engine_source\mTransform.h"
#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mTileManager.h"

#include "mPlayerInfo.h"
#include "mPlayer.h"
namespace m
{
	Tile::Tile()
		: mCoord(Vector2(-1.f, -1.f))
		, isWall(false)
		, inClosed(false)
		, inOpen(false)
	{
		SetIsRhombus(true);	
		AddComponent<MeshRenderer>();
	}
	Tile::~Tile()
	{}
	void Tile::Initialize()
	{}
	void Tile::Update()
	{
		GameObject::Update();
		if (GetHover())
		{
			TileManager::hoverTile = this;
			SET_MATERIAL(this, L"testTile3");
		}
		else
		{
			SET_MATERIAL(this, L"testTile");
		}
		
		MAKE_VEC2_F_VEC3(posV2, GET_POS(this));
		MAKE_VEC2_F_VEC3(scaleV2, GET_SCALE(this));
		MAKE_VEC2_F_VEC3(playerPosV2, GET_POS(PlayerInfo::player));
		if (Vector2::PointIntersectRect(posV2, scaleV2, playerPosV2))
		{
			TileManager::playerStandTile = this;
		}
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