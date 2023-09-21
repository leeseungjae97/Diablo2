#pragma once
#include "../engine_source/mGameObject.h"
#include "../engine_source/OverlayLookUpTables.h"

namespace m
{
	class MoveAbleObject;

	class Overlay :
		public GameObject
	{
	public:
		Overlay(const std::wstring& overlayName
			, Vector3 initPos
			, Vector2 size = Vector2::Zero
			, Vector2 offset = Vector2::Zero
			, Vector2 centerPos = Vector2::Zero
			, int length = 0
			, float duration = 0.f
			, bool loop = true
		);
		virtual ~Overlay();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void MakeOverlay(const std::wstring& overlayName
			, Vector2 size = Vector2::Zero
			, Vector2 offset = Vector2::Zero
			, Vector2 centerPos = Vector2::Zero
			, int length = 0
			, float duration = 0.f
			, bool loop = true
		);
		void SetDirection(int direction);
		void SetSyncPlay(Animator* animator);

		void SetMoveAbleObject(MoveAbleObject* mao) { mOwnerObject = mao; }
		void OverDraw() { bOverDraw = true; }
	private:
		std::wstring wsOverlayName;
		MoveAbleObject* mOwnerObject;
		bool bOverDraw;
	};
}


