#pragma once
#include "_Engine.h"
namespace m
{
    class FieldItem;

    class FieldItemManager
	{
	public:
		static void Add(FieldItem* item);
		static void Erase(FieldItem* item);
		static void EraseAll();
		static std::vector<FieldItem*> items;
	};
}

