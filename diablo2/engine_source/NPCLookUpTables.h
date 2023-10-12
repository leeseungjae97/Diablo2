#pragma once

#ifndef NPC_LOOK_UP_TABLES_H
#define NPC_LOOK_UP_TABLES_H

enum class eNPCType
{
    EquimentNPC,
    ConsumNPC,
    End
};

static std::wstring NPCMaterialNames[(int)eNPCType::End] = {
    L"npc1",
    L"npc2",
};
static std::wstring NPCNames[(int)eNPCType::End] = {
    L"무기상인",
    L"소비상인",
};

static m::math::Vector2 NPCSizes[(int)eNPCType::End] = {
    m::math::Vector2(29.f, 76.f),
    m::math::Vector2(29.f, 76.f),
};
static m::math::Vector2 NPCOffsets[(int)eNPCType::End] = {
    m::math::Vector2(0,0),
    m::math::Vector2(0,0),
};
static m::math::Vector2 NPCCenterPos[(int)eNPCType::End] = {
    m::math::Vector2(0,0),
    m::math::Vector2(0,0),
};
static int NPCLength[(int)eNPCType::End] = {
    16,
    17,
};
static std::wstring NPCMenus[(int)eNPCType::End][4] = {
    {L"대화",L"거래",L"취소",L""},
    {L"거래",L"취소",L"",L""},
};
#endif