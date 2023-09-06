#include "guiWidget.h"

namespace gui
{
	Widget::Widget()
		: mState(eState::Active)
		, mParent(nullptr)
		, mFlag(ImGuiWindowFlags_None)
	{
	}
	Widget::~Widget()
	{

	}

	void Widget::FixedUpdate()
	{
	}

	void Widget::Update()
	{

	}

	void Widget::LateUpdate()
	{
	}

	void Widget::Render()
	{
		if (mState != eState::Active)
			return;

		if (mParent == nullptr)
		{
			renderParent();
		}
		else
		{
			renderChild();
		}
	}
	void Widget::AddWidget(Widget* child)
	{
		mChilds.push_back(child);
		child->SetParent(this);
	}
	void Widget::WindowFocus(bool enable)
	{
		//if (enable == true)
		//	ImGui::SetWindowFocus(GetName().c_str());
		//else
		//	ImGui::SetWindowFocus(nullptr);
	}

	void Widget::renderParent()
	{

		FixedUpdate();
		bool Active = (bool)GetState();
		ImGui::Begin(GetName().c_str(), &Active, mFlag);
		Update();
		for (Widget* child : mChilds)
		{
			child->Render();
		}
		LateUpdate();
		ImGui::End();

		if (Active == false)
		{
			Close();
		}
	}

	void Widget::renderChild()
	{
		FixedUpdate();
		ImGui::BeginChild(GetName().c_str(), mSize);
		Update();
		for (Widget* child : mChilds)
		{
			child->Render();
		}
		LateUpdate();
		ImGui::EndChild();
	}
}