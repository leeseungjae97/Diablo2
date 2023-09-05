#pragma once

#include "mInvenItem.h"
#include "mGameObject.h"

namespace m
{
	class EmptyRect
	{
	public:
		EmptyRect();
		~EmptyRect();

		bool GetFill() { return bFill; }
		void SetFill(bool fill) { bFill = fill; }

		InvenItem* GetFillItem() { return mFillItem; }
		void SetFillItem(InvenItem* item) { mFillItem = item; }

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

	private:
		Vector2 mPos;
		Vector2 mSize;

		InvenItem* mFillItem;
		GameObject::eState mState;
		
		bool bFill;
	};
}
