#pragma once



namespace m
{
	std::wstring monsterRHandNames[(int)eMonsterType::End][(int)MDDiablo::eAnimationType::End] = {
		{
			
		},
		{
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
		},
	};
	std::wstring monsterLHandNames[(int)eMonsterType::End][(int)MDDiablo::eAnimationType::End] = {
		{

		},
		{
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
		},
	};
	math::Vector2 monsterHandSizes[(int)eMonsterType::End][(int)MDDiablo::eAnimationType::End] = {
		//Diablo
		{
			// None
		},
		//Balrog
		{
			math::Vector2(207.f, 165.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(157.f, 80.f),
			math::Vector2(161.f, 74.f),
			math::Vector2(152.f, 76.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
		},
	};
	int monsterHandLength[(int)eMonsterType::End][(int)MDDiablo::eAnimationType::End] = {
		{
			
		},
		{
			16,
			0,
			0,
			6,
			8,
			8,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
		},
	};
}