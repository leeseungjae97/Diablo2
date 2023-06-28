#pragma once
#include "mScene.h"
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
