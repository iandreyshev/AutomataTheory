#pragma once
#include <functional>
#include "tinyxml2/tinyxml2.h"

struct MealyNode
{
	std::string name;
	std::string dest;
	std::string out;
};

class CMealyTable
{
public:
	CMealyTable() = delete;
	CMealyTable(const tinyxml2::XMLDocument &xmlTable)
	{
		(void)xmlTable;
	}
	void Minimize()
	{
	}
	void ForEach(std::function<void(MealyNode&)> action)
	{
		(void)action;
	}

private:

};