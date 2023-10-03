#pragma once

enum class eWallType
{
    Stage4Wall1,
    End,
};
enum class eWallDirection
{
    LeftUpRightDown,
    LeftDownRightUp,
    End
};
eWallDirection wallDirections[(int)eWallType::End] = {
    eWallDirection::LeftUpRightDown,
};
int wallSizes[(int)eWallType::End][2] = {
    {3, 1},
};

