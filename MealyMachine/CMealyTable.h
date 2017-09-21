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
	CMealyTable(const tinyxml2::XMLDocument &xmlTable);
	CMealyTable Minimize() const;

private:
	CMealyTable();

};