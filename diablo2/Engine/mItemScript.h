#pragma once
#include "../engine_source/mScript.h"
namespace m
{
    class ItemScript :
        public Script
    {
    public:
        ItemScript();
        virtual ~ItemScript();

        virtual void Initialize() override;
        virtual void Update() override;

        virtual void OnCollisionEnter(Collider2D* other) override;
        virtual void OnCollisionStay(Collider2D* other) override;
        virtual void OnCollisionExit(Collider2D* other) override;
    private:
    };
}

