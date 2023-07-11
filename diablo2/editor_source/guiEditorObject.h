#pragma once
#include "../engine_source/mGameObject.h"
namespace gui
{
	class EditorObject
		: public m::GameObject
	{
	public:
		EditorObject();
		virtual	~EditorObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:
	};
}


