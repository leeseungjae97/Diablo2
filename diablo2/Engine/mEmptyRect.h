#pragma once
#include "_Engine.h"
#include "../engine_source/mGameObject.h"
namespace m
{
	class EmptyRect
	{
	public:
		EmptyRect();
		~EmptyRect();

		bool GetFill() { return bFill; }
		void SetFill(bool fill) { bFill = fill; }

		void SetSize(Vector2 size) { mSize = size; }
		void SetSize(float x, float y) { mSize = Vector2(x, y); }
		Vector2 GetSize() { return mSize; }

		void SetPos(Vector2 pos) { mPos = pos; }
		void SetPos(float x, float y) { mPos = Vector2(x, y); }
		Vector2 GetPos() { return mPos; }

		bool MouseHover(float z, Camera* camera);
		bool MouseClick(float z, Camera* camera);

		void SetState(GameObject::eState state) { mState = state; }
		GameObject::eState GetState() { return mState; }
		void SetItemType(int item) { mEquimentItemType = item; }
		int GetItemType() { return mEquimentItemType; }

		void SetItem(int item) { mEqumentItem = item; }
		int GetItem() { return mEqumentItem; }

		void SetXY(int x, int y) { xy.x = x; xy.y = y; }
		Vector2 GetXY() { return xy; }
    private:
		Vector2 mPos;
		Vector2 mSize;
		Vector2 xy;
		GameObject::eState mState;

		int mEquimentItemType;
		int mEqumentItem;
		
		bool bFill;
	};
}

