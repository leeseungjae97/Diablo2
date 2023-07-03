#pragma once
namespace m
{
	class MouseManager
	{
	public:
		static __forceinline void SetMouseOnUI(bool onui) { mMouseOnUI = onui; }
		static __forceinline bool GetMouseOnUI() { return mMouseOnUI; }

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();

	private:
		static bool mMouseOnUI;
	};
}


