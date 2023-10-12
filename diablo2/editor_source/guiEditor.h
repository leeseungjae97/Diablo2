#pragma once

#include "../engine_source/_Engine.h"
#include "../engine_source/mGraphics.h"

#include "guiWidget.h"
#include "guiEditorObject.h"
#include "guiDebugObject.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

namespace gui
{
    class Dockspace;
    class Editor
	{
	public:
		static void Initialize();
		static void Run();

		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		static void DebugRender(const DebugMesh& mesh);

	private:
		static void imguiInit();
		static void imguiRender();
		static void imguiRelease();

	private:
		static std::map<std::wstring, Widget*> mWidgets;
		static std::vector<EditorObject*> mEditorObjects;
		static std::vector<DebugObject*> mDebugObjects;

		static bool noRender;
		static ImGuiIO mIO;

		static Dockspace* mDockspace;
	};
}
