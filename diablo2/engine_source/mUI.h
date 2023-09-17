#pragma once
#include "mGameObject.h"

namespace m
{
	class UI
		: public GameObject
	{
	public:
		UI();
		UI(bool useDefaultMeshRenderer);
		virtual ~UI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetText(const std::wstring text) { wsText = text; }
		const std::wstring& GetText() { return wsText; }
		void SetTextColor(Vector4 color) { vTextColor = color; }
		void SetTextSize(float textSize) { fTextSize = textSize; }
	private:
		void drawText();

	protected:
		std::wstring wsText;
		float fTextSize;
		Vector4 vTextColor;
	};
}

