#pragma once
#include "mButton.h"

#include "..\engine_source\mMaterial.h"


namespace m
{
	class SkillButton :
		public Button
	{
	public:
		SkillButton(int indexX, int indexY, float startX
					, float startY, float intervalX
					, float intervalY, int _skillIndex);
		virtual ~SkillButton();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		bool GetCanClick() { return bCanClick; }
		void SetCanClick(bool _DeClick) { bCanClick = _DeClick; }

		int GetSkillIndex() { return skillIndex; }

		void SetDeClickMaterial(std::shared_ptr<Material> material) { DeClickMaterial = material; }
		void SetDeClickHoverMaterial(std::shared_ptr<Material> material) { DeClickHoverMaterial = material; }

	private:
		bool bCanClick;
		int indexX;
		int indexY;
		float startX;
		float startY;
		float intervalX;
		float intervalY;
		int skillIndex;

		std::shared_ptr<Material> DeClickMaterial;
		std::shared_ptr<Material> DeClickHoverMaterial;
	};
}