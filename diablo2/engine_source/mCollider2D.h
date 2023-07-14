#pragma once
#include "mComponent.h"
#include "mTransform.h"

namespace m
{
	class Collider2D :
		public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 size) { mCenter = size; }

		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);

		UINT GetColliderID() { return mColliderID; }

		Vector3 GetPosition() { return mPosition; }
		Vector3 GetScale() { return mScale; }
		Vector3 GetRotation() { return mRotation; }

		Vector2 GetSize() { return mSize; }
		Vector2 GetCenter() { return mCenter; }
		eColliderType GetType() { return mType; }
		void SetRectColor(eColor color) { mColor = color; }
	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		eColor mColor;
		Transform* mTransform;

		Vector3 mPosition;
		Vector3 mScale;
		Vector3 mRotation;

		Vector2 mSize;
		Vector2 mCenter;
	};
}

