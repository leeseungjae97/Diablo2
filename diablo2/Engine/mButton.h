#pragma once
#include "mBackground.h"
#include "..\engine_source\mMaterial.h"
namespace m
{
	class Button :
		public Background
	{
	public:
		Button();
		~Button();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		bool GetHover() { return bHover; }
		bool GetClick() { return bClick; }

		void SetClickMaterial(std::shared_ptr<Material> material) { mClickedMaterial = material; }
		void SetNormalMaterial(std::shared_ptr<Material> material) { mNormalMaterial = material; }

	private:
		bool bHover;
		bool bClick;
		std::shared_ptr<Material> mNormalMaterial;
		std::shared_ptr<Material> mClickedMaterial;
	};
}

