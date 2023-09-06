#pragma once
#include "guiWidget.h"
namespace gui
{
    class GameView :
        public Widget
    {
	public:
		GameView();
		~GameView();

		virtual void FixedUpdate() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
    private:
    };
}

