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

	}
	Tile::~Tile()
	{}
}