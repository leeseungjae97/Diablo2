#pragma once

enum class eNPCType
{
    EquimentNPC,
    ConsumNPC,
    End
};

std::wstring NPCMaterialNames[(int)eNPCType::End] = {
    L"npc1",
    L"npc2",
};
std::wstring NPCNames[(int)eNPCType::End] = {
    L"무기상인",
    L"소비상인",
};

m::math::Vector2 NPCSizes[(int)eNPCType::End] = {
    m::math::Vector2(29.f, 76.f),
    m::math::Vector2(29.f, 76.f),
};
m::math::Vector2 NPCOffsets[(int)eNPCType::End] = {
    m::math::Vector2(0,0),
    m::math::Vector2(0,0),
};
m::math::Vector2 NPCCenterPos[(int)eNPCType::End] = {
    m::math::Vector2(0,0),
    m::math::Vector2(0,0),
};
int NPCLength[(int)eNPCType::End] = {
    16,
    17,
};
std::wstring NPCMenus[(int)eNPCType::End][4] = {
    {L"대화",L"거래",L"취소",L""},
    {L"거래",L"취소",L"",L""},
};