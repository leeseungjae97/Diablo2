#pragma once
#include "mCamera.h"

namespace m
{
	class MouseManager
	{
	public:
		static __forceinline void SetMouseOnUI(bool onui) { mMouseOnUI = onui; }
		static __forceinline bool GetMouseOnUI() { return mMouseOnUI; }
		static __forceinline void SetMouseOnMonster(bool onmonster) { mMouseOnMonster = onmonster; }
		static __forceinline bool GetMouseOnMonster() { return mMouseOnMonster; }
		static __forceinline void SetMouseHoverMonsterTileCoord(Vector2 monsterCoord) { hoverMonsterTileCoord = monsterCoord; }
		static __forceinline Vector2 GetMouseHoverMonsterTileCoord() { return hoverMonsterTileCoord; }
		static __forceinline int GetMouseHoverMonsterId() { return hoverMonsterId; }
		static __forceinline void SetMouseHoverMonsterId(int id) { hoverMonsterId = id; }
		static Vector3 UnprojectionMousePos(float z, Camera* camera);

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();

	private:
		static bool mMouseOnUI;
		static bool mMouseOnMonster;

		static Vector2 hoverMonsterTileCoord;
		static int hoverMonsterId;
	};
}


