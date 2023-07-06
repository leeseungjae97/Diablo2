#pragma once
#include "..\engine_source\mScene.h"
#define RESOL_WID 1600.f
#define RESOL_HEI 900.f

//#define RESOL_WID 800.f
//#define RESOL_HEI 600.f

namespace m
{
	class MainMenuScene :
		public Scene
	{
	public:
		MainMenuScene();
		virtual ~MainMenuScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:
	};
}
