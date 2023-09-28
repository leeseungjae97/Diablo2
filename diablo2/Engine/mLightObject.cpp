#include "mLightObject.h"
namespace m
{
    LightObject::LightObject()
    {
    }

    LightObject::~LightObject()
    {
    }

    void LightObject::Update()
    {
        GameObject::Update();
        if(mFollower)
        {
            SET_POS_VEC(this, GET_POS(mFollower));
        }
    }

    void LightObject::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void LightObject::Initialize()
    {
        GameObject::Initialize();
    }

    void LightObject::Render()
    {
        GameObject::Render();
    }
}
