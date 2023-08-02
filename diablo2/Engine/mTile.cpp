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
		Collider2D* col = ADD_COMP(this, Collider2D);
		col->SetColor(eColor::None);
		col->AddExceptType(eLayerType::Player);

		AddComponent<MeshRenderer>();
	}
	Tile::~Tile()
	{}
	void Tile::Initialize()
	{
	}
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
		Vector3 ppos= GET_POS(PlayerInfo::player);
		Vector3 pscale= GET_SCALE(PlayerInfo::player);
		Vector2 playerPosV2Left = Vector2(ppos.x - pscale.x / 2.f, ppos.y - pscale.y / 2.f);
		Vector2 playerPosV2Right = Vector2(ppos.x + pscale.x / 2.f, ppos.y - pscale.y / 2.f);
		if (Vector2::PointIntersectRhombus(posV2, scaleV2, GET_VEC2_F_VEC3_D(ppos)))
		{
			TileManager::playerStandTile = this;
		}
		Collider2D* mCollider = GET_COMP(this, Collider2D);
		if (mCollider->GetOnEnter())
		{
			for (auto obj : mCollider->GetCollideredObjects())
			{
				auto dObj = dynamic_cast<MoveAbleObject*>(obj);
				if (dObj) dObj->SetCoord(GetCoord());
			}
		}
		//if (Vector2::PointIntersectRhombus(posV2, scaleV2, playerPosV2Left)
		//	&& Vector2::PointIntersectRhombus(posV2, scaleV2, playerPosV2Right))
		//{
		//	TileManager::playerStandTile = this;
		//}
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