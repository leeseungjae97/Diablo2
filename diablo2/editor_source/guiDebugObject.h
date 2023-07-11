#pragma once
#include "../engine_source/mGameObject.h"
namespace gui
{
	class DebugObject
		: public m::GameObject
	{
	public:
		DebugObject();
		~DebugObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:
	};
}


