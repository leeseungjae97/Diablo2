#pragma once
#include "../engine_source/mScene.h"
namespace m
{
    class Camera;
    class SelectCharacterScene :
        public Scene
    {
    public:
        SelectCharacterScene();
        ~SelectCharacterScene();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
    private:
    };
}
