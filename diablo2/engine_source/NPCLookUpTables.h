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
    L"�������",
    L"�Һ����",
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
    {L"��ȭ",L"�ŷ�",L"���",L""},
    {L"�ŷ�",L"���",L"",L""},
};