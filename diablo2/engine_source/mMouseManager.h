#pragma once
#include "mCamera.h"
#include "../Engine/mItem.h"
namespace m
{
	class MouseManager
	{
	public:
		static void SetMouseOnUI(bool onui) { mMouseOnUI = onui; }
		static bool GetMouseOnUI() { return mMouseOnUI; }
		static void SetMouseOnMonster(bool onmonster) { mMouseOnMonster = onmonster; }
		static bool GetMouseOnMonster() { return mMouseOnMonster; }
		static void SetMouseHoverMonsterTileCoord(Vector2 monsterCoord) { hoverMonsterTileCoord = monsterCoord; }
		static Vector2 GetMouseHoverMonsterTileCoord() { return hoverMonsterTileCoord; }

		static int GetMouseHoverMonsterId() { return hoverMonsterId; }
		static void SetMouseHoverMonsterId(int id) { hoverMonsterId = id; }

		static Vector3 UnprojectionMousePos(float z, Camera* camera);
		static void SetMouseFollow(InvenItem* item) { mMouseFollowItem = item; }

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static InvenItem* GetMouseFollow() { return mMouseFollowItem; }

    private:
		static bool mMouseOnUI;
		static bool mMouseOnMonster;

		static Vector2 hoverMonsterTileCoord;
		static int hoverMonsterId;

		static InvenItem* mMouseFollowItem;
	};
}


