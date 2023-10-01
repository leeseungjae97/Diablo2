#pragma once
namespace m
{
    class Camera;
    class GameObject;

    class ScreenEffectManager
	{
	public:
        static void Initialize();
		static void Update();
		static void DoFadeIn();
		static void DoFadeOut();
		static void DoFadeOutIn();
		static void DoShake();

		static void FadeIn();
		static void FadeOut();
		static void FadeOutIn();
		static void Shake(float time) { bShakeCamera = true; fShakeTime = time; }


		static GameObject* mFade;
		static Camera* mUICamera;
		static Camera* mPlayCamera;
		static float fFadeValue;

		static bool bFadeIn;
		static bool bFadeOut;
		static bool bFadeInOut;
		static bool bShakeCamera;

		static float fShakeTime;
	};
}


