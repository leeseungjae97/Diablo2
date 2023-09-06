#include "guiDockspace.h"

namespace gui
{
	Dockspace::Dockspace()
		: mFullScreen(true)
		, mPadding(false)
		, mDockspaceFlags(ImGuiDockNodeFlags_None)
	{
	}
	Dockspace::~Dockspace()
	{
	}
	void Dockspace::FixedUpdate()
	{
		// If you strip some features of, this demo is pretty much equivalent to calling DockSpaceOverViewport()!
	  // In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
	  // In this specific demo, we are not using DockSpaceOverViewport() because:
	  // - we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
	  // - we allow the host window to have padding (when opt_padding == true)
	  // - we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport() in your code!)
	  // TL;DR; this demo is more complicated than what you would normally use.
	  // If we removed all the options we are showcasing, this demo would become:
	  //     void ShowExampleAppDockSpace()
	  //     {
	  //         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	  //     }



	  // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	  // because it would be confusing to have two docking targets within each others.
		mFlag = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (mFullScreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			mFlag |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			mFlag |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			mDockspaceFlags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (mDockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
			mFlag |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!mPadding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		//ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	}
	void Dockspace::Update()
	{
		//ImGui::Begin("DockSpace Demo", p_open, window_flags);
		if (!mPadding)
			ImGui::PopStyleVar();

		if (mFullScreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("mDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), mDockspaceFlags);
		}
		else
		{
			//ShowDockingDisabledMessage();
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Options"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem("Fullscreen", NULL, &mFullScreen);
				ImGui::MenuItem("Padding", NULL, &mPadding);
				ImGui::Separator();

				if (ImGui::MenuItem("Flag: NoSplit", "", (mDockspaceFlags & ImGuiDockNodeFlags_NoSplit) != 0)) { mDockspaceFlags ^= ImGuiDockNodeFlags_NoSplit; }
				if (ImGui::MenuItem("Flag: NoResize", "", (mDockspaceFlags & ImGuiDockNodeFlags_NoResize) != 0)) { mDockspaceFlags ^= ImGuiDockNodeFlags_NoResize; }
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (mDockspaceFlags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { mDockspaceFlags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (mDockspaceFlags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { mDockspaceFlags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
				if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (mDockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, mDockspaceFlags)) { mDockspaceFlags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
				ImGui::Separator();

				bool Active = (bool)GetState();
				if (ImGui::MenuItem("Close", NULL, false, &Active != NULL))
					SetState(eState::Paused);

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		//ImGui::End();
	}

	//ImGui::End();a

	void Dockspace::LateUpdate()
	{

	}

	void Dockspace::Render()
	{
		Widget::Render();
	}

}
