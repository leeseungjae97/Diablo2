#pragma once

namespace m
{
	enum class eItemType
	{
		None,
		Weapon,
		Ring,
		Amulet,
		Belt,
		Helmet,
		Shoes,
		Glove,
		Armor,
		Posion,
		Scroll,
		END,
	};

	enum eItem
	{
		hpPosion1,
		mpPosion1,

		jaredsStone,
		END
	};
	//std::wstring 
	std::wstring itemNameTable[eItem::END] = {
		// posions
		L"hpPosion1",
		L"mpPosion1",

		//weapons
		L"jaredsStone",
	};
	eItemType itemTypeTable[eItem::END] = {
		eItemType::Posion,
		eItemType::Posion,

		eItemType::Weapon,
	};
	int itemInvenSpaceTable[eItem::END][2] = {
		{1,1},
		{1,1},

		{1,3},
	};
	float itemFieldSpaceTable[eItem::END][2] = {

	};
	// 28.f, 28.f = one inven = 1.f, 1.f
	float itemInvenDisplayScale[eItem::END][2] = {
		{1.f,1.f},
		{1.f,1.f},
		
		{1.f, 3.f},
	};
}
