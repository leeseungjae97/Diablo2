#pragma once

enum class eFloorType
{
    Stage1,
    Stage2,
    Stage3,
    Stage4,
    End,
};

std::wstring stage1Floors[10] = {
    L"lava1",
    L"lava2",
    L"lava3",
    L"lava4",
    L"lava5",
    L"lava6",
    L"lava7",
    L"lava8",
    L"lava9",
    L"lava10",
};

m::math::Vector2 floorSizes[(int)eFloorType::End] = {
    m::math::Vector2(8000, 3999),
    m::math::Vector2(8000, 3999),
    m::math::Vector2(8000, 3999),
    m::math::Vector2(8000, 3999),
};