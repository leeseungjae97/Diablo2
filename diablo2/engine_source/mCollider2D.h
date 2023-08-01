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
		void SetSize(Vector3 size) { mSize = size; }
		void SetCenter(Vector2 size) { mCenter = size; }

		void SetColor(eColor color) { mColor = color; }
		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);

		UINT GetColliderID() { return mColliderID; }

		Vector3 GetPosition() { return mPosition; }
		Vector3 GetScale() { return mScale; }
		Vector3 GetRotation() { return mRotation; }

		Vector3 GetSize() { return mSize; }
		Vector2 GetCenter() { return mCenter; }
		eColliderType GetType() { return mType; }

		void AddExceptType(eLayerType type) { exceptTypes.push_back(type); }
		void ClearExceptType() { exceptTypes.clear(); }

		bool GetOnEnter() { return bOnEnter; }
		bool GetOnStay() { return bOnStay; }
		bool GetOnExit() { return bOnExit; }

		int GetInsertsectColliderNumber() { return intersectColliderNumber; }

		Vector3 GetCollideredObjectPos() { return collideredObjectPos; }
		std::vector<GameObject*>& GetCollideredObjects() { return collideredObjects; }
	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		std::vector<eLayerType> exceptTypes;
		std::vector<GameObject*> collideredObjects;

		eColor mColor;
		Transform* mTransform;

		Vector3 mPosition;
		Vector3 mScale;
		Vector3 mRotation;

		Vector3 mSize;
		Vector2 mCenter;

		Vector3 collideredObjectPos;

		int intersectColliderNumber;

		bool bOnEnter;
		bool bOnStay;
		bool bOnExit;
	};
}

