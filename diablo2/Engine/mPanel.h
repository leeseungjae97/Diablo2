#pragma once
#include "../engine_source/mUI.h"
namespace m
{
    class Panel :
        public UI
    {
    public:
        Panel();
        virtual ~Panel();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
    };
}

