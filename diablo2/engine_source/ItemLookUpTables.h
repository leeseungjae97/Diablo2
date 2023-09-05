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

	enum class eItem
	{
		hpPosion1,
		mpPosion1,

		jaredsStone,

		leaderArmor,

		cap,
		END
	};
	//std::wstring 
	std::wstring itemNameTable[(int)eItem::END] = {
		// posions
		L"hpPosion1",
		L"mpPosion1",

		//weapons
		L"jaredsStone",

		//armor
		L"leaderArmor",

		//helmet
		L"cap",
	};
	std::wstring fieldItemTable[(int)eItem::END] = {
		L"hpPosionField",
		L"mpPosionField",
		L"stoneField",
		L"leaderArmorField",
		L"capField"
	};
	std::wstring fieldItemAnimTable[(int)eItem::END] = {
		L"hpPosionAnim",
		L"mpPosionAnim",
		L"stoneAnim",
		L"leaderArmorAnim",
		L"capAnim",
	};
	
	eItemType itemTypeTable[(int)eItem::END] = {
		eItemType::Posion,
		eItemType::Posion,

		eItemType::Weapon,

		eItemType::Armor,

		eItemType::Helmet,

	};
	m::math::Vector2 itemFieldAnimSpaceTable[(int)eItem::END] = {
		{20.f, 159.f}
		,{20.f, 159.f}
		,{20.f, 159.f}
		,{20.f, 159.f}
		,{20.f, 159.f}
	};
	//float itemFieldSpaceTable[(int)eItem::END][2] = {

	//};
	// 28.f, 28.f = one inven = 1.f, 1.f
	float itemInvenDisplayScale[(int)eItem::END][2] = {
		{1.f, 1.f},
		{1.f, 1.f},

		{1.f, 3.f},
		{2.f, 4.f},
		
		{2.f, 2.f},
	};
}
