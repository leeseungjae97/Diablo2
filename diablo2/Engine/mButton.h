#pragma once

#include "..\engine_source\mMaterial.h"
#include "..\engine_source\mUI.h"
namespace m
{
	class Button :
		public UI
	{
	public:
		Button();
		virtual ~Button();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		bool GetClick() { return bClick; }
		void SetClickFunction(void (*ccf)()) { fClickFunctionPtr = ccf; }

		void SetClickMaterial(std::shared_ptr<Material> material) { mClickedMaterial = material; }
		void SetNormalMaterial(std::shared_ptr<Material> material) { mNormalMaterial = material; }

	private:
		bool bClick;
		void (*fClickFunctionPtr)();
		std::shared_ptr<Material> mNormalMaterial;
		std::shared_ptr<Material> mClickedMaterial;
	};
}

