#pragma once

enum class eWallType
{
    Stage4Wall1,
    Stage4Wall2,

    Stage1Wall1,
    Stage1Wall2,
    Stage1Wall3,
    Stage1Door,
    Stage1Flag,

    Stage1Chair,

    Stage2Wall1,
    End,
};
enum class eWallDirection
{
    LeftUpRightDown,
    LeftDownRightUp,
    Point,
    Tile,
    Door,
    End
};
static std::wstring wallMaterialNames[(int)eWallType::End] = {
    L"s4Wall1",
    L"s4Wall2",

    L"s1Wall1",
    L"s1Wall2",
    L"s1Wall3",

    L"s1Door",
    L"s1Flag",

    L"s1Chair1",

    L"s2Wall1",
};
static eWallDirection wallDirections[(int)eWallType::End] = {
    eWallDirection::LeftUpRightDown,
    eWallDirection::LeftDownRightUp,

    eWallDirection::Point,
    eWallDirection::LeftUpRightDown,
    eWallDirection::LeftDownRightUp,

    eWallDirection::Door,
    eWallDirection::Point,

    eWallDirection::Tile,

    eWallDirection::Door,
};
static int wallSizes[(int)eWallType::End][2] = {
    {3, 1},
    {1, 3},

    {1, 1},
    {3, 1},
    {1, 3},

    {1, 1},
    {1, 1},

    {2, 2},

    {1, 1},
};

