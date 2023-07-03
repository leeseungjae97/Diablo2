#pragma once
#include "mGameObject.h"

namespace m
{
	class UI
		: public GameObject
	{
	public:
		UI();
		virtual ~UI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		bool GetHover() { return bHover; }

	private:
		bool bHover;
	};
}

