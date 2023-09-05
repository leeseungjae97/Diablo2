#include "mTile.h"

#include "../engine_source/mTransform.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTileManager.h"
#include "../engine_source/mMonsterManager.h"

#include "mTileScript.h"
#include "mPlayerManager.h"
#include "mPlayer.h"
#include "mMonster.h"
namespace m
{
	Tile::Tile()
		: mCoord(Vector2(-1.f, -1.f))
		, willOnMonsterCount(0)
		, isWall(false)
		, inClosed(false)
		, inOpen(false)
		, onMonster(false)
		, G(0)
		, H(0)
		, mParentTile(nullptr)
		
	{
		SetIsRhombus(true);
		ADD_COMP(this, TileScript);
		ADD_COMP(this, MeshRenderer);
	}
	Tile::~Tile()
	{}
	void Tile::Initialize()
	{
	}
	void Tile::Update()
	{
		GameObject::Update();

		//if (isWall) return;

		//if (GetHover())
		//{
		//	TileManager::hoverTile = this;
		//	SET_MATERIAL(this, L"greenTile");
		//}
		//else
		//{
		//	if(GetComponent<MeshRenderer>()->GetMaterial() != saveMaterial)
		//		GetComponent<MeshRenderer>()->SetMaterial(saveMaterial);
		//}

		//MAKE_VEC2_F_VEC3(posV2, GET_POS(this));
		//MAKE_VEC2_F_VEC3(scaleV2, GET_SCALE(this));
		//Vector3 ppos = GET_POS(PlayerManager::player);
		//Vector3 pscale = GET_SCALE(PlayerManager::player);
		//Vector2 playerPosV2Left = Vector2(ppos.x - pscale.x / 2.f, ppos.y - pscale.y / 2.f);
		//Vector2 playerPosV2Right = Vector2(ppos.x + pscale.x / 2.f, ppos.y - pscale.y / 2.f);
		//if (Vector2::PointIntersectRhombus(posV2, scaleV2, GET_VEC2_F_VEC3_D(ppos)))
		//{
		//	TileManager::playerStandTile = this;
		//}
		//for (Monster* monster : MonsterManager::monsters)
		//{
		//	MAKE_VEC2_F_VEC3(mPosV2, GET_POS(monster));
		//	if (Vector2::PointIntersectRhombus(posV2, scaleV2, mPosV2))
		//	{
		//		monster->SetCoord(mCoord);
		//	}
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