#pragma once
#include "guiWidget.h"


namespace gui
{
	class Dockspace : public Widget
	{
	public:
		Dockspace();
		~Dockspace();

		virtual void FixedUpdate() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		bool mFullScreen;
		bool mPadding;
		ImGuiDockNodeFlags mDockspaceFlags;
	};
}
