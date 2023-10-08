#pragma once
#include "mItem.h"
namespace m
{
    class UI;

    class FieldItem :
        public Item
    {
    public:
        FieldItem(eItem item, Vector3 initPos);
        virtual ~FieldItem();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
    private:
        UI* mNameUI;
        bool bDownAlt;
    };
}

