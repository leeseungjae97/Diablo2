#pragma once

enum class eTorchType
{
    Stage1Torch1,
    End
};

std::wstring wsTorchNames[(int)eTorchType::End] = {
    L"st1Torch",
};
int iTorchLength[(int)eTorchType::End] = {
    20,
};
m::math::Vector2 vTorchCenterPos[(int)eTorchType::End] = {
    m::math::Vector2(0,0),
};
m::math::Vector2 vTorchSizes[(int)eTorchType::End] = {
    m::math::Vector2(32, 113),
};