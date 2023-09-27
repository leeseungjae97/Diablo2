#pragma once
#include "mGameObject.h"
#include "mMath.h"

namespace m
{
    class Camera;
    class InteractUI;
	class InteractUIManager
	{
	public:
		enum class eInteractUIType
		{
			ExItem,
			BuyItem,
			BuyFail,
			End,
		};
		static void Update();
        static GameObject::eState GetInteractUIState();
        static void SetInteractUIState(GameObject::eState state);
		static void SetItemUI(
			int itemType
			, eInteractUIType type
			, m::math::Vector3 pos
			, bool exBack
			, Camera* camera
			, float fontSize = 15.f
		);

		static bool bItemHover;
		static InteractUI* mShopInteractUI;
		static eInteractUIType mCurUIType;
		static m::math::Vector3 mInitPos;
	};
}

