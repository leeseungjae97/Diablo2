#pragma once

#ifndef AFFECT_OVERLAY_LOOK_UP_TABLE_H
#define AFFECT_OVERLAY_LOOK_UP_TABLE_H

enum class eAffectOverlayType
{
    Fire1,
    Fire2,
    Fire3,
    End,
};

enum class eOverlayFunction
{
    Damage,

    End
};

static std::wstring affectOverlayNames[(int)eAffectOverlayType::End] = {
    L"fire1",
    L"fire2",
    L"fire3",
};

static m::math::Vector2 affectOverlaySizes[(int)eAffectOverlayType::End] = {
    m::math::Vector2(66.f, 89.f),
    m::math::Vector2(66.f, 167.f),
    m::math::Vector2(66.f, 136.f),  
};

static int affectOverlayLength[(int)eAffectOverlayType::End] = {
    37,
    37,
    37,
};

static int affectOverlayLoopAnimationIndex[(int)eAffectOverlayType::End][3] = {
    {15,36,29},
    {15,36,29},
    {15,36,29},
};

static float affectOverlayDuration[(int)eAffectOverlayType::End] = {
    0.03f,
    0.03f,
    0.03f,
};

static eOverlayFunction affectOverlayFunction[(int)eAffectOverlayType::End] = {
    eOverlayFunction::Damage,
    eOverlayFunction::Damage,
    eOverlayFunction::Damage,
};

#endif