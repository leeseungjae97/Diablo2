#include "mEmptyRect.h"
#include "mMouseManager.h"

namespace m
{
	EmptyRect::EmptyRect()
		: bFill(false)
		, mPos(Vector2::Zero)
		, mSize(Vector2::One)
	{
	}
	EmptyRect::~EmptyRect()
	{}

    void EmptyRect::AddItem(Item* item)
    {
		//TODO:1
    }

    void EmptyRect::EraseItem(Item* item)
    {
		//TODO:2
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
		if(Vector2::PointIntersectRect(mPos, mSize, mousePosV2))
		{
			return Input::GetKeyDown(eKeyCode::LBUTTON);
		}
		return false;
	}
}
