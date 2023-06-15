#pragma once
#include "mComponent.h"
namespace m
{
	class Mesh;
	class Shader;
    class MeshRenderer :
        public Component
    {
	public:
		MeshRenderer();
		~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Mesh* mMesh;
		Shader* mShader;
    };
}

