#pragma once
#include "mComponent.h"

namespace m
{
	class Camera
		: public Component
	{
	public:
		enum class eProjectionType
		{
			Perspective,
			Orthorgaphic,
			None,
		};
		static Matrix GetViewMatrix() { return View; }
		static Matrix GetProjectionMatrix() { return Projection; }

		Matrix GetPrivateViewMatrix() { return mView; }
		Matrix GetPrivateProjectionMatrix() { return mProjection; }
		static Vector2 GetCameraCenter() { return mCameraCenter; }
		Camera();
		~Camera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		bool CreateViewMatrix();
		bool CreateProjectionMatrix(eProjectionType type);
		void RegisterCameraInRenderer();

		void TurnLayerMask(eLayerType type, bool enable = true);
		void EnableLayerMasks() { mLayerMask.set(); }
		void DisableLayerMasks() { mLayerMask.reset(); }

		void AlphaSortGameObject();
		void ZSortTransparencyGameObjects();
		void DivideAlphaBlendGameObjects(const std::vector<GameObject*> gameObjs);
		
		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();

		static void EnableDepthStencilState();
		static void DisableDepthStencilState();

		void SetFollowObject(GameObject* f) { mFollowObject = f; }
		GameObject* GetFollowObject() { return mFollowObject; }

	private:
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;

		static Vector2 mCameraCenter;

		eProjectionType mType;
		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;

		std::bitset<(UINT)eLayerType::End> mLayerMask;
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutOutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;

		GameObject* mFollowObject;
	};
}

