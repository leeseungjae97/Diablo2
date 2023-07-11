#pragma once
#include "mButton.h"
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

		int GetSkillIndex() { return skillIndex; }
	private:
		int indexX;
		int indexY;
		float startX;
		float startY;
		float intervalX;
		float intervalY;
		int skillIndex;
	};
}