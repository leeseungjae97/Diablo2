#pragma once
#include "mComponent.h"
#include "mCollider2D.h"
namespace m
{
    class Script :
        public Component
    {
    public:
        Script();
        ~Script();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* other);
        virtual void OnCollisionStay(Collider2D* other);
        virtual void OnCollisionExit(Collider2D* other);
    private:
    };
}

