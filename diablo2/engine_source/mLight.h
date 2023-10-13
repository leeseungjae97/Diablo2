#pragma once
#include "mComponent.h"
#include "mGraphics.h"

namespace m
{
    class Light :
        public Component
    {
    public:
		Light();
		~Light();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		LightAttribute GetAttribute() { return mAttribute; }
		void SetType(eLightType rype) { mAttribute.type = rype; }
		void SetRadiusX(float radius) { mAttribute.radiusX = radius; }
		void SetRadiusY(float radius) { mAttribute.radiusY = radius; }
		void SetAngle(float angle) { mAttribute.angle = angle; }
		void SetColor(Vector4 color) { mAttribute.color = color; }
		Vector4 GetColor() { return mAttribute.color; }
		eLightType GetType() { return mAttribute.type; }
		float GetRadiusX() { return mAttribute.radiusX; }
		float GetRadiusY() { return mAttribute.radiusY; }
		float GetAngle() { return mAttribute.angle; }
		void LightOff() { bLightOff = true; }
		void LightOn() { bLightOff = false; }

    private:
		LightAttribute mAttribute;
		bool bLightOff;
    };
}

