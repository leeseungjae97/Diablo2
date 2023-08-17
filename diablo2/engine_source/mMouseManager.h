#pragma once
#include "mCamera.h"

namespace m
{
	class MouseManager
	{
	public:
		static __forceinline void SetMouseOnUI(bool onui) { mMouseOnUI = onui; }
		static __forceinline bool GetMouseOnUI() { return mMouseOnUI; }
		
		static Vector3 UnprojectionMousePos(float z, Camera* camera);

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();

	private:
		static bool mMouseOnUI;
	};
}


