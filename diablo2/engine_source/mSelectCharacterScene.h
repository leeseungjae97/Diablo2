#pragma once
#include "mScene.h"
namespace m
{
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
