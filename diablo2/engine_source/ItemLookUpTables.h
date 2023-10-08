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
		L"jaredsStoneField",
		L"leaderArmorField",
		L"capField"
	};
	std::wstring fieldItemAnimTable[(int)eItem::END] = {
		L"hpPosionAnim",
		L"mpPosionAnim",
		L"jaredsStoneAnim",
		L"leaderArmorAnim",
		L"capAnim",
	};
	int fieldItemAnimLenght[(int)eItem::END] = {
		17,
		17,
		18,
		17,
		17,
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
		,{37.f, 153.f}
		,{38.f, 173.f}
		,{21.f, 149.f}
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
	// posion = 0 ��� 1 ȸ����
	// weapon = 0 ��� 1 ������ 2 ���밡���� ����
	// armor = 0 ��� 1 ��� 2 ���밡���� ����
	int itemFunctionValue[(int)eItem::END][4] = {
		{25,30,0,0},
		{50, 40,0,0},

		{120,50,1,0},

		{200,10,1,0},

		{100,5,1,0},
	};

	std::wstring itemCostFunctionNames[(int)eItem::END][5] = {
		{L"�̷��� ��������", L"���: ",L"ȸ����: ",L"",L""},
		{L"�̷��� ��������", L"���: ",L"ȸ����: ",L"",L""},

		{L"�ڷ��� ����", L"���: ",L"������: ",L"���� ������ ����: ",L""},

		{L"���� �Ƹ�", L"���: ",L"���: ",L"���� ������ ����: ",L""},

		{L"ĸ", L"���: ",L"���: ",L"���� ������ ����: ",L""},
	};
}
