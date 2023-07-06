#pragma once
#include "..\engine_source\mScript.h"
#include "..\engine_source\mCamera.h"
namespace m
{
	class GridScript :
		public Script
	{
	public:
		GridScript();
		virtual ~GridScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetCamera(Camera* camera) { mCamera = camera; }
	private:
		Camera* mCamera;
	};
}
