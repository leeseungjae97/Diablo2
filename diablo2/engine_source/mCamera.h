#pragma once
#include "mComponent.h"

namespace m
{
	class Camera
		: public Component
	{
	public:
		Camera();
		~Camera();

	private:
		static Matrix mView;
		static Matrix mProjection;
	};
}

