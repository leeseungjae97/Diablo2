#pragma once

enum class eWallType
{
    Stage4Wall1,
    Stage4Wall2,
    End,
};
enum class eWallDirection
{
    LeftUpRightDown,
    LeftDownRightUp,
    End
};
std::wstring wallMaterialNames[(int)eWallType::End] = {
    L"wall1",
    L"wall2",
};
eWallDirection wallDirections[(int)eWallType::End] = {
    eWallDirection::LeftUpRightDown,
    eWallDirection::LeftDownRightUp,
};
int wallSizes[(int)eWallType::End][2] = {
    {3, 1},
    {1, 3},
};

