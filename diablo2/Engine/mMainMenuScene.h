#pragma once
#include "..\engine_source\mScene.h"

namespace m
{
	class Camera;
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
