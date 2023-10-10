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
		float GetTextSize() { return fTextSize; }
		void SetTextNormalColor(Vector4 color) { vTextNormalColor = color; }
		void SetTextClickColor(Vector4 color) { vTextHoverColor = color; }
		void SetTextSize(float textSize) { fTextSize = textSize; }
		void SetTextOffset(Vector2 textOffset) { vTextOffset = textOffset; }
	private:
		void drawText();

	protected:
		std::wstring wsText;
		float fTextSize;
		Vector2 vTextOffset;
		Vector4 vTextColor;
		Vector4 vTextNormalColor;
		Vector4 vTextHoverColor;
	};
}

