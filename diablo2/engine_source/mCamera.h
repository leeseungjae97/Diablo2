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
		static Matrix& GetViewMatrix() { return View; }
		static Matrix& GetProjectionMatrix() { return Projection; }
		static void SetViewMatrix(Matrix view) { View = view; }
		static void SetProjectionMatrix(Matrix proj) { Projection = proj; }

		Matrix& GetPrivateViewMatrix() { return mView; }
		Matrix& GetPrivateProjectionMatrix() { return mProjection; }
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
		void DivideAlphaBlendGameObjects(const std::vector<GameObject*>& gameObjs);
		
		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();
		bool ClipingArea(GameObject* gameObj);
		static void EnableDepthStencilState();
		static void DisableDepthStencilState();

		void SetFollowObject(GameObject* f) { mFollowObject = f; }
		GameObject* GetFollowObject() { return mFollowObject; }

		float GetSize() { return mSize; }

	private:
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;

		float mWidth;
		float mHeight;
		Vector3 mPos;

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

