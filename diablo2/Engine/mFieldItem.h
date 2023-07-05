#pragma once
#include "mItem.h"
namespace m
{
    class FieldItem :
        public Item
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

