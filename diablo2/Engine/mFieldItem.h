#pragma once
#include "mGameObject.h"
namespace m
{
    class FieldItem :
        public GameObject
    {
    public:
        FieldItem();
        virtual ~FieldItem();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
    private:
    };
}

