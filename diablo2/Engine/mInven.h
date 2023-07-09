#pragma once
#include "..\engine_source\mUI.h"

#include "mInvenItem.h"
namespace m
{
	class Inven :
		public UI
	{
	public:
		Inven();
		~Inven();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		bool GetFill() { return bFill; }
		void SetFill(bool fill) { bFill = fill; }

		InvenItem* GetFillItem() { return mFillItem; }
		void SetFillItem(InvenItem* item) { mFillItem = item; }
	private:
		InvenItem* mFillItem;
		bool bFill;
	};
}

