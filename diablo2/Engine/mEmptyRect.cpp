#include "mEmptyRect.h"

#include "../engine_source/mMouseManager.h"

namespace m
{
	EmptyRect::EmptyRect()
		: mPos(Vector2::Zero)
		, mSize(Vector2::One)
		, mState()
		, bFill(false)
	    , mEquimentItemType(0)
	    , mEqumentItem(0)
	{
	}

	EmptyRect::~EmptyRect()
	{
	}

	bool EmptyRect::MouseHover(float z, Camera* camera)
	{
		Vector3 mousePos = MouseManager::UnprojectionMousePos(z, camera);
		MAKE_VEC2_F_VEC3(mousePosV2, mousePos);
		return Vector2::PointIntersectRect(mPos, mSize, mousePosV2);
	}

	bool EmptyRect::MouseClick(float z, Camera* camera)
	{
		Vector3 mousePos = MouseManager::UnprojectionMousePos(z, camera);
		MAKE_VEC2_F_VEC3(mousePosV2, mousePos);
		if (Vector2::PointIntersectRect(mPos, mSize, mousePosV2))
		{
			return Input::GetKeyDown(eKeyCode::LBUTTON);
		}
		return false;
	}
}