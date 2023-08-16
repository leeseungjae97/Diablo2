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
		void Release();

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
		void SetVisible(bool visible) { bVisible = visible; }

		bool GetVisible() { return bVisible; }
		bool GetOnEnter() { return bOnEnter; }
		bool GetOnStay() { return bOnStay; }
		bool GetOnExit() { return bOnExit; }

		void SetExit() { bOnEnter = false; bOnExit = true; bOnStay = false; }
		void SetEnter() { bOnEnter = true; bOnExit = false; bOnStay = false; }
		void SetStay() { bOnEnter = false; bOnExit = false; bOnStay = true; }

		std::vector<Collider2D*>& GetCollidereds() { return collidereds; }

		void SetColliderFunctionType(eColliderFunctionType type) { mFunctionType = type; }
		eColliderFunctionType GetColliderFunctionType() { return mFunctionType; }

		bool SearchObjectGameObjectId(UINT gameObjectId);

		void Resize() { bResize = true; }
	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		std::vector<eLayerType> exceptTypes;
		std::vector<Collider2D*> collidereds;
		eColliderFunctionType mFunctionType;

		eColor mColor;
		Transform* mTransform;

		Vector3 mPosition;
		Vector3 mScale;
		Vector3 mRotation;

		Vector3 mSize;
		Vector2 mCenter;

		bool bOnEnter;
		bool bOnStay;
		bool bOnExit;

		bool bVisible;

		bool bResize;
	};
}

