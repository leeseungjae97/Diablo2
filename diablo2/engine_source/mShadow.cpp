#include "mShadow.h"

#include "mGameObject.h"
#include "mTransform.h"
namespace m
{
    Shadow::Shadow()
        : Component(eComponentType::Shadow)
    {
    }

    Shadow::~Shadow()
    {
    }

    void Shadow::Initialize()
    {
        Component::Initialize();
    }

    void Shadow::Update()
    {
        Component::Update();
    }

    void Shadow::LateUpdate()
    {
        Component::LateUpdate();
    }

    void Shadow::Render()
    {
        Component::Render();
    }
}
